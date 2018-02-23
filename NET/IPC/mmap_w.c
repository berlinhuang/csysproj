//
// Created by root on 17-11-8.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAPLEN 0x1000

void sys_err(char *str, int exitno)
{
    perror(str);
    exit(exitno);
}


int main( int argc, char *argv[])
{
    char *mm;
    int fd;
    int i = 0;
    if(argc <2)
    {
        printf("./a.out filename\n");
        exit(1);
    }
    fd = open(argv[1],O_RDWR|O_CREAT, 0777);
    if(fd < 0)
        sys_err("open",1);
    //文件头0(SEEK_SET)，当前位置1(SEEK_CUR)，文件尾2(SEEK_END)）
    if(lseek(fd,MAPLEN-1, SEEK_SET)<0) //
        sys_err("lseek",3);
    if(write(fd,"\0",1)<0)
        sys_err("write",4);
    mm = mmap(NULL,MAPLEN,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0); //

    if(mm==MAP_FAILED)
        sys_err("mmap",2);
    close(fd);
    while(1)
    {
        sprintf(mm,"hello%d",i++);
        sleep(1);
    }
    munmap(mm,MAPLEN);
    return 0;
}