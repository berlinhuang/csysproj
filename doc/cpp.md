- static_cast<目标数据类型>(78.28)   80%用这个   只在编译时进行类型检查
```C++
    int n = static_cast<int>(18.98);//
    printf("\n%d",static_cast<int>(98.98));//
     
    int *p = static_cast<int*>(malloc(100));
```
- const_cast<int*>(p);//去掉常量属性     15%用这个
```C++
    int num[3] = {1,2,3};
    const int *p = num;
    std::cout<<*p<<*(p+1)<<*(p+2)<<std::endl;
    int *pnew = const_cast<int*>(p);//去掉常量属性     15%用这个
    *pnew = 100;
```
- reinterpret_cast<char*>(num);//专业转换指针  1%用这个
```C++
    float fl = 123.3231;
    int num = 3;
    char *p = reinterpret_cast<char*>(num);//专业转换指针  1%用这个
```

- dynamic_cast 基类的指针或引用 安全的转换为派生类的指针或引用  运行时类型检查(RTTI Run-Time Type Identification)
```C++
    // 原理: 将一个基类对象指针（或引用）cast （抛）到继承类指针，
    // dynamic_cast 会根据基类指针是否真正指向继承类指针来做相应处理。//
    
    // 返回值: 对指针进行dynamic_cast，失败返回null，成功返回正常cast后的对象指针；
    // 对引用进行dynamic_cast，失败抛出一个异常，成功返回正常cast后的对象引用。
    
    // 注意: dynamic_cast在将父类cast到子类时，父类必须要有虚函数
    
    // 对编译器的要求: dynamic_cast<> 会用到RTTI技术，因此需要启动“运行时类型信息”这一选项，而在VC.net 2003中默认是关闭的。
    // 所以，需要人为的启动这一选项。否则编译器会警告
    class Base
    {
        virtual void fun(){}
    };
    
    class Derived:public Base
    {
    };
   
    
    void func
    {
        Base *p = new Derived();//父类类型的指针 指向子类对象
        Derived *pd = dynamic_cast<Derived *> (p);
        
        
        Base *p = new Base();//父类类型的指针 指向父类对象
        Derived *pd = dynamic_cast<Derived *> (p);//子类Derived中包含父类Base中没有的数据和函数成员 它返回NULL 
   
    }
    

```