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
- Reactor = non-blocking IO + IO multiplexing
    > muduo
    
    > lighttpd
    
    > libevent
    
    > ACE
    
    > Java NIO, Netty
    
    > POE
    
    > Twisted
    
    > Reactor释义"反应堆"，是一种事件驱动机制。和普通函数调用的不同之处在于：应用程序不是主动的调用某个API完毕处理。而是恰恰相反。
    
    > Reactor逆置了事件处理流程，应用程序须要提供对应的接口并注冊到Reactor上，假设对应的时间发生，Reactor将主动调用应用程序注冊的接口，这些接口又称为"回调函数"。
   
- Proactor
    
    > boost.asio
    
    > Windows IOCP

---
### Networlk Library

- C - libevent
- C++ - ACE/ASIO
- Java - Netty, Mina 游戏行业做服务器开发的Java程序员用的比较多的PRC框架
- Python -twisted
- Perl - POE
- Ruby - EventMachine



