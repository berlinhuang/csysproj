[1. netstat](#1)

[2. tcpdump](#2)

[3. ipcs](#3)

[4. ipcrm](#4)

[5. ps top ](#5)

-   [5.1 ps](#5.1)
    
-   [5.2 top](#5.2)

[6. sed awk](#6)    

-   [6.1 sed](#6.1)
    
-   [6.2 awk](#6.2)

-   [6.3 正规表达式](#6.3)

[7. cpu disk monitor](#7)

---
<h3 id = "1"> 1. netstat</h3>

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
- 网络套接字

| Proto |Recv-Q| Send-Q| Local Address |  Foreign Address  | State |  Timer       |
| :-----|:----:| -----:|:-------------:| -----------------:|:-----:| ------------:|
| tcp   |    0 |   0   |127.0.0.1:6942 |     0.0.0.0:*     | LISTEN|关闭 (0.00/0/0)|
| udp   |    0 |   0   |0.0.0.0:41961  |     0.0.0.0:*     |       |关闭 (0.00/0/0)|

- Unix域套接字

| Proto |Refcnt| Flags | type    |  state     | I-Node |  Path       |
| :-----|:----:| -----:|:-------:| ----------:|:-----:| ------------:|
| unix  |  2   |[ACC]  | 流      |  listening | 19793|@/tmp/.ICE-unix/1566|
| unix  |  2   |[]     | 数据报   |           | 19343|/run/user/1000/systemd/notify|

> netstat -tulp

> netstat -lnp

<h3 id = "2">2. tcpdump</h3>

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
> 共享内存作用

1. 数据传输，一个进程需要将它的数据发送给另一个进程，发送的数据量在一个字节到几M之间；
2. 共享数据，多个进程想要操作共享数据，一个进程对数据的修改，其他进程应该立刻看到；
3. 通知事件，一个进程需要向另一个或一组进程发送消息，通知它们发生了某件事情；
4. 资源共享，多个进程之间共享同样的资源。为了做到这一点，需要内核提供锁和同步机制；
5. 进程控制，有些进程希望完全控制另一个进程的执行（如Debug进程），此时控制进程希望能够拦截另一个进程的所有陷入和异常，并能够及时知道它的状态改变。

<h3 id = "3"> 3. ipcs(state) 提供IPC设备的信息 包括共享内存，消息队列，信号</h3>  

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

<h3 id = "4"> 4. ipcrm(remove) </h3>  

> 通过指定ID删除IPC资源，同时将与IPC对象关联的数据一并删除，只有超级用户或IPC资源创建者能够删除

- ipcrm -M shmkey   移除用shmkey创建的    共享内存段
- ipcrm -m shmid    移除用shmid标识的     共享内存段
- ipcrm -S semkey   移除用semkey创建的    信号量
- ipcrm -s semid    移除用semid标识的     信号量
- ipcrm -Q msgkey   移除用msgkey创建的    消息队列
- ipcrm -q msgid    移除用msgid标识的     消息队列

---

<h3 id = "5"> 5. ps top </h3>  
<h4 id='5.1'> 5.1 ps </h4>

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
- ps -aux --sort -pcpu | less //根据 CPU使用 来递减排序
- ps -aux --sort -pmem | less //根据 内存使用 来递减排序
- ps -aux --sort=-pcpu | less // cpu递减
- ps -aux --sort=-pcpu,+pmem |less // cpu递减 mem递增
- ps -C getty     //使用 -C 参数，后面跟你要找的进程的名字    
- ps -L 1213     //特定进程的线程，可以使用-L 参数，后面加上特定的PID 
- ps -eLf | grep "..." // 查看线程

<h4 id='5.2'> 5.2 top </h4>

> top [-d 数字] | top [-bnp]   
            
- 选项与参数：
    - -d  ：后面可以接秒数，就是整个程序画面升级的秒数。默认是 5 秒；
    - -b  ：以批量的方式运行 top ，还有更多的参数可以使用喔！通常会搭配数据流重导向来将批量的结果输出成为文件。
    - -n  ：与 -b 搭配，意义是，需要进行几次 top 的输出结果。
    - -p  ：指定某些个 PID 来进行观察监测而已。
    - -c  ：显示进程的完整命令
    
> 将top的资讯进行2次，然后将结果输出到/tmp/top.txt
- top -b -n 2 > /tmp/top.txt  

> 我们自己的bash PID可由$$变量取得，请使用top持续观察该PID : 
- echo $$
- top -d 2 -p 13639


---
<h3 id = "6"> 6. sed awk </h3>  
<h4 id='6.1'> 6.1 sed (stream editor) </h4> 

> sed [-nefr] [动作]

- 选项与参数：
    - -n  ：使用安静(silent)模式。在一般 sed 的用法中，所有来自 STDIN 
      的数据一般都会被列出到萤幕上。但如果加上 -n 参数后，则只有经过
      sed 特殊处理的那一行(或者动作)才会被列出来。
    - -e  ：直接在命令列模式上进行 sed 的动作编辑；
    - -f  ：直接将 sed 的动作写在一个文件内， -f filename 则可以运行 filename 内的 
      sed 动作；
    - -r  ：sed 的动作支持的是延伸型正规表示法的语法。(默认是基础正规表示法语法)
    - -i  ：直接修改读取的文件内容，而不是由萤幕输出。

- 动作说明：  [n1[,n2]]function
    - n1, n2 ：不见得会存在，一般代表『选择进行动作的行数』，举例来说，如果我的动作
         是需要在 10 到 20 行之间进行的，则『 10,20[动作行为] 』

- function 有底下这些咚咚：
    - a   ：新增， a 的后面可以接字串，而这些字串会在新的一行出现(目前的下一行)～
    - c   ：取代， c 的后面可以接字串，这些字串可以取代 n1,n2 之间的行！
    - d   ：删除，因为是删除啊，所以 d 后面通常不接任何咚咚；
    - i   ：插入， i 的后面可以接字串，而这些字串会在新的一行出现(目前的上一行)；
    - p   ：列印，亦即将某个选择的数据印出。通常 p 会与参数 sed -n 一起运行～
    - s   ：取代，可以直接进行取代的工作哩！通常这个 s 的动作可以搭配正规表示法！例如 1,20s/old/new/g 就是啦！
以行为单位的新增/删除功能

> 将/etc/passwd的内容列出并且列印行号，同时，请将第 2~5 行删除
- nl /etc/passwd | sed '2,5d'

> 在第二行后面加入两行字，例如『Drink tea or .....』与『drink beer?』
-  nl /etc/passwd | sed '2a drink tea \ 
- \> drink beer ?'

> 我想将第2-5行的内容取代成为『No 2-5 number』呢？
- nl /etc/passwd | sed '2,5c No 2-5 number'

> 仅列出 /etc/passwd 文件内的第 5-7 行
- nl /etc/passwd | sed -n '5,7p'

> 部分数据的搜寻并取代的功能
- sed 's/要被取代的字串/新的字串/g'


>  /sbin/ifconfig eth0 | grep 'inet addr'
- inet addr:192.168.1.100  Bcast:192.168.1.255  Mask:255.255.255.0

> /sbin/ifconfig eth0 | grep 'inet addr' | \\

> \>  sed 's/^.*addr://g'
- 192.168.1.100  Bcast:192.168.1.255  Mask:255.255.255.0

> /sbin/ifconfig eth0 | grep 'inet addr' | \\

> \>  sed 's/^.*addr://g' | sed 's/Bcast.*$//g'
- 192.168.1.100 

> 删除掉空白行
- sed '/^$/d'


<h4 id='6.2'> 6.2 awk </h4>

- awk其名称得自于它的创始人 Alfred Aho 、Peter Weinberger 和 Brian Kernighan 姓氏的首个字母
> awk '条件类型1{动作1} 条件类型2{动作2} ...' filename
-  awk 的内建变量
    - NF	每一行($0)拥有的栏位总数
    - NR	目前 awk 所处理的是『第几行』数据
    - FS	目前的分隔字节，默认是空白键
- awk 的逻辑运算字节
    - \>	大於
    - <	小於
    - \>=	大於或等於
    - <=	小於或等於
    - ==	等於
    - !=	不等於
- -F参数：指定分隔符，可指定一个或多个

> 用 last 可以将登陆者的数据取出来
- last -n 5

> 用 last 可以将登陆者的数据取出来 第一列和第三列
- last -n 5 | awk '{print $1 "\t" $3}'

     
- last -n 5| awk '{print $1 "\t lines: " NR "\t columns: " NF}'

> 要查阅第三栏小於10以下的数据，并且仅列出帐号与第三栏 仅能在第二行后才开始生效
- cat /etc/passwd | awk '{FS=":"} $3 < 10 {print $1 "\t " $3}'
>  awk 在开始处理输入文件之前会执行 BEGIN 块
- cat /etc/passwd | awk 'BEGIN {FS=":"} $3 < 10 {print $1 "\t " $3}'
> awk 在处理了输入文件中的所有行之后执行END块
- awk '{count++;print $0;} END{print "user count is ",count}' /etc/passwd


<h4 id='6.3'> 6.3 正规表达式 </h4>

> 待搜寻的字串(word)在行首！
- grep -n '^word' regular_express.txt

> 待搜寻的字串(word)在行尾！
- grep -n 'word$' regular_express.txt

> 搜寻含有单引号 ' 的那一行！ 转义字符\
- grep -n \\' regular_express.txt

> . 一个字节, 搜寻的字串可以是 (eve) (eae) (eee) (e e)， 但不能仅有 (ee)
- grep -n 'e.e' regular_express.txt

> \* 重复零个到无穷多个的前一个RE字符, 找出含有 (es) (ess) (esss) 等等的字串，注意，因为 * 可以是 0 个，所以 es 也是符合带搜寻字串
- grep -n 'ess*' regular_express.txt 

> [list]
 
> 搜寻含有 (gl) 或 (gd) 的那一行. 例如『 a[afl]y 』代表搜寻的字串可以是 aay, afy, aly 即 [afl] 代表 a 或 f 或 l 的意思！
- grep -n 'g[ld]' regular_express.txt

> [n1-n2]
 
> 例如不想要开头是英文字母
- grep -n '^[^a-zA-Z]' regular_express.txt
- grep -n '^[^[:alpha:]]' regular_express.txt

> \\{n,m\\}    

> 在 g 与 g 之间有 2 个到 3 个的 o 存在的字串，亦即 (goog)(gooog)
- grep -n 'go\\{2,3\\}g' regular_express.txt

<h3 id = "7"> 7. cpu disk </h3>  

> 查看物理cpu个数( --sort -u  )
- grep 'physical id' /proc/cpuinfo | sort -u

> 查看核心数量
- grep 'core id' /proc/cpuinfo | sort -u | wc -l

> 查看线程数
- grep 'processor' /proc/cpuinfo | sort -u | wc -l

> 当前目录下的文件夹大小 du (disk usage)按大小排序目录
- du -h --time --max-depth=1 | sort -hr 

> 查看文件系统的容量 使用情况
- df -h

> 查看各个分区的使用情况 lsblk(lst block devices) 
- lsblk


