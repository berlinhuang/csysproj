//
// Created by root on 17-11-8.
//


/**

两个进程通过一个管道只能实现单向通信
用于有血缘关系的进程之间,通过fork来传递
其实就是在内核开辟一块缓冲区



写端关闭，读端读完返回0
写端没写，读端读完阻塞
读端关闭，产生sigpipe信号13，写进程会终止进程
读端没读，写端写完阻塞


父进程调用pipe开辟管道，得到两个文件描述符指向管道的两端。
父进程调用fork创建子进程，那么子进程也有两个文件描述符指向同一管道。
父进程关闭管道读端，子进程关闭管道写端。父进程可以往管道里写，子进程可以从管道里读，管道是用环形队列实现的，数据从写端流入从读端流出，这样就实现了进程间通信。
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 80
int main(void)
{
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];
    if (pipe(fd) < 0) {//调用pipe函数时在内核中开辟一块缓冲区（称为管道）用于通信，它有一个读端一个写端
        perror("pipe");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (pid > 0) { /* parent */
        close(fd[0]);//关闭读端f[0]
        write(fd[1], "hello world\n", 12);
        wait(NULL);
    } else { /* child */
        close(fd[1]);//关闭写端f[1]
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
    return 0;
}
