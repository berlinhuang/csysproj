## 传输层协议( UNP 2nd chapter)
> TCP(传输控制协议)
- 有点像打电话，双方拿起电话互通身份之后就建立了连接，然后说话就行了，这边说的话那边保证听得到，并且是按说话的顺序听到的，说完话挂机断开连接。也就是说TCP传输的双方需要首先建立连接，之后由TCP协议保证数据收发的可靠性，丢失的数据包自动重发，上层应用程序收到的总是可靠的数据流，通讯之后关闭连接。
- TCP(SOCK_STREAM)协议是面向流的协议。流式套接字（SOCK_STREAM）
1. 是一种面向连接的的字节流协议：三次握手，四次挥手
2. 是一种可靠的数据传输服务：一端发送，对端确认，没收到会自动重传，数次重传失败才放弃
3. 接收端有序接收：接收的每个分节都关联一个序列号，非顺序到达可以据此排序。重复数据会被丢弃
4. 提供流量控制：用滑动窗口进行流量控制，指发送速率不要太快，要让接收方来得及接收
5. 提供拥塞控制：防止过多的数据注入网络中，使网络中路由器或链路不至过载
6. 全双工传输：

> UDP(用户数据报协议)
- 应用进程往UDP套接字(SOCK_DGRAM)写入一个消息，封装到一个UDP数据报，再封装成一个IP数据报
- 有点像寄信，写好信放到邮筒里，既不能保证信件在邮递过程中不会丢失，也不能保证信件是按顺序寄到目的地的。使用UDP协议的应用程序需要自己完成丢包重发、消息排序等工作
- UDP(SOCK_DGRAM数据报)是面向消息的协议，每个UDP段都是一条消息，应用程序必须以消息为单位提取数据，不能一次提取任意字节的数据，这一点和TCP是很不同的。
- 发送端调用了几次write，接收端必须用相同次数的read读完。UPD是基于报文的，在接收的时候，每次最多只能读取一个报文，报文和报文是不会合并的，如果缓冲区小于报文长度，则多出的部分会被丢弃。

1. 不面向连接：提供无连接服务，UDP客户与服务器不必存在任何长期的关系
2. 不保证可靠性：数据到达目的地，校验错误，或者传输中丢失，不会被源端重传
3. 不保证顺序： 各个数据报跨网络后顺序会变化
4. 不提供流量控制：


## IO模型（UNP 6th chapter）

> IO模型

- 阻塞式
- 非阻塞式
- IO复用
- 信号驱动IO
- 异步(asynchronous)IO


> IO操作（系统调用）一般分为两个阶段：
- 1.数据是否准备好。
- 2.将数据从内核空间拷贝到用户空间。

> 是否阻塞
- 前四种模型都是同步IO模型，因为第二阶段的IO操作(recvfrom)将阻塞进程。
- 真正能做到非阻塞的只有异步IO模型，两个阶段都没有阻塞。
- 这里所说的是否阻塞都是体现在第一个阶段。

## 非阻塞IO (UNP 16th chapter)

> 调用sock()创建套接字，默认的socket都是阻塞的

> 把一个套接字设置为非阻塞，就是告诉内核，当所请求的IO操作无法完成时，不要将进程睡眠，而是返回一个错误。

> 可能阻塞的 socket系统调用:
- 输入操作中的read readv recv recvfrom
- 输出操作中的write writev send sendto
- 接受连接中的accept
- 发起连接中的connect

#### 非阻塞accept
>原因：
- 服务器端select向服务器进程返回可读，但服务器要在一段时间后才能调用accpet
- 在服务器从select返回和调用accept之间，收到来看客户端的RST
- 这个已完成的连接从队列中删除（假设没有在其它已完成的连接存在）
- 服务器调用accept，但是由于没有已完成的连接，就阻塞了 

> 解决方法 ：
- 将监听套接口置为非阻塞 并且在后面的accept调用中忽略 下面错误:
    - \#define EWOULDBLOCK	EAGAIN	//Operation would block 
    - \#define	ECONNABORTED	103	//Software caused connection abort
    - \#define	EPROTO		71	// Protocol error 

#### 非阻塞connect
> 三种用途
1. 我们可以在三路握手的同时做一些其它的处理。
2. 可以用这种技术同时建立多个连接。
3. 由于我们使用select来等待连接的完，因此我们可以给select设置一个时间限制，从而缩短connect 的超时时间。

> 实现步骤
1. 创建socket，返回套接口描述符；
2. 调用fcntl把套接口描述符设置成非阻塞；
3. 调用非阻塞connect；
4. 判断连接是否成功建立。




## LT ET

> 水平触发： 只要能读写，每次调用epoll_wait都会通知

> 边缘触发： 上次没有读写完，下次调用epoll_wait不会通知



<table>
    <tr>
        <td>select/poll</td><td>水平触发</td>
    </tr>
    <tr>
        <td>信号驱动IO</td><td>边缘触发</td>
    </tr>
    <tr>
        <td>epoll</td><td>水平触发（默认）/边缘触发</td>
    </tr>
</table>

> epoll_wait()返回必定是已就绪的文件描述符，listenfd阻塞不阻塞accept都会立即返回


> LT non-blocking listenfd

> ET non-blicking listenfd


> LT blocking connfd

> LT non-blocking connfd

> ET blocking connfd

> ET non-blocking connfd 


