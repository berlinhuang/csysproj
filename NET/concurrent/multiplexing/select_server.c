//
// Created by root on 17-11-8.
//


/**
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
nfds:        监控的文件描述符集里最大文件描述符加1，因为此参数会告诉内核检测前多少个文件描述符的状态
readfds：    监控有读数据到达文件描述符集合，传入传出参数
writefds：   监控写数据到达文件描述符集合，传入传出参数
exceptfds：  监控异常发生达文件描述符集合,如带外数据到达异常，传入传出参数
timeout：    定时阻塞监控时间，3种情况
                1.NULL，永远等下去
                2.设置timeval，等待固定时间
                3.设置timeval里时间均为0，检查描述字后立即返回，轮询
struct timeval {
    long tv_sec; // seconds
    long tv_usec; // microseconds
};

int FD_ISSET(int fd, fd_set *set); 测试文件描述符集合里fd是否置1
void FD_SET(int fd, fd_set *set); 把文件描述符集合里fd位置1
void FD_ZERO(fd_set *set); 把文件描述符集合里所有位清0

**/

/* server.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include "./../wrap.h"
#define MAXLINE 80
#define SERV_PORT 8000
int main(int argc, char *argv[])
{
    int i, maxi, maxfd, listenfd, connfd, sockfd;
    int nready, client[FD_SETSIZE];    // FD_SETSIZE 默认为 1024                 1.单个进程可监控的fd数量被限制，即能监听端口的大小有限
    ssize_t n;
    fd_set rset, allset;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];// #define INET_ADDRSTRLEN 16
    socklen_t cliaddr_len;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);                               //socket

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(SERV_PORT);
    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));           //bind

    Listen(listenfd, 20);                                                     //listen

    maxfd = listenfd; // 默认最大FD_SETSIZE
    maxi = -1;// 初始化
    for (i = 0; i < FD_SETSIZE; i++)
        client[i] = -1;// 用-1初始化client[]                                     3.需要维护一个用来存放大量fd的数据结构，这样会使得用户空间和内核空间在传递该结构时复制开销大
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    for ( ; ; ) {
        rset = allset;
        // 阻塞( 没有数据不会执行后面的语句) 每次循环时都从新设置select监控信号集
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);   //                 2.对socket进行扫描时是线性扫描，即采用轮询的方法，效率较低
        if (nready < 0)
            perr_exit("select error");
        if (FD_ISSET(listenfd, &rset))// new client connection
        {
            cliaddr_len = sizeof(cliaddr);
            connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);         //accept
            printf("received from %s at PORT %d\n",inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
            for (i = 0; i < FD_SETSIZE; i++)
                if (client[i] < 0)
                {
                    client[i] = connfd; // 保存accept返回的文件描述符到client[]里
                    break;
                }
            if (i == FD_SETSIZE) // 达到select能监控的文件个数上限 1024
            {
                fputs("too many clients\n", stderr);
                exit(1);
            }
            FD_SET(connfd, &allset);// 添加一个新的文件描述符到监控信号集里
            if (connfd > maxfd)
                maxfd = connfd; // select第一个参数需要
            if (i > maxi)
                maxi = i; // 更新client[]最大下标值
            if (--nready == 0)
                continue;
            //如果没有更多的就绪文件描述符继续回到上面select阻塞监听,负责处理未处理完的就绪文件描述符
        }
        for (i = 0; i <= maxi; i++)// 遍历文件描述符来获取已经就绪的socket 检测哪个clients 有数据就绪
        {
            if ( (sockfd = client[i]) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset))
            {
                if ( (n = Read(sockfd, buf, MAXLINE)) == 0)
                {
                    Close(sockfd);/*当client关闭链接时,服务器端也关闭对应链接 */
                    FD_CLR(sockfd, &allset);/* 解除select监控此文件描述符 */
                    client[i] = -1;
                }
                else
                {
                    int j;
                    for (j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);
                    Write(sockfd, buf, n);
                }
                if (--nready == 0)
                    break;
            }
        }
    }
    close(listenfd);
    return 0;
}
