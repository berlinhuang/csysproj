
> array 静态数组

### Sequence Containers
> vector 动态数组 
```C++
    template < class T,
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class vector{
    }
    
```
- 以原大小两倍空间增长，将旧数据复制过来，再添加新数据

> list 环形双向链表  
```C++
    template < class T,
               class Alloc = alloc > // 缺 省使用alloc作为适配器
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
                class Compare = less<typename Sequence::value_type> >//从小到大
    class priority_queue{
    
    }
    
    
    priority_queue< int, vector<int>, greater<int> > p;// 从大到小
    
    
```
- 底部以vector作为容器
```C++
    // for max_heap

    template< class RandomAccessIterator >
    intline void push_heap(RandomAccessIterator first, RandomAccessItertor last)
    {
        __push(first, las, value_type(last));
    }
    
    
    template< class RandomAccessIterator >
    intline void pop_heap(RandomAccessIterator first, RandomAccessItertor last)
    {
        __pop(first, last, value_type(first));
    }
    
    template< class RandomAccessIterator >
    void sort_heap(RandomAccessIterator first, RandomAccessItertor last)
    {
        while(last-first > 1)
            pop_heap(first, last--);
    }
        
    template< class RandomAccessIterator >
    inline void make_heap(RandomAccessIterator first, RandomAccessItertor last)
    {
        __make_heap(first, last, value_type(first), distance_type(first));
    }
        
    
    
```


---


### Associative Containers


> RB-tree

1. set
```C++
    template < class Key,
               class Compare = less<Key>, //从小到大
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class set{
    }
    
```
2. map
```C++
    template < class Key,
               class T,
               class Compare = less<Key>, //从小到大
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class map{
    }
    
```
3. multiset
4. multimap

> hashtable

1. hash_set
```C++
    template < class Value,
               class HashFcn = hash<Value>,
               class EqualKey = equal_to<Value>,
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class hash_set{
    }
    
```
2. hash_map
```C++
    template < class Value,
               class T,
               class HashFcn = hash<Value>,
               class EqualKey = equal_to<Value>,
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class hash_map{
    }
    
```
3. hash_multiset
```C++
    template < class Value,
               class HashFcn = hash<Value>,
               class EqualKey = equal_to<Value>,
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class hash_multiset{
    }
    
```
4. hash_multimap
```C++
    template < class Value,
               class T,
               class HashFcn = hash<Value>,
               class EqualKey = equal_to<Value>,
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class hash_multimap{
    }
    
```
