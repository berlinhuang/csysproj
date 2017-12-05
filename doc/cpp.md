> volatile
- 类型修饰符 这个关键字声明的变量，编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问
- 每次使用它的时候总是重新从它所在的内存读取数据.而不是优化做法(读寄存器的数据)


> static

- static全局变量 
    - 初始化在编译的时候进行。在main函数被调用之前初始化并且只初始化一次,防止在其他文件单元中被引用。
    - 拥有文件作用域，只在声明的文件中有效，其他源文件中不可见。
    - 生存期从main第一次执行,直到程序结束。
    
- static函数变量(static局部变量) 
    - 在函数中有效，第一次进入函数初始化且只初始化一次，以后进入函数将沿用上一次的值
    - 在{}中定义了static变量，其作用域为{}内，出了{}，程序会指示该的static变量未定义
    - 生存期从main第一次执行,直到程序结束。
    
- static普通函数
    - 用static修饰的函数，本限定在本源码文件中，不能被本源码文件以外的代码文件调用
    - static函数在内存中只有一份，普通函数在每个被调用中维持一份拷贝
    
- static成员函数 
    - static成员函数没有this形参，它可以直接访问所属类的static成员，但不能直接使用非static成员。
    - 类的非static成员函数是可以直接访问类的static和非static成员，而不用作用域操作符。
    
- static成员变量
    - 类内声明，类外定义
    - 不通过类构造函数初始化，而是在定义时进行初始化
    - 一个例外：初始化式为常量表达式，整型static const数据成员（static const int） 可以在类的定义体内进行初始化：
      ```C++
      class Lunais{
        static const int zty = 30;
      }
      ```


> extern

- 传统的声明外部变量的功能: extern int a;仅仅是一个变量的声明，说明这个变量为外部变量，是在其他的c文件中定义的全局变量。而不是在定义变量a，并未为a分配内存空间。
```C++
//对变量而言，想在本源文件中使用另一个源文件的变量，就需要在使用前用extern声明该变量，或者在头文件中用extern声明该变量；
//对函数而言，想在本源文件中使用另一个源文件的函数，就需要在使用前用声明该函数，声明函数加不加extern都没关系，所以在头文件中函数可以不用加extern
```
- extern “C”是使C++能够调用C写的库文件的一个手段，如果要对编译器提示使用C的方式来处理函数的话，那么就要使用extern “C”来说明

```C++
    // 单一语句形式的链接指示符
    extern "C" size_t strlen(const char *);
    // 复合语句形式的链接指示符
    extern "C" {
        int strcmp( const char*, const char*);
        char *strcat(char*, const char*);
    }
    
    extern "C"{
        #include <string.h>
    }

```

> const
- const限定符
    - 因为const对象一旦创建后其值就不能再改变，所以const对象必须初始化
    - 默认情况下const对象只在文件内有效，如果想在多个文件之间共享const对象，必须在变量的定义之前添加extern关键字
    - const int i = 1;

- 对const的引用/(reference to const)常量引用
    - 把引用(常量引用)绑定到const对象上就像绑定到其他对象上一样,我们称之为对常量的引用(reference to const)
    - 允许为一个常量引用绑定非常量的对象，字面值，甚至是个一般表达式
    ```C++
    double dval(3.14);
    const int &ri(dval);
    // 实际上编译器做了如下操作
    const int temp = dval;
    const int &ri = temp;
    
    
    char str[10]("hello");
    const char (&rstr)[10](str); //常量引用    用str初始化
    str[4] = 'x';//ok
    rstr[4] = 'y';//false
    const char (&rrstr)[10](rstr);//引用可以给另一个引用初始化
    
    
    int(*p)(int a, int b)(add);
    std::cout<<p(1,2)<<std::endl;
    int(*const&rp)(int a, int b)(p);//引用函数指针     限定了函数指针不被修改
    rp = dec;//false  
    
    ```
    
- 指向常量的指针(pointer to constant)/底层const表示指针所指的对象是个常量: const int *a(param);
    - 和引用一样，也可以让指针指向常量或非常量
    - 不能用于改变其所指对象的值
    - 要存放常量对象（const int i = 1）的地址，只能使用指向常量的指针(const int *p)
    ```C++
    char str[10]("hello");
    const char *pc(str);//定义一个常量指针（百度百科）
    
    str[3] = 'x';//ok
    
    pc[3] = 'y';//false
    *(pc+3) ='y';//false 错误
    
    pc = "world"//ok
    ```

- 常量指针(const pointer)/顶层const表示指针本身是个常量:  
    - 指针是对象而引用不是，因此就像其他对象类型一样，允许把指针本身定为常量
    - 常量指针必须初始化，而且一旦初始化完成，则它的值（也就是存放在指针中的那个地址）就不能再改变了
    - 把*放在const关键字之前用以说明 指针是一个常量
    ```C++
        int errNumb = 0;
        int *const curErr = &errNumb;
    ```
    
- 指向常量的指针常量

- const 引用作形参

- const 成员函数 

- const 成员变量