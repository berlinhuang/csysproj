//
// Created by root on 17-11-8.
//

/* wrap.c */
#include "wrap.h"

void perr_exit(const char *s)
{
    perror(s);
    exit(1);
}
/**
 *
 * @param family
 * 对于IPv4，domain参数指定为AF_INET (AF: address family   INET:internet)
 * AF_INET6 与上面类似，不过是来用IPv6的地址
 * AF_UNIX 本地协议，使用在Unix和Linux系统上，一般都是当客户端和服务器在同一台及其上的时候使用
 * @param type
 * 对于TCP协议，type参数指定为SOCK_STREAM，表示面向流的传输协议
 * 如果是UDP协议，则type参数指定为SOCK_DGRAM，表示面向数据报的传输协议
 * @param protocol
 * 0 默认协议
 * @return 成功返回一个新的文件描述符，失败返回-1，设置errno
 */
int Socket(int family, int type, int protocol)
{
    int n;
    if ( (n = socket(family, type, protocol)) < 0)
        perr_exit("socket error");
    return n;
}
/**
 * 将参数sockfd和addr绑定在一起，使sockfd这个用于网络通讯的文件描述符监听sa所描述的地址和端口号
 * @param fd socket文件描述符
 * @param sa 构造出IP地址加端口号
 * @param salen sizeof(sa)长度
 * @return  成功返回0，失败返回-1, 设置errno
 *
struct sockaddr_in servaddr;
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(8000);
 例：Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));//绑定
 */
void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (bind(fd, sa, salen) < 0)
        perr_exit("bind error");
}

/**
 * 声明sockfd处于监听状态，并且最多允许有backlog个客户端处于连接待状态，如果接收到更多的连接请求就忽略
 * @param fd socket文件描述符
 * @param backlog 排队建立3次握手队列和刚刚建立3次握手队列的链接数和   cat /proc/sys/net/ipv4/tcp_max_syn_backlog
 * @return 成功返回0，失败返回-1
 */
void Listen(int fd, int backlog)
{
    if (listen(fd, backlog) < 0)
        perr_exit("listen error");
}
/**
 * 三方握手完成后，服务器调用accept()接受连接，如果服务器调用accept()时还没有客户端的连接请求，就阻塞等待直到有客户端连接上来
 * @param fd 先前的监听文件描述符
 * @param sa 传出参数，返回链接客户端地址信息，含IP地址和端口号
 * @param salenptr 传入传出参数（值-结果）,传入sizeof(addr)大小，函数返回时返回真正接收到地址结构体的大小
 * @return 成功返回一个新的socket文件描述符，用于和客户端通信，失败返回-1，设置errno        最后关闭connfd断开连接，而不关闭listenfd
 *
 while (1) {
    cliaddr_len = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &cliaddr_len);
    n = read(connfd, buf, MAXLINE);
    ......
    close(connfd);
 }
 */
int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
    int n;
    again:
    if ( (n = accept(fd, sa, salenptr)) < 0) {
        if ((errno == ECONNABORTED) || (errno == EINTR))
            goto again;
        else
            perr_exit("accept error");
    }
    return n;
}

/**
 * 客户端需要调用connect()连接服务器，connect和bind的参数形式一致，区别在于bind的参数是自己的地址，而connect的参数是对方的地址
 * @param fd
 * @param sa 传入参数，指定服务器端地址信息，含IP地址和端口号
 * @param salen 传入参数,传入sizeof(sa)大小
 * @return 成功返回0，失败返回-1，设置errno         如果对方未响应，要隔6s，重发尝试，可能要等待75s的尝试并最终返回超时，才得知连接失败。
 */

//// 即使是一次尝试成功，也会等待几毫秒到几秒的时间，如果此期间有其他事务要处理，则会白白浪费时间，而用非阻塞的connect 则可以做到并行，提高效率。
//// 而通常，非阻塞的connect 函数与 select 函数配合使用：在一个TCP套接口被设置为非阻塞之后调用connect，
//// connect （函数本身返回-1）会立即返回EINPROGRESS或EWOULDBLOCK错误，表示连接操作正在进行中，但是仍未完成；同时TCP的三路握手操作继续进行；
//// 在这之后，我们可以调用select来检查这个链接是否建立成功。若建立连接成功，select的结果中该描述符可写；若失败，则可写可读，此时可以使用getsockopt获取错误信息。
void Connect(int fd, const struct sockaddr *sa, socklen_t salen)
{
    if (connect(fd, sa, salen) < 0)
        perr_exit("connect error");
}

/**
 * #include <unistd.h>
 * 从打开的设备或文件中读取数据
 * @param fd
 * @param ptr
 * @param nbytes 请求读取的字节数
 * @return  注意返回值类型是ssize_t，表示有符号的size_t，这样既可以返回正的字节数、0（表示到达文件末尾）也可以返回负值-1（表示出错） 并设置errno，如果在调read之前已到达文件末尾，则这次read返回0
 */
ssize_t Read(int fd, void *ptr, size_t nbytes)
{
    ssize_t n;
    again:
    if ( (n = read(fd, ptr, nbytes)) == -1) {
        if (errno == EINTR)
            goto again;
        else
            return -1;
    }
    return n;
}
/**
 *
 * @param fd
 * @param ptr
 * @param nbytes
 * @return 成功返回写入的字节数，出错返回-1并设置errno
 */
ssize_t Write(int fd, const void *ptr, size_t nbytes)
{
    ssize_t n;
    again:
    if ( (n = write(fd, ptr, nbytes)) == -1) {
        if (errno == EINTR)
            goto again;
        else
            return -1;
    }
    return n;
}
/**
 *
 * @param fd
 * @return 成功返回0，出错返回-1并设置errno
 */
void Close(int fd)
{
    if (close(fd) == -1)
        perr_exit("close error");
}

ssize_t Readn(int fd, void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char
            *ptr;
    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nread = read(fd, ptr, nleft)) < 0) {
            if (errno == EINTR)
                nread = 0;
            else
                return -1;
        } else if (nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    return n - nleft;
}

ssize_t Writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;
    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;
            else
                return -1;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return n;
}

static ssize_t my_read(int fd, char *ptr)
{
    static int read_cnt;
    static char *read_ptr;
    static char read_buf[100];
    if (read_cnt <= 0) {
        again:
        if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return -1;
        } else if (read_cnt == 0)
            return 0;
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;
    return 1;
}

ssize_t Readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char c, *ptr;
    ptr = vptr;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;
        } else if (rc == 0) {
            *ptr = 0;
            return n - 1;
        } else
            return -1;
    }
    *ptr = 0;
    return n;
}


/**
 *
 * @param open_max
 * @return
 */
int epollcreate( int open_max )
{
    int efd = epoll_create(open_max);//创建epoll句柄 OPEN_MAX个文件描述符                                         epoll_create
    if (efd == -1)
        perr_exit("epoll_create");
    return efd;
}

/**
 *
 * @param efd
 * @param op
 * @param fd
 * @param tep
 * @return
 */
void epollctl(int efd, int op, int fd, struct epoll_event *tep)
{
    int res = epoll_ctl(efd, EPOLL_CTL_ADD, fd, tep);//控制某个epoll监控的文件描述符上的事件 注册 修改 删除     epoll_ctl
    if (res == -1)
        perr_exit("epoll_ctl");
}
/**
 *
 * @param efd
 * @param events 冲内核得到的事件集合
 * @param maxevents 告诉内核ep多大，不能大于创建epoll_create(int size) 中size的大小
 * @param timeout
 * @return
 */
int epollwait(int efd, struct epoll_event *events, int maxevents, int timeout ){
    int nready = epoll_wait(efd, events, maxevents, timeout); //内存拷贝，利用mmap()文件映射内存加速与内核空间的消息传递；即epoll使用mmap减少复制开销  epoll_wait
    if (nready == -1) //-1表示阻塞
        perr_exit("epoll_wait");
    return nready;
};