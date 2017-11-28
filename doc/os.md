---
<table>
    <caption>32bit linux os 进程虚拟地址空间</caption>
    <tr><td>1G内核空间</br>0xFFFFFFFF</br>|</br>0xC0000000</td><td></td></tr>
    <tr><td rowspan = "11">3G用户空间</br>0xBFFFFFFF</br>|</br>0x00000000</td><td>环境变量</td></tr>
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