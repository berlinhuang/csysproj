//
// Created by root on 17-11-8.
//

// epoll multiIO server.c

//提高程序在大量并发连接中只有少量活跃的情况下的系统CPU利用率

//select/poll那种IO事件的电平触发（Level Triggered）
// 缺省的工作方式，并且同时支持block和no-block socket。在这种做法中，内核告诉你一个文件描述符是否就绪了，然后你可以对这个就绪的fd进行IO操作。
// 如果你不作任何操作，内核还是会继续通知你的

//边沿触发（Edge Triggered）
// 高速工作方式，只支持no-block socket。在这种模式下，当描述符从未就绪变为就绪时，内核通过epoll告诉你。
// 然后它会假设你知道文件描述符已经就绪，并且不会再为那个文件描述符发送更多的就绪通知，直到你做了某些操作导致那个文件描述符不再为就绪状态了

/**
 *
#include <sys/epoll.h>
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)

epfd：为epoll_creat的句柄

op：表示动作，用3个宏来表示：
    EPOLL_CTL_ADD(注册新的fd到epfd)，
    EPOLL_CTL_MOD(修改已经注册的fd的监听事件)，
    EPOLL_CTL_DEL(从epfd删除一个fd)；

event：告诉内核需要监听的事件
    struct epoll_event {
        uint32_t events; // Epoll events
        epoll_data_t data; // User data variable
    };
        EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）
        EPOLLOUT：表示对应的文件描述符可以写
        EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）
        EPOLLERR：表示对应的文件描述符发生错误
        EPOLLHUP：表示对应的文件描述符被挂断；
        EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的
        EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里



#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout)

 events：用来从内核得到事件的集合，

 maxevents：告之内核这个events有多大，这个maxevents的值不能大于创建epoll_create()时的size，

 timeout：是超时时间
    -1：阻塞
    0：立即返回，非阻塞
    >0：指定微秒

 返回值：成功返回有多少文件描述符就绪，时间到时返回0，出错返回-1

 */

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //bzero
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
//#include <errno.h>
#include "../wrap.h"
#define MAXLINE 80
#define SERV_PORT 8000
#define OPEN_MAX 1024
int main(int argc, char *argv[])
{
    int i, j, maxi, listenfd, connfd, sockfd;
    int nready, efd, res;
    ssize_t n;
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clilen;
    int client[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;
    struct epoll_event tep, ep[OPEN_MAX];//

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);// 接口
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));//绑定

    Listen(listenfd, 20);//监听

    for (i = 0; i < OPEN_MAX; i++)
        client[i] = -1;
    maxi = -1;
    efd = epoll_create(OPEN_MAX);//创建epoll句柄 OPEN_MAX个文件描述符                                         epoll_create

    if (efd == -1)
        perr_exit("epoll_create");
    tep.events = EPOLLIN;  //对应的文件描述符可读
    tep.data.fd = listenfd; //

    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);//控制某个epoll监控的文件描述符上的事件 注册 修改 删除     epoll_ctl

    if (res == -1)
        perr_exit("epoll_ctl");
    for ( ; ; ) {
        // efd :
        // ep : 冲内核得到的事件集合
        // OPEN_MAX: 告诉内核ep多大，不能大于创建epoll_create(int size) 中size的大小
        nready = epoll_wait(efd, ep, OPEN_MAX, -1); //内存拷贝，利用mmap()文件映射内存加速与内核空间的消息传递；即epoll使用mmap减少复制开销  epoll_wait
        if (nready == -1) //-1表示阻塞
            perr_exit("epoll_wait");
        for (i = 0; i < nready; i++)
        {
            if (!(ep[i].events & EPOLLIN))
                continue;
            if (ep[i].data.fd == listenfd) //新连接
            {
                clilen = sizeof(cliaddr);
                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);//接收新的连接
                printf("received from %s at PORT %d\n",
                       inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                       ntohs(cliaddr.sin_port));
                for (j = 0; j < OPEN_MAX; j++)
                    if (client[j] < 0)
                    {
                        client[j] = connfd;/* save descriptor */
                        break;
                    }
                if (j == OPEN_MAX)
                    perr_exit("too many clients");
                if (j > maxi)
                    maxi = j;

                tep.events = EPOLLIN;
                tep.data.fd = connfd; /* max index in client[] array */
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);// 监听新的文件描述符

                if (res == -1)
                    perr_exit("epoll_ctl");
            }
            else//
            {
                sockfd = ep[i].data.fd;
                n = Read(sockfd, buf, MAXLINE);
                if (n == 0) //客户端关闭连接
                {
                    for (j = 0; j <= maxi; j++)
                    {
                        if (client[j] == sockfd)
                        {
                            client[j] = -1;//重新初始化
                            break;
                        }
                    }
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);//将该文件描述符从红黑树上摘除
                    if (res == -1)
                        perr_exit("epoll_ctl");
                    Close(sockfd);//关闭与客户端连接
                    printf("client[%d] closed connection\n", j);
                }
                else //对读取的数据进行处理
                {
                    for (j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);
                    Writen(sockfd, buf, n);
                }
            }
        }
    }
    close(listenfd);
    close(efd);
    return 0;
}
