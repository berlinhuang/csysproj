- 线程，有时被称为轻量级进程(Lightweight Process，LWP).一个标准的线程由线程ID，当前指令指针(PC)，寄存器集合和堆栈组成。
- 线程是cpu调度的基本单位
- 在linux下，线程最是小的执行单位；进程是最小的分配(管理)资源单位


> 线程间共享资源
1. 文件描述符表
2. 每种信号的处理方式
3. 当前工作目录
4. 用户ID和组ID
5. 内存地址空间

> 线程间非共享资源
1. 线程id
2. 处理器现场和栈指针(内核栈)
3. 独立的栈空间(用户空间栈)
4. errno变量
5. 信号屏蔽字
6. 调度优先级

> 32bit linux os 进程虚拟地址空间
<table>
    <caption>32bit linux os 进程虚拟地址空间</caption>
    <tr><td>1G内核空间</br>0xFFFFFFFF</br>|</br>0xC0000000</td><td>内存管理</br>网络管理</br>进程管理</br>驱动管理</td><td>以太网协议</br>TCP</br> IP</td></tr>
    <tr><td rowspan = "11">3G用户空间</br>0xBFFFFFFF</br>|</br>0x00000000</td><td>环境变量</td><td rowspan = "11">socket </br>application</td></tr>
    <tr><td>命令行参数</td><tr>
    <tr><td>栈</td></tr>
    <tr><td></td></tr>
    <tr><td>共享库</td></tr>
    <tr><td></td></tr>
    <tr><td>堆</td></tr>
    <tr><td>bss</td></tr>
    <tr><td>data</td></tr>
    <tr><td>text</td></tr>
</table>

---

> 进程地址空间:
- 命令行参数
- 环境变量
- stack: 局部变量 函数调用时的参数   从高到低分配
- 共享库: 
- heap: 进程运行中被动态分配的内存段 大小并不固定 malloc free  从低到高分配
- bss(Block Started by Symbol): 未初始化的全局变量(静态内存分配)
- data: 已初始化的全局变量(静态内存分配)
- text: 存放程序执行代码 包含一些只读的常数变量，例如字符串常量等 C++成员函数(多个对象共享) 

---
> Linux使用了四级保护机制：
- 0级供 操作系统内核使用；
- 1级供 系统调用使用；
- 2级供 共享库用；
- 3级供 应用程序使用

---
> IPC（进程间通信）

- pipe 匿名管道 用于有血缘关系的进程之间,通过fork来传递
- fifo 有名管道(named pipe) 解决无血缘关系的进程通信


- System V message queue
- Posix message queue


- Sun RPC (s可用在同一主机上客户端和服务器之间的消息传递)

- 共享内存
    - mmap 内存共享映射
    - shm System V版本的共享内存
    
    
- socket 套接字
    - Unix域套接字 (Unix Domain Socket) (同一台主机上client和server之间通信)
    - 网络套接字
        - socket( AF_UNIX, SOCK_STREAM, ... )   域间流式套接字
        - socket( AF_INET, SOCK_DGRAM, ... ) 网络数据包套接字




---
> 进程信息共享
1. 共享文件系统: read write lseek..., 需要同步 
2. 共享内核信息: 管道(调用pipe函数时在内核中开辟一块缓冲区), System V mq
3. 共享内存: 两个不同进程A、B共享内存的意思是，同一块物理内存被映射到进程A、B各自的进程地址空间
---

> 共享内存
1. 共享内存允许两个或更多进程共享一个给定的存储区，因为数据不需要再客户进程和服务进程之间复制。所以这是最快的一种IPC。
2. 使用共享内存时需要注意：多个进程对共享内存的同步访问。
3. 通常用信号量实现对共享内存的同步访问。

> 共享内存段的最大限制: cat /proc/sys/kernel/shmmax 

> ELF 是什么 ？其大小与程序中全局变量的是否初始化有什么关系（注意未初始化的数据放在 bss 段）

Linux ELF  ELF = Executable and Linkable Format ，可执行连接格式

> linux查看修改线程默认栈空间大小 ulimit -s
---
