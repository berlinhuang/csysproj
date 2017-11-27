[1. netstat](#1)

[2. tcpdump](#2)

[3. ipcs](#3)

[4. ipcrm](#4)

[5. ps top ](#5)

-   [5.1 ps](#5.1)
    
-   [5.2 top](#5.2)
    

<h3 id = "1"> netstat</h3>

- \-a (all)显示所有选项，默认不显示LISTEN相关
- \-t (tcp)仅显示tcp相关选项
- \-u (udp)仅显示udp相关选项
- \-n 拒绝显示别名，能显示数字的全部转化成数字。
- \-l 仅列出有在Listen (监听) 的服務状态
- \-p 显示建立相关链接的程序名
- \-r 显示路由信息，路由表
- \-e 显示扩展信息，例如uid等
- \-s 按各个协议进行统计
- \-c 每隔一个固定时间，执行该netstat命令。
- 提示：LISTEN和LISTENING的状态只有用-a或者-l才能看到
> netstat -ano   

| Proto |Recv-Q| Send-Q| Local Address |  Foreign Address  | State |  Timer       |
| :-----|:----:| -----:|:-------------:| -----------------:|:-----:| ------------:|
| tcp   |    0 |   0   |127.0.0.1:6942 |     0.0.0.0:*     | LISTEN|关闭 (0.00/0/0)|
| udp   |    0 |   0   |0.0.0.0:41961  |     0.0.0.0:*     |       |关闭 (0.00/0/0)|

> netstat -tulp

> netstat -lnp

<h3 id = "2"> tcpdump</h3>

> tcpdump [-AennqX] [-i 接口] [-w 储存档名] [-c 次数]  [-r 档案] [所欲撷取的封包数据格式]

- \-A ：封包的内容以 ASCII 显示，通常用来捉取 WWW 的网页封包资料。
- \-e ：使用资料连接层 (OSI 第二层) 的 MAC 封包数据来显示；
- \-nn：直接以 IP 及 port number 显示，而非主机名与服务名称
- \-q ：仅列出较为简短的封包信息，每一行的内容比较精简
- \-X ：可以列出十六进制 (hex) 以及 ASCII 的封包内容，对于监听封包内容很有用
- \-i ：后面接要『监听』的网络接口，例如 eth0, lo, ppp0 等等的界面；
- \-w ：如果你要将监听所得的封包数据储存下来，用这个参数就对了！后面接档名
- \-r ：从后面接的档案将封包数据读出来。那个『档案』是已经存在的档案，并且这个『档案』是由 -w 所制作出来的。
- \-c ：监听的封包数，如果没有这个参数， tcpdump 会持续不断的监听， 直到使用者输入 [ctrl]-c 为止。

> 所欲撷取的封包数据格式：我们可以专门针对某些通讯协议或者是 IP 来源进行封包撷取，那就可以简化输出的结果，并取得最有用的信息。常见的表示方法有：
- 'host foo', 'host 127.0.0.1' ：针对单部主机来进行封包撷取
- 'net 192.168' ：针对某个网域来进行封包的撷取；
- 'src host 127.0.0.1' 'dst net 192.168'：同时加上来源(src)或目标(dst)限制
- 'tcp port 21'：还可以针对通讯协议侦测，如 tcp, udp, arp, ether 等
- 还可以利用 and 与 or 来进行封包数据的整合显示呢！

> tcpdump -i eth0 -nn  //以IP与port number捉下eth0这个网络卡上的封包，持续3秒

- tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
- listening on eth0, link-type EN10MB (Ethernet), capture size 65535 bytes
- 17:01:47.360523 IP 192.168.1.101.1937 > 192.168.1.100.22: Flags [.], ack 196, win 65219, 
- 17:01:47.362139 IP 192.168.1.100.22 > 192.168.1.101.1937: Flags [P.], seq 196:472, ack 1,
- 17:01:47.363201 IP 192.168.1.100.22 > 192.168.1.101.1937: Flags [P.], seq 472:636, ack 1,
- 17:01:47.363328 IP 192.168.1.101.1937 > 192.168.1.100.22: Flags [.], ack 636, win 64779,
> <==按下 [ctrl]-c 之后结束
- 6680 packets captured              <==捉下来的封包数量
- 14250 packets received by filter   <==由过滤所得的总封包数量
- 7512 packets dropped by kernel     <==被核心所丢弃的封包


- 17:01:47.362139：这个是此封包被撷取的时间，『时:分:秒』的单位；
- IP：透过的通讯协议是 IP ；
- 192.168.1.100.22 > ：传送端是192.168.1.100这个IP，而传送的port number为22，你必须要了解的是，那个大于 (>) 的符号指的是封包的传输方向喔！
- 192.168.1.101.1937：接收端的IP是192.168.1.101， 且该主机开启port 1937来接收；
- [P.], seq 196:472：这个封包带有PUSH的数据传输标志， 且传输的数据为整体数据的 196~472 byte；
- ack 1：ACK的相关资料。

>  tcpdump -i eth0 -nn port 21

- 这样就仅提出 port 21 的信息而已，且仔细看的话，你会发现封包的传递都是双向的， client 端发出『要求』而 server 端则予以『响应』，所以，当然是有去有回啊！ 而我们也就可以经过这个封包的流向来了解到封包运作的过程

> 我们先在一个终端机窗口输入『 tcpdump -i lo -nn 』 的监听，
  再另开一个终端机窗口来对本机 (127.0.0.1) 登入『ssh localhost』 三向交握

> tcpdump -i lo -nn
 - 1 tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
 - 2 listening on lo, link-type EN10MB (Ethernet), capture size 96 bytes
 - 3 11:02:54.253777 IP 127.0.0.1.32936 > 127.0.0.1.22: S 933696132:933696132(0) 
   win 32767 <mss 16396,sackOK,timestamp 236681316 0,nop,wscale 2>
 - 4 11:02:54.253831 IP 127.0.0.1.22 > 127.0.0.1.32936: S 920046702:920046702(0) 
   ack 933696133 win 32767 <mss 16396,sackOK,timestamp 236681316 236681316,nop,
   wscale 2>
 - 5 11:02:54.253871 IP 127.0.0.1.32936 > 127.0.0.1.22: . ack 1 win 8192 <nop,
   nop,timestamp 236681316 236681316>
 - 6 11:02:54.272124 IP 127.0.0.1.22 > 127.0.0.1.32936: P 1:23(22) ack 1 win 8192 
   <nop,nop,timestamp 236681334 236681316>
 - 7 11:02:54.272375 IP 127.0.0.1.32936 > 127.0.0.1.22: . ack 23 win 8192 <nop,
   nop,timestamp 236681334 236681334>


- 第 3 行显示的是『来自 client 端，带有 SYN 主动联机的封包』，
- 第 4 行显示的是『来自 server 端，除了响应 client 端之外(ACK)，还带有 SYN 主动联机的标志；
- 第 5 行则显示 client 端响应 server 确定联机建立 (ACK)
- 第 6 行以后则开始进入数据传输的步骤。

> 使用 tcpdump 在 router 上面监听『明码』的传输数据时， 例如 FTP 传输协议，你觉得会发生什么问题呢？ 我们先在主机端下达『 tcpdump -i lo port 21 -nn -X 』然后再以 ftp 登入本机，并输入账号与密码， 结果你就可以发现如下的状况：

> tcpdump -i lo -nn -X 'port 21'

- 0x0000:  4500 0048 2a28 4000 4006 1286 7f00 0001  E..H*(@.@.......
- 0x0010:  7f00 0001 0015 80ab 8355 2149 835c d825  .........U!I.\.%
- 0x0020:  8018 2000 fe3c 0000 0101 080a 0e2e 0b67  .....<.........g
- 0x0030:  0e2e 0b61 3232 3020 2876 7346 5450 6420  ...a220.(vsFTPd.
- 0x0040:  322e 302e 3129 0d0a                      2.0.1)..

> 如何使用 tcpdump 监听 (1)来自 eth0 适配卡且 (2)通讯协议为 port 22 ，(3)封包来源为 192.168.1.101 的封包资料？

> tcpdump -i eth0 -nn 'port 22 and src host 192.168.1.101'




---


1. 数据传输，一个进程需要将它的数据发送给另一个进程，发送的数据量在一个字节到几M之间；
2. 共享数据，多个进程想要操作共享数据，一个进程对数据的修改，其他进程应该立刻看到；
3. 通知事件，一个进程需要向另一个或一组进程发送消息，通知它们发生了某件事情；
4. 资源共享，多个进程之间共享同样的资源。为了做到这一点，需要内核提供锁和同步机制；
5. 进程控制，有些进程希望完全控制另一个进程的执行（如Debug进程），此时控制进程希望能够拦截另一个进程的所有陷入和异常，并能够及时知道它的状态改变。

<h3 id = "3"> ipcs(state) 提供IPC设备的信息 包括共享内存，消息队列，信号</h3>  

> ipcs [resource-option] [output-format]

> ipcs [resource-option] -i id

- resource选项：
    - ipcs -m   查看系统共享内存信息
    - ipcs -q   查看系统消息队列信息
    - ipcs -s   查看系统信号量信息
    - ipcs [-a] 系统默认输出信息，显示系统内所有的IPC信息

- 输出格式控制：
    - ipcs -c　　查看IPC的创建者和所有者
    - ipcs -l　　查看IPC资源的限制信息
    - ipcs -p　　查看IPC资源的创建者和使用的进程ID
    - ipcs -t　　查看最新调用IPC资源的详细时间
    - ipcs -u　　查看IPC资源状态汇总信息
- 额外格式控制：　以人类可以阅读的方式显示size
    - ipcs -l --human

<h3 id = "4"> ipcrm(remove) </h3>  

> 通过指定ID删除IPC资源，同时将与IPC对象关联的数据一并删除，只有超级用户或IPC资源创建者能够删除

- ipcrm -M shmkey   移除用shmkey创建的    共享内存段
- ipcrm -m shmid    移除用shmid标识的     共享内存段
- ipcrm -S semkey   移除用semkey创建的    信号量
- ipcrm -s semid    移除用semid标识的     信号量
- ipcrm -Q msgkey   移除用msgkey创建的    消息队列
- ipcrm -q msgid    移除用msgid标识的     消息队列

---

<h3 id = "5"> ps top </h3>  
<h4 id='5.1'> ps </h4>
1. UNIX 风格，选项可以组合在一起，并且选项前必须有“-”连字符 ps -ef
2. BSD 风格，选项可以组合在一起，但是选项前不能有“-”连字符 ps aux
3. GNU 风格的长选项，选项前有两个“-”连字符

- 选项与参数：
    - -A  ：所有的 process 均显示出来，与 -e 具有同样的效用；
    - -a  ：不与 terminal 有关的所有 process ；
    - -u  ：有效使用者 (effective user) 相关的 process ；
    - x   ：通常与 a 这个参数一起使用，可列出较完整资讯
- 输出格式规划：
    - l   ：较长、较详细的将该 PID 的的资讯列出；
    - j   ：工作的格式 (jobs format)
    - -f  ：做一个更为完整的输出。


- ps 
- ps -ax    //-a 代表 all。同时加上x参数会显示没有控制终端的进程
- ps -ax | less //less命令和管道来使用
- ps -u berlin //用户’berlin’的进程
- ps -aux | less //通过cpu和内存使用来过滤进程
- ps -aux --sort -pcpu | less //根据 CPU使用 来升序排序
- ps -aux --sort -pmem | less //根据 内存使用 来升序排序
- ps -C getty     //使用 -C 参数，后面跟你要找的进程的名字    
- ps -L 1213     //特定进程的线程，可以使用-L 参数，后面加上特定的PID 
  
<h4 id='5.2'> top </h4>

> top [-d 数字] | top [-bnp]   
            
- 选项与参数：
    - -d  ：后面可以接秒数，就是整个程序画面升级的秒数。默认是 5 秒；
    - -b  ：以批量的方式运行 top ，还有更多的参数可以使用喔！通常会搭配数据流重导向来将批量的结果输出成为文件。
    - -n  ：与 -b 搭配，意义是，需要进行几次 top 的输出结果。
    - -p  ：指定某些个 PID 来进行观察监测而已。
    
> 将top的资讯进行2次，然后将结果输出到/tmp/top.txt
- top -b -n 2 > /tmp/top.txt  

> 我们自己的bash PID可由$$变量取得，请使用top持续观察该PID : 
- echo $$
- top -d 2 -p 13639