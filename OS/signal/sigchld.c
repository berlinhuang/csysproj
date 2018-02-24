
/**
 *
 * SIGCHLD的产生条件:
 *
 * 子进程终止时
 * 子进程接收到SIGSTOP信号停止时
 * 子进程处在停止态，接受到SIGCONT后唤醒时
 **/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
void sys_err(char *str)
{
    perror(str);
    exit(1);
}

void do_sig_child(int signo)
{
    int status;
    pid_t pid;
    while ((pid = waitpid(0, &status, WNOHANG)) > 0)
    {
        if (WIFEXITED(status))
            printf("child %d exit %d\n", pid, WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("child %d cancel signal %d\n", pid, WTERMSIG(status));
    }
}

int main(void)
{
    pid_t pid;
    int i;

//阻塞SIGCHLD
    for (i = 0; i < 10; i++)
    {
        if ((pid = fork()) == 0)
            break;// child
        else if (pid < 0)
            sys_err("fork");
    }

    if (pid == 0) {// 10 个 child
        int n = 18;
        while (n--)
        {
            printf("child ID %d\n", getpid());//打印n次
            sleep(1);
        }
        return i;
    }
    else if (pid > 0)// parent
    {
//先设置捕捉
//再解除对SIGCHLD的阻塞

        struct sigaction act;
        act.sa_handler = do_sig_child;//SIGCHLD产生执行do_sig_child
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGCHLD, &act, NULL);//信号捕捉设定

        while (1)
        {
            printf("Parent ID %d\n", getpid());
            sleep(1);
        }
    }
    return 0;
}