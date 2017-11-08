//
// Created by root on 17-11-8.
//

// epoll multiIO server.c
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include "../../wrap.h"
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
    efd = epoll_create(OPEN_MAX);//创建epoll句柄 OPEN_MAX个文件描述符

    if (efd == -1)
        perr_exit("epoll_create");
    tep.events = EPOLLIN;  //对应的文件描述符可读
    tep.data.fd = listenfd; //

    //efd:epoll_create()返回的句柄
    //EPOLL_CTL_ADD: 注册新的fd到epfd
    //listenfd:
    //tep:告诉内核要监听的时间
    res = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);//控制某个epoll监控的文件描述符上的事件 注册 修改 删除


    if (res == -1)
        perr_exit("epoll_ctl");
    for ( ; ; ) {
        // efd :
        // ep : 冲内核得到的事件集合
        // OPEN_MAX: 告诉内核ep多大，不能大于创建epoll_create(int size) 中size的大小
        nready = epoll_wait(efd, ep, OPEN_MAX, -1); // 阻塞监听 等待所监控的文件描述符上面的事件发生,相当于select()
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
