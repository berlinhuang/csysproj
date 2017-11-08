//
// Created by root on 17-11-8.
//

/**

当只写打开FIFO管道时，如果没有FIFO没有读端打开，则open写打开会阻塞。
FIFO内核实现时可以支持双向通信。（pipe单向通信，因为父子进程共享同一个file 结构体）
FIFO可以一个读端，多个写端；也可以一个写端，多个读端。



命令行下建一个fifo : mkfifo myfifo
也可以用api: int mkfifo(const char *pathname, mode_t mode)
两个文件编译成fifo_w fifo_r
调用写： ./fifo_w myfifo
调用读： ./fifo_r myfifo

 */



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
void sys_err(char *str, int exitno)
{
    perror(str);
    exit(exitno);

}

int main(int argc, char *argv[])
{
    int fd;
    char buf[1024];
    int len;
    if(argc<2)
    {
        printf("./a.out fifoname\n");
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        sys_err("open",1);
    }
    len=read(fd,buf,sizeof(buf));
    write(STDOUT_FILENO,buf,len);
    close(fd);

    return 0;
}