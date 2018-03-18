//
// Created by root on 18-3-18.
//

/**
struct shmid_ds{
    struct ipc_perm shm_perm;  //操作权限
    int shm_segsz;             //段的大小（以字节为单位）
    time_t shm_atime;          //最后一个进程附加到该段的时间
    time_t shm_dtime;          //最后一个进程离开该段的时间
    time_t shm_ctime;          //最后一个进程修改该段的时间
    unsigned short shm_cpid;   //创建该段进程的pid
    unsigned short shm_lpid;   //在该段上操作的最后1个进程的pid
    short shm_nattch;          //当前附加到该段的进程的个数
    //下面是私有的
    unsigned short shm_npages;          //段的大小（以页为单位）
    unsigned long *shm_pages;           //指向frames->SHMMAX的指针数组
    struct vm_area_struct *attaches;    //对共享段的描述
};
 */

#include "myshm.h"
#define PATHNAME "."
int main(int argc, char **argv)
{

    int      id;
    int flag;
    char    *ptr;
    size_t  length=1024;
    key_t key;
    //内核为每一个共享内存段维护着一个特殊的数据结构，就是shmid_ds，这个结构在include/linux/shm.h中定义
    struct shmid_ds buff;
    key = ftok(PATHNAME,1);

    if(key<0)
    {
        printf("ftok error\r\n");
        return -1;
    }
// IPC_CREAT   如果共享内存不存在，则创建一个共享内存，否则打开操作。
// IPC_EXCL    只有在共享内存不存在的时候，新的共享内存才建立，否则就产生错误。
    id = shmget(key, length,IPC_CREAT | IPC_EXCL| S_IRUSR | S_IWUSR  );     //shmget
    if(id<0)
    {
        printf("errno: %s\r\n",strerror(errno));
        printf("shmget error\r\n");
        return -1;
    }
    ptr = shmat(id, NULL, 0);                                               //shmat
    if(ptr==NULL)
    {
        printf("shmat error\r\n");
        return -1;
    }
    // IPC_STAT 设置shmid_ds结构中的数据反射与共享内存相关联的值。
    // IPC_SET 如果进程有相应的权限，将与共享内存相关联的值设置为shmid_ds数据结构中所提供的值。
    // IPC_RMID 删除共享内存段。
    shmctl(id,IPC_STAT,&buff);                                              //shctl
    int i;
    for(i=0;i<buff.shm_segsz;i++)
    {
        *ptr++ = i%256;
    }
    return 0;
}