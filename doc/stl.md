
> array 静态数组

#### STL
> vector 动态数组 
```C++
    template < class T,
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class vector{
    }
    
```
- 以原大小两倍空间增长，讲旧数据复制过来，再添加新数据

> list 环形双向链表  
```C++
    template < class T,
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class list{
    }
    
```
> deque 双端队列 
- 分段连续空间链接而成

1. stack 栈 
```C++
    template < class T,
               class Sequence = deque<T> >
    class stack{
    }
    
```
2. queue 单线队列
```C++
    template < class T,
               class Sequence = deque<T> >以list作为dueue的底层容器
    class queue{
    }
    
    queue<int, list<int> > iqueue;//以list作为queue的底层容器
    
```

> heap 堆 

1. priority_queue 优先级队列
```C++
    <queue>
    template <  class T, 
                class Sequence = vector<T>,//容纳优先队列的容器 也可以是dequeue
                class Compare = less<typename Sequence::value_type> >// 从大到小
    class priority_queue{
    
    }
    
    
    priority_queue< int, vector<int>, greater<int> > p;//从小到大
    
    
```
- 底部以vector作为容器