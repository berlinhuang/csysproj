//
// Created by root on 17-11-8.
//

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "./../wrap.h"
#define MAXLINE 80
#define SERV_PORT 8000
int main(int argc, char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd, n;
    sockfd = Socket(AF_INET, SOCK_STREAM, 0);//设置socket地址，数据流，协议类型

    bzero(&servaddr, sizeof(servaddr));//清空地址

    servaddr.sin_family = AF_INET;//ipv4
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);//地址
    servaddr.sin_port = htons(SERV_PORT);//端口

    Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//连接服务器

    while (fgets(buf, MAXLINE, stdin) != NULL) {//读取键盘输入
        Write(sockfd, buf, strlen(buf));
        n = Read(sockfd, buf, MAXLINE);
        if (n == 0)
            printf("the other side has been closed.\n");//返回结果为空
        else
            Write(STDOUT_FILENO, buf, n);//将服务器返回的结果写到标准输出
    }
    Close(sockfd);
    return 0;
}
