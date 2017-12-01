> TCP是一种面向连接的、可靠的协议
- 有点像打电话，双方拿起电话互通身份之后就建立了连接，然后说话就行了，这边说的话那边保证听得到，并且是按说话的顺序听到的，说完话挂机断开连接。也就是说TCP传输的双方需要首先建立连接，之后由TCP协议保证数据收发的可靠性，丢失的数据包自动重发，上层应用程序收到的总是可靠的数据流，通讯之后关闭连接。

- TCP(流)协议是面向流的协议。

> UDP协议不面向连接，也不保证可靠性
- 有点像寄信，写好信放到邮筒里，既不能保证信件在邮递过程中不会丢失，也不能保证信件是按顺序寄到目的地的。使用UDP协议的应用程序需要自己完成丢包重发、消息排序等工作

- 而UDP(数据报)是面向消息的协议，每个UDP段都是一条消息，应用程序必须以消息为单位提取数据，不能一次提取任意字节的数据，这一点和TCP是很不同的。
- 发送端调用了几次write，接收端必须用相同次数的read读完。UPD是基于报文的，在接收的时候，每次最多只能读取一个报文，报文和报文是不会合并的，如果缓冲区小于报文长度，则多出的部分会被丢弃。
## 阻塞 非阻塞

> IO操作（系统调用）一般分为两个阶段：1.数据是否准备好。2.将数据从内核空间拷贝到用户空间。

> 真正能做到非阻塞的只有异步IO模型，两个阶段都没有阻塞。

> 这里所说的是否阻塞都是体现在第一个阶段。

> 调用sock()创建套接字，默认的socket都是阻塞的

> 把一个套接字设置为非阻塞，就是告诉内核，当所请求的IO操作无法完成时，不要将进程睡眠，而是返回一个错误。

> 可能阻塞socket的系统调用:
- 输入操作中的read readv recv recvfrom
- 输出操作中的write writev send sendto
- 接受连接中的accept
- 发起连接中的connect

#### 非阻塞accept

> 服务器端select向服务器进程返回可读，但服务器要在一段时间后才能调用accpet
> 在服务器从select返回和调用accept之间，收到来看客户端的RST
> 这个已完成的连接从队列中删除（假设没有在其它已完成的连接存在）
> 服务器调用 accept，但是由于没有已完成的连接，就阻塞了 

> 解决方法 ：
> 将监听套接口置为非阻塞 并且在后面的accept调用中忽略 下面错误
- \#define EWOULDBLOCK	EAGAIN	//Operation would block 
- \#define	ECONNABORTED	103	//Software caused connection abort
- \#define	EPROTO		71	// Protocol error 

#### 非阻塞connect
> 三种用途
1. 我们可以在三路握手的同时做一些其它的处理。
2. 可以用这种技术同时建立多个连接
3. 由于我们使用select 来等待连接的完，因此我们可以给select设置一个时间限制，从而缩短connect 的超时时间。

> 实现步骤
1. 创建socket，返回套接口描述符；
2. 调用fcntl 把套接口描述符设置成非阻塞；
3. 调用connect 开始建立连接；
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


