//
// Created by root on 17-11-15.
//
/**
 *
 *
 创建socket默认为阻塞


 epoll
 水平触发，只要可读或可写，事件会一直触发
 边缘触发，只有从不可读变为可读、从不可写变成可写，事件才会触发

☆☆☆基于此，水平触发，socket不需要设置为non-block，因为只要触发，就可以读或写。

☆☆☆边缘触发要设置成非阻塞的原因:
 对于边缘，事件一旦触发，需要用户一直读，直到缓冲区数据全部读完为止才可以，
 如果设置为block，在没有数据可读时，就block了,这样可能导致其他文件描述符的任务会被饿死
 如果设置为non-block，有数据可读时会返回eagain错误来告知用户，数据读完了，不用再读了

------------------------------------------------------
 场景：
1 管道(pipe)读端的文件描述符(rfd)注册于Epoll实例。
2 写者(Writer)向管道(pipe)写端写2KB的数据。
3 epoll_wait调用结束，返回rfd作为就绪的文件描述符。
4 管道读者(pipe reader) 从rfd读1KB的数据。
5 下一次epoll_wait调用

 问题:
rfd文件描述符使用EPOLLET(边缘触发)标记加入Epoll接口，第5步对epoll_wait的调用可能会阻塞，尽管文件输入缓冲区中仍然有可用数据；
与此同时，远端实体由于已经发送数据，可能正在等待回应

 原因:
边缘触发模式仅在所监控的文件描述符状态发生变化时才投递事件，所以，第5步的调用方可能最终一直在等待数据到来，但数据其实已经在输入缓存区
经过第2步的写操作和第3步的事件处理，rfd上只会产生一次事件。由于第4步的读操作没有读完全部的缓冲区数据，第5步对epoll_wait的调用可能会永远阻塞。(  重点  )
------------------------------------------------------

 使用EPOLLET标记时，应该设置文件描述符为非阻塞，以避免阻塞读写，使处理多个文件描述符的任务饿死。
 因此，使用Epoll边缘触发(EPOLLET)模式的接口，以下有两点建议：
1 使用非阻塞的文件描述符
2 只有在read或write返回EAGAIN之后，才继续等待事件（调用epoll_wait）

------------------------------------------------------

饥饿（边沿触发）
 原因:
    如果I/O数据量很大，可能在读取数据的过程中其他文件得不到处理，造成饥饿。
 解决方法:
    是维护一个就绪列表，在关联数据结构中标记文件描述符为就绪状态，由此可以记住哪些文件在等待，并对所有就绪文件作轮转处理。
 **/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_SOCKET_NUMBERS 1024
#define BUF_SIZE 1024

int setnonblocking(int fd);
void addfd(int epollfd, int fd, int flag);
void lt(struct epoll_event* events, int number, int epollfd, int listenfd);
void et(struct epoll_event* events, int number, int epollfd, int listenfd);


int main (int argc, char* argv[])
{
    if( argc <= 2)
    {
        printf("please input ip address and port num\r\n");
        exit(1);
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    int ret = 0;

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int listenfd = socket(AF_INET,SOCK_STREAM, 0);                                     //socket
    assert(listenfd >= 0);
    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));//               //bind
    assert(ret != -1);
    ret = listen(listenfd, 5);                                                         //listen
    assert(ret != -1);

    //连接部分放到epoll托管
    struct epoll_event events[MAX_SOCKET_NUMBERS];//epoll所能托管最多文件描述符个数
    int epollfd = epoll_create(5);                                                     //epoll_create
    assert(epollfd != -1);
    addfd(epollfd,listenfd,true);// 把监听套接字存放到epoll true采用ET模式                 //epoll_ctl        add  listen_fd

    while(1)
    {
        //不停阻塞等待事件处理，返回就把事件处理掉
        //-1表示会一直阻塞
        int ret = epoll_wait(epollfd, events, MAX_SOCKET_NUMBERS, -1);                 //epoll_wait
        if(ret < 0)
        {
            printf("epoll wait error\r\n");
            exit(1);
        }
        lt(events, ret, epollfd, listenfd);                          // Level-triggered
        //et(events,ret,epollfd,listenfd);                              //Edge-triggered
    }
    close(listenfd);
    return 0;
}

int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL,new_option);
    return new_option;

}


void addfd(int epollfd,int fd, int flag)
{
    struct epoll_event event;
    memset(&event, 0x00, sizeof(event));
    event.data.fd = fd;
    event.events = EPOLLIN; //可读
    if(flag)
    {
        event.events |= EPOLLET;                                                                            // level trigger
    }
    epoll_ctl(epollfd, EPOLL_CTL_ADD,fd,&event);//
    setnonblocking(fd);//设置成非阻塞，不然阻塞模式accept会出现问题
}


//电平触发(只要可读，可写 就能读或者写)    提醒多次，可以下次处理
void lt( struct epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUF_SIZE];
    for(int i= 0 ; i<number;i++)
    {
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd)//监听事件的  套接字   listenfd就绪有新的客户端连接请求
        {
            struct sockaddr_in client_address;
            socklen_t client_addresslen =sizeof(client_address);
            int connfd = accept(listenfd, (struct sockaddr*)&client_address,&client_addresslen);
            addfd(epollfd, connfd, 0);                                          //add new_fd
            if(connfd<0)
            {
                printf("accept error\r\n");
                exit(1);
            }
        }
        else if(events[i].events  &  EPOLLIN)//可读事件的  套接字
        {
            printf("LT once\r\n");
            memset(buf,0x00, sizeof(buf));
            int ret = recv(sockfd,buf,sizeof(buf)-1,0);
            if(ret <= 0)
            {
                printf("recv 0\r\n");
                close(sockfd);
                continue;
            }
            printf("recv data form %d buf is %s \r\n",sockfd,buf);

        }
        else
        {
            printf("something else happen\r\n");
        }
    }
}

//边缘触发(从不可读到可读， 从不可写到可写 才能触发)    只提醒一次，必须处理  边缘触发，顾名思义，不到边缘情况，是死都不会触发的
void et( struct epoll_event* events, int number, int epollfd, int listenfd)
{
    char buf[BUF_SIZE];
    for(int i = 0;i<number;i++)
    {
        int sockfd = events[i].data.fd;
        if(sockfd == listenfd)
        {
            struct sockaddr_in client_address;
            socklen_t client_addresslen = sizeof(client_address);
            int connfd = accept (listenfd, (struct sockaddr *)&client_address, &client_addresslen);//接收新的连接
            addfd(epollfd, connfd, 1);                                                     //add     newcon_fd
        }
        else if(events[i].events & EPOLLIN)
        {
            printf("ET once \r\n");
            while(1)//促发一次就要全部读取完，或者直到errno=EAGAIN
            {
                memset(buf,0x00,sizeof(buf));
                int ret =recv(sockfd,buf,sizeof(buf)-1,0);   //非阻塞 会立即返回 返回成功说明读写操作完成了，返回失败会设置相应errno状态码
                if(ret < 0)//中断
                {//再读一次或者这是一个阻塞的socket，说明读缓冲区没有数据，已经处理完了
                    if((errno == EAGAIN)||(errno == EWOULDBLOCK))
                    {
                        printf("read later\r\n");
                        break;
                    }
                    close(sockfd);
                    break;

                }
                else if(ret == 0)
                {
                    int res = epoll_ctl(epollfd, EPOLL_CTL_DEL, sockfd, NULL);
                    close(sockfd);
                }
                else
                {
                    printf("recv data form %d buf is %s\r\n",sockfd,buf);
                }
            }
        }
        else
        {
            printf("something else happen\r\n");

        }
    }
}