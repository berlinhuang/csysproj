//
// Created by root on 17-11-8.
//

//多进程并发服务器
/**
#include <arpa/inet.h>

int inet_pton(int af, const char *src, void *dst);

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);

支持IPv4和IPv6
可重入函数
 */

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "./../wrap.h"
#define MAXLINE 80
#define SERV_PORT 8000
void do_sigchild(int num)
{
    waitpid(0, NULL, WNOHANG);//0回收和当前调用waitpid一个组的所有子进程
}

int main(void)
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int listenfd, connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
    int i, n;
    pid_t pid;
    struct sigaction newact;//信号捕捉

    newact.sa_handler = do_sigchild;//设置捕捉函数
    sigemptyset(&newact.sa_mask);//设置阻塞其他的信号
    newact.sa_flags = 0;//
    sigaction(SIGCHLD, &newact, NULL);// 一个进程停止会将SIGCHLD信号发给父进程， 处理的信号SIGCHLD，newact 新的处理函数， NULL不保留旧的处理函数

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);//打开网络通讯接口

    // bzero无返回值，并且使用string.h头文件，string.h曾经是posix标准的一部分，但是在POSIX.1-2001标准里面，这些 函数被标记为了遗留函数而不推荐使用。
    // 在POSIX.1-2008标准里已经没有这些函数了。推荐使用memset替代bzero。
    bzero(&servaddr, sizeof(servaddr));//将内存块的前 n 个字节清零，s 参数为指针
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//绑定
    Listen(listenfd, 20);//监听

    printf("Accepting connections ...\n");
    while (1) {
        cliaddr_len = sizeof(cliaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);//cliaddr_len 为NULL表示不关心客户端地址，返回新的文件描述符
        pid = fork();//多进程并发
        if (pid == 0) {//子进程
            Close(listenfd);//子进程监听的文件描述符 不需要
            while (1) {
                n = Read(connfd, buf, MAXLINE);//读取
                if (n == 0) {
                    printf("the other side has been closed.\n");
                    break;
                }
                printf("received from %s at PORT %d\n",
                       inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),//地址 [将“二进制整数” －> “点分十进制”]
                       ntohs(cliaddr.sin_port));//端口 将一个无符号短整型数从网络字节顺序转换为主机字节顺序
                for (i = 0; i < n; i++)
                    buf[i] = toupper(buf[i]);//touppper
                Write(connfd, buf, n);//返回
            }
            Close(connfd);
            return 0;
        }
        else if (pid > 0) {//父进程
            Close(connfd);//关闭子进程用的文件描述符，避免下次fork在产生
        }
        else//pid < 0 失败
            perr_exit("fork");
    }

    return 0;
}
