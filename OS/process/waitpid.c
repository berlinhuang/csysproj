
/**

僵尸进程: 子进程退出，父进程没有回收子进程资源（PCB），则子进程变成僵尸进程
孤儿进程: 父进程先于子进程结束，则子进程成为孤儿进程,子进程的父进程成为1号进程init进程，称为init进程领养孤儿进程

**/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


#include <sys/types.h>
#include <sys/wait.h>



// child process will be a Zombie process
int Zombie(void)
{
    pid_t pid=fork();
    if(pid<0)
    {
        perror("fork");
        exit(1);
    }

    if(pid>0)
    { /* parent */
        while(1);
    }

/* child */  // Zombie process

    return 0;
}


/**

#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);

pid_t waitpid(pid_t pid, int *status, int options);
< -1    回收指定进程组内的任意子进程
= -1    回收任意子进程
= 0     回收和当前调用waitpid一个组的所有子进程
> 0     回收指定ID的子进程


父进程调用wait或waitpid时可能会：

* 阻塞（如果它的所有子进程都还在运行）。
* 带子进程的终止信息立即返回（如果一个子进程已终止，正等待父进程读取其终止信息）。
* 出错立即返回（如果它没有任何子进程）。

这两个函数的区别是：
* 如果父进程的所有子进程都还在运行，调用wait将使父进程阻塞，而调用waitpid时如果在options参数中指定WNOHANG可以使父进程不阻塞而立即返回0。
* wait等待第一个终止的子进程，而waitpid可以通过pid参数指定等待哪一个子进程。


调用wait和waitpid
 1. 不仅可以获得子进程的终止信息，
 2. 还可以使父进程阻塞等待子进程终止，起到进程间同步的作用。

 如果参数status不是空指针，则子进程的终止信息通过这个参数传出，
 如果只是为了同步而不关心子进程的终止信息，可以将status参数指定为NULL。


 */


int main(void)
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) // child
    {
        int i;
        for (i = 3; i > 0; i--)
        {
            printf("This is the child\n");
            sleep(1);
        }
        exit(3);
    }
    else //pid > 0    parent
    {
        int stat_val;
        waitpid(pid, &stat_val, 0);
        if (WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        else if (WIFSIGNALED(stat_val))
            printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
    }

    return 0;
}



