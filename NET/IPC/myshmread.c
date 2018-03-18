//
// Created by root on 18-3-18.
//

#include "myshm.h"
int main(int argc, char **argv)
{
    const char * const pathname=".";

    int      id;
    int flag;
    char    *ptr;
    size_t  length=1024;
    key_t key;
    struct shmid_ds buff;
    key = ftok(pathname,1);

    if(key<0)
    {
        printf("ftok error\r\n");
        return -1;
    }

    flag = IPC_CREAT |  0400;

    id = shmget(key, length, flag);                                         //shmget
    if(id<0)
    {
        printf("shmget error\r\n");
        return -1;
    }
    ptr = shmat(id, NULL, 0);                                               //shmat
    if(ptr==NULL)
    {
        printf("shmat error\r\n");
        return -1;
    }

    shmctl(id,IPC_STAT,&buff);                                             //shmctl
    int i;
    unsigned char c;
    for(i=0;i<buff.shm_segsz;i++)
    {
        c=*ptr++;
        printf("ptr[%d]=%d\r\n",i,c);
    }
    shmctl(id, IPC_RMID, NULL);
    return 0;
}