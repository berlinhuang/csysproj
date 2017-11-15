# csysproj
> This repo describes the sys programming in linux using C language
## concurrent (处理并发的模型)

- multiprocess (多进程处理并发)
    > pid = fork()
- multithread (多线程处理并发)
    > pthread_create()
- multiplexing (I/O多路复用处理并发)

    1. select
    2. poll
    3. epoll 
> 每个进程/线程处理一个连接, 由于申请进程/线程会占用相当可观的系统资源，同时对于多进程/线程的管理会对系统造成压力，因此这种方案不具备良好的可扩展性

## Thread Synchronization (线程间同步)
> 每个进程中访问临界资源的那段代码称为[临界区]（Critical Section）

> [临界资源]是一次仅允许一个进程使用的共享资源

> 多线程访问共享的资源会产生竞争，所以要进行同步(线程排队)

> 多个线程读取常量不用同步，读取变量才要同步，即涉及线程要要对数据修改才同步
- compete   竞争 
    1. mutex     互斥量     加锁原语
    2. condition 条件变量    同步原语
    3. semaphore 信号量
    4. rwlock 


## IPC（进程间通信）
- pipe 匿名管道 用于有血缘关系的进程之间,通过fork来传递
- fifo 有名管道 解决无血缘关系的进程通信
- mmap  内存共享映射
- socket 套接字
    1. Unix域套接字 (Unix Domain Socket) (同一台主机上client和server之间通信)
    2. 网络套接字
        > socket( AF_UNIX, SOCK_STREAM, ... )   域间流式套接字
    
        > socket( AF_INET, SOCK_DGRAM, ... ) 网络数据包套接字
    - 建立套接字流程
    
        > server: socket() bind() listen() accept()...
        
        > client: socket() connect() ...
---

### C10K

> FreeBSD推出了kqueue，Linux推出了epoll，Windows推出了IOCP，Solaris推出了/dev/poll。这些操作系统提供的功能就是为了解决C10K问题。

> epoll技术的编程模型就是异步非阻塞回调，也可以叫做Reactor，事件驱动，事件轮循（EventLoop）。

> Nginx，libevent，node.js这些就是Epoll时代的产物

> 由于epoll, kqueue, IOCP每个接口都有自己的特点，程序移植非常困难，于是需要对这些接口进行封装，以让它们易于使用和移植，其中libevent库就是其中之一。跨平台，封装底层平台的调用，提供统一的 API，但底层在不同平台上自动选择合适的调用。

> 在处理IO的时候，阻塞和非阻塞都是同步IO。 只有使用了特殊的API才是异步IO。

<table>
    <tr>
        <td rowspan = "2">同步</td>
        <td colspan = "2" >IO multiplexing(select/poll/epoll)</td>
        <td rowspan = "2">异步</td>
        <td>Linux</td>
        <td>Windows</td>
        <td>.NET</td>
    </tr>
    <tr>
        <td>阻塞</td>
        <td>非阻塞</td>
        <td>AIO</td>
        <td>IOCP</td>
        <td>BeginInvoke/EndInvoke</td>
    </tr>
</table>



### Networlk Library

- C - libevent
- C++ - ACE/ASIO
- Java - Netty, Mina 游戏行业做服务器开发的Java程序员用的比较多的PRC框架
- Python -twisted
- Perl - POE
- Ruby - EventMachine



