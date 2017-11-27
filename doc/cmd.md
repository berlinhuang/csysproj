
#### netstat
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

#### tcpdump


#### ipcs


#### ipcrm
