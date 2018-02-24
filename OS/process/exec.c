#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> //perror()

int main(void)
{
    execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
    perror("exec ps");
//    execlp("ls","ls","-l", "/home/berlin/code/",(char*)0);
    exit(1);
}

/**
 * 注意在调用execlp时传了两个“ps”参数，
 * 第一个“ps”是程序名，execlp函数要在PATH环境变量中找到这个程序并执行它，
 * 而第二个“ps”是第一个命令行参数，execlp函数并不关心它的值，只是简单地把它传给ps程序，ps程序可以通过main函数的argv[0]取到这个参数
 */


/**
#include <unistd.h>
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);


l 命令行参数列表
p 搜素file时使用path变量
v 使用命令行参数数组
e 使用环境变量数组,不使用进程原有的环境变量，设置新加载程序运行的环境变量


 不带字母p（表示path）的exec函数:
    第一个参数必须是程序的相对路径或绝对路径，例如“/bin/ls”或“./a.out”，而不能是“ls”或“a.out”。

 对于带字母p的函数：
    如果参数中包含/，则将其视为路径名。
    否则视为不带路径的程序名，在PATH环境变量的目录列表中搜索这个程序

 带有字母l（表示list）的exec函数要求将新程序的每个命令行参数都当作一个参数传给它，命令行参数的个数是可变的，
 因此函数原型中有…，…中的最后一个可变参数应该是NULL，起sentinel的作用。

 对于带有字母v（表示vector）的函数，则应该先构造一个指向各参数的指针数组，然后将该数组的首地址当作参数传给它，
 数组中的最后一个指针也应该是NULL，就像main函数的argv参数或者环境变量表一样。

 对于以e（表示environment）结尾的exec函数，可以把一份新的环境变量表传给它，其他exec函数仍使用当前的环境变量表执行新程序。


 exec调用举例如下：
    char *const ps_argv[] ={"ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL};
    char *const ps_envp[] ={"PATH=/bin:/usr/bin", "TERM=console", NULL};

    execl("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);
    execv("/bin/ps", ps_argv);
    execle("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);
    execve("/bin/ps", ps_argv, ps_envp);
    execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);  //  ps -o pid,ppid,pgrp,session,tpgid,comm
    execvp("ps", ps_argv);

 由于exec函数只有错误返回值，只要返回了一定是出错了，所以不需要判断它的返回值，直接在后面调用perror即可

 **/