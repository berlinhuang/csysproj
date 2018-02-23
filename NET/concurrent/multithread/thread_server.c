//
// Created by root on 17-11-8.
//

/* server.c */
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "./../wrap.h"
#include <ctype.h>

#define MAXLINE 80
#define SERV_PORT 8000

struct s_info {//客户端缓冲
    struct sockaddr_in cliaddr;
    int connfd;
};

void *do_work(void *arg)
{
    int n,i;
    struct s_info *ts = (struct s_info*)arg;
    char buf[MAXLINE];//线程的用户空间栈上
    char str[INET_ADDRSTRLEN];
    /* 可以在创建线程前设置线程创建属性,设为分离态,哪种效率高内? */
    pthread_detach(pthread_self());//设置线程分离属性（两种方法：创建前设置属性；pthread_detach()设置)
    while (1) {
        n = Read(ts->connfd, buf, MAXLINE);
        if (n == 0) {
            printf("the other side has been closed.\n");
            break;
        }
        printf("received from %s at PORT %d\n",
               inet_ntop(AF_INET, &(*ts).cliaddr.sin_addr, str, sizeof(str)),
               ntohs((*ts).cliaddr.sin_port));
        for (i = 0; i < n; i++)
            buf[i] = toupper(buf[i]);
        Write(ts->connfd, buf, n);
    }
    Close(ts->connfd);
}


int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    int i = 0;
    pthread_t tid;
    struct s_info ts[383];//线程数
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);//打开连接端口
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//绑定
    Listen(listenfd, 20);//监听

    printf("Accepting connections ...\n");
    while (1) {
        cliaddr_len = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);//接收连接
        ts[i].cliaddr = cliaddr;
        ts[i].connfd = connfd;
        /* 达到线程最大数时,pthread_create出错处理, 增加服务器稳定性 */
        pthread_create(&tid, NULL, do_work, (void*)&ts[i]);//创建线程 新线程要执行的函数do_work    ts[i]是调用函数的参数
        i++;
    }
    return 0;
}
