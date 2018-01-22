
> array 静态数组

### Sequence Containers
> 1. vector 动态数组 
```C++
    template < class T,
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class vector{
    }
    
```
- 以原大小两倍空间增长，将旧数据复制过来，再添加新数据

> 2. list 环形双向链表  
```C++
    template < class T,
               class Alloc = alloc > // 缺 省使用alloc作为适配器
    class list{
    }
    
```
> 3. deque 双端队列 
```C++
    template < class T,
               class Alloc = alloc,
               size_t BufSiz = 0 >
    class deque{
    }
```
- 分段连续空间链接而成

(1). stack 栈 
```C++
    template < class T,
               class Sequence = deque<T> >
    class stack{
    }
    
```
(2). queue 单向队列
```C++
    template < class T,
               class Sequence = deque<T> >以dueue(双端队列)作为queue的底层容器
    class queue{
    }
    
    queue<int, list<int> > iqueue;//以list(环形双向链表)作为queue的底层容器
    
```

> 4. heap 堆 

(1). priority_queue 优先级队列
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
    // 底部叶节点（vector.end()）插入，上溯
    template< class RandomAccessIterator >
    intline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
        __push(first, last, distance_type(first), value_type(last));
    }
    
    template< class RandomAccessIterator,
              class Distance,
              class T>
    __push(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*)
    {
        __push_heap(first, Distance((last-first)-1), Distance(0), T(*(last-1)) );// first, hole, topIndex, value
    }
    
    //上溯
    template< class RandomAccessIterator,
                  class Distance,
                  class T>
    void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value)
    {
        Distance parent = (holeIndex - 1) / 2;// hole上溯
        while(holeIndex > topIndex && *(first + parent) < value )
        {
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) /2;
        }
        *(first+holeIndex) = value;
           
    }
    
    
    
    
    // 取走根节点，设置为叶节点右端元素（底部容器vector.end()），下溯
    template< class RandomAccessIterator >
    intline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
        __pop(first, last, value_type(first));
    }
    
    template< class RandomAccessIterator, class T >
    inline void __pop( RandomAccessIterator first, RandomAccessIterator last, T* )
    {
        __pop_heap(first, last - 1, last - 1,  T(*(last-1)), distance_type(first)); 
    }
    
    template< class RandomAccessIterator, 
              class Distance,
              class T >
    inline void __pop_heap( RandomAccessIterator first,
                            RandomAccessIterator last,
                            RandomAccessIterator result,
                            T value,
                            Distance*)
    {
        *result = *first;
        __adjust_heap(first, Distance(0), Distance(last - first), value);
    }
    
    template< class RandomAccessIterator, 
              class Distance,
              class T >
    void __adjust_heap( RandomAccessIterator first, 
                        Distance holeIndex,
                        Distance len,
                        T value)
    {
        Distance topIndex = holeIndex;
        //下溯
        Distance secondChild = 2 * holeIndex + 2; //由于从0开始计算 所以右儿子为 2n + 2;
        while(secondChild < len )
        {
            if( *(first +secondChild) < *(first +(secondChild -1))
                secondChild --;
            *(first+holeIndex) = *(first+secondChild);
            holeIndex = secondChild;
            secondChild = 2*(secondChild + 1);
        }
        if(secondChild == len)//只有左边节点
        {
            *(first + holeIndex) = *(first + (secondChild - 1));
            holeIndex = secondChild - 1;
        }       
         //把当初标记的最后的一个节点插入堆中( T(*(last - 1)  )
        __push_heap(first, holeIndex, topIndex, value);
    }
    
    
    
    
    // 不断的pop_heap，从右往前插入到vector
    template< class RandomAccessIterator >
    void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
        while(last-first > 1)
            pop_heap(first, last--);
    }
        
        
        
    template< class RandomAccessIterator >
    inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
    {
        __make_heap(first, last, value_type(first), distance_type(first));
    }
    
    template< class RandomAccessIterator, 
              class Distance,
              class T >
    void __make_heap( RandomAccessIterator first,
                      RandomAccessIterator last,
                      T*,
                      Distance*)
    {
        if (last - first < 2) return; //判断边界情况,如果只有一个元素 直接返回
            Distance len = last - first;  
            Distance parent = (len - 2)/2;   //最后一个元素的父节点  下溯   
            while (true) 
            {
                __adjust_heap(first, parent, len, T(*(first + parent)), comp);  
                if (parent == 0) 
                    return;  
                parent--;  
            }  
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
```C++
    template < class Key,
               class Compare = less<Key>, //从小到大
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class multiset{
    }
    
```
4. multimap
```C++
    template < class Key,
               class T,
               class Compare = less<Key>, //从小到大
               class Alloc = alloc > // 缺省使用alloc作为适配器
    class multimap{
    }
    
```

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
