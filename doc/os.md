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

>  进程地址空间:

- 命令行参数
- 环境变量
- stack: 局部变量 函数调用时的参数
- 共享库: 
- heap: 进程运行中被动态分配的内存段 大小并不固定 malloc free
- bss(Block Started by Symbol): 未初始化的全局变量(静态内存分配)
- data: 已初始化的全局变量(静态内存分配)
- text: 存放程序执行代码 包含一些只读的常数变量，例如字符串常量等 C++成员函数(多个对象共享) 


> Linux使用了四级保护机制：
- 0级供 操作系统内核使用；
- 1级供 系统调用使用；
- 2级供 共享库用；
- 3级供 应用程序使用



