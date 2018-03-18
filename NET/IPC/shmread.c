//
// Created by root on 18-3-18.
//

/**
 * int shmget(
 * key_t key,  //通过 ftok 获取。
 * size_t size, //size 以字节为单位指定内存区大小
 * int shmflg //表示权限组合 可以是 IPC_EXCL | IPC_CREAT | 0600
 * );
 *
 *
 * //启动对该共享内存的访问，并把共享内存连接到当前进程的地址空间
 * void *shmat(
 *  int shm_id,             //由shmget返回
 *  const void *shm_addr,   //shm_addr指定共享内存连接到当前进程中的地址位置，通常为空，表示让系统来选择共享内存的地址。
 *  int shmflg              //shm_flg是一组标志位，通常为0
 * );
 *
 * void *shmat(
 *  int shm_id,                  //由shmget返回
 *  const void *shm_addr,        //shmat函数返回的地址指针
 *  int shmflg
 * );
 *
 *
 */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include "shmdata.h"
#include <string.h>

int main()
{
    int running = 1;//程序是否继续运行的标志
    void *shm = NULL;//分配的共享内存的原始首地址
    struct shared_use_st *shared;//指向shm
    int shmid;      //共享内存标识符
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);//创建共享内存
    if(shmid == -1)
    {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }
    //将共享内存连接到当前进程的地址空间
    shm = shmat(shmid, 0, 0);
    if(shm == (void*)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("\nMemory attached at %X\n",  (unsigned int)(long)shm);
    //设置共享内存
    shared = (struct shared_use_st*)shm;
    shared->written = 0;
    while(running)//读取共享内存中的数据
    {
        //没有进程向共享内存定数据有数据可读取
        if(shared->written != 0)
        {
            printf("You wrote: %s", shared->text);
            sleep(rand() % 3);
            //读取完数据，设置written使共享内存段可写
            shared->written = 0;
            //输入了end，退出循环（程序）
            if(strncmp(shared->text, "end", 3) == 0)
                running = 0;
        }
        else//有其他进程在写数据，不能读取数据
            sleep(1);
    }
    //把共享内存从当前进程中分离
    if(shmdt(shm) == -1)
    {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    //删除共享内存
    if(shmctl(shmid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
