//
// Created by root on 17-11-8.
//

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
