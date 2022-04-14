####  RTTI
> 在C++环境中﹐头文件(header file)含有类之定义(class definition)亦即包含有关类的结构资料(representational information)。但是﹐这些资料只供编译器(compiler)使用﹐编译完毕后并未留下来﹐所以在执行时期(at run-time)﹐无法得知对象的类资料﹐包括类名称、数据成员名称与类型、函数名称与类型等等。例如﹐两个类Figure和Circle﹐其之间为继承关系。
```C++
    Figure *p; 
    p = new Circle(); 
    Figure &q = *p; 
    // 在执行时﹐p指向一个对象﹐但欲得知此对象之类资料﹐就有困难了。同样欲得知q 所参考(reference) 对象的类资料﹐也无法得到。RTTI(Run-Time Type Identification)就是要解决这困难﹐也就是在执行时﹐您想知道指针所指到或参考到的对象类型时﹐该对象有能力来告诉您。随着应用场合之不同﹐所需支持的RTTI范围也不同。最单纯的RTTI包括﹕ 
    //1类识别(class identification)──包括类名称或ID。 
    //2继承关系(inheritance relationship)──支持执行时期的「往下变换类型」(downward casting)﹐亦即动态变换类型(dynamic casting) 。
    
    //在对象数据库存取上﹐还需要下述RTTI﹕ 
    //1.对象结构(object layout) ──包括属性的类型、名称及其位置（position或offset）。
    //2.成员函数表(table of functions)──包括函数的类型、名称、及其参数类型等。
        //其目的是协助对象的I/O 和持久化(persistence) ﹐也提供调试讯息等。 
        //若依照Bjarne Stroustrup 之建议〔注1 〕﹐C++ 还应包括更完整的RTTI﹕ 
    //1.能得知类所实例化的各对象 。 
    //2.能参考到函数的源代码。 
    //3.能取得类的有关在线说明(on-line documentation) 。 
        //其实这些都是C++ 编译完成时所丢弃的资料﹐如今只是希望寻找个途径来将之保留到执行期间。然而﹐要提供完整的RTTI﹐将会大幅提高C++ 的复杂度﹗
```

> RTTI(Run Time Type Identification):通过运行时类型识别，程序能够使用基类的指针或引用来检查着这些指针或引用所指的对象的实际派生类型。

> RTTI提供了两个非常有用的操作符：typeid和dynamic_cast。
- typeid操作符，返回指针和引用所指的实际类型；
- dynamic_cast操作符，将基类类型的指针或引用安全地转换为其派生类类型的指针或引用。

> 为了提供RTTI﹐C++ 就将在vptr中附加个指针﹐指向typeinfo对象
- 由于该类所实例化之各对象﹐皆含有个指针指向vtbl虚函数表﹐因之各对象皆可取出typeinfo对象而得到RTTI

> 编译器提供的RTTI执行过程
```C++
    Figure *f1 = new Square();  
    Figure *f2 = new Square(); 
    const typeinfo ty = typeid(*f2); 
    其中﹐typeid(*f2) 的动作是﹕ 
    1.取得f2所指之对象。 
    2.从对象取出指向vptr指针﹐经由此指针取得vtbl表。 
    3.从表中找出指向typeinfo对象之指针﹐经由此指针取得typeinfo对象。 
    这typeinfo对象就含有RTTI了。经由f1及f2两指针皆可取得typeinfo对象﹐所以 typeid(*f2) == typeid(*f1)。
```
> 程序员自己提供的RTTI 
 - 通常程序员自己可提供简单的RTTI﹐例如提供类的名称或识别(TypeID)。最常见的方法是﹕为类体系定义些虚函数如Type_na() 及Isa() 函数等。
```C++
    class Figure { }; 
    
    class Rectangle : public Figure { }; 
    
    class Square : public Rectangle 
    { 
        int data; 
    public: 
        Square() { data=88; } 
        void Display() { cout << data << endl; } 
    }; 
    
    void main() 
    { 
        Figure *f = new Rectangle(); 
        Square *s = (Square *)f; 
        s -> Display(); 
    } 
    //这时s指向Rectangle之对象﹐而s->Display()呼叫Square::Display()﹐将找不到data值。若在执行时能利用RTTI来检查之﹐就可发出错误讯息。于是﹐自行加入RTTI功能﹕ 
    class Figure 
    { 
    public: 
        virtual char* Type_na() { return "Figure"; } 
        virtual int Isa(char* cna) { return !strcmp(cna, "Figure")? 1:0; } 
    }; 
    
    class Rectangle:public Figure 
    { 
    public: 
        virtual char* Type_na() { return "Rectangle"; } 
        virtual int Isa(char* cna)  { return !strcmp(cna, "Rectangle")?1 : Figure::Isa(cna); } 
        static Rectangle* Dynamic_cast(Figure* fg) { return fg -> Isa(Type_na())?(Rectangle*)fg : 0; } 
    }; 
    
    class Square:public Rectangle 
    { 
        int data; 
    public: 
        Square() { data=88; } 
        virtual char* Type_na() { return "Square"; } 
        virtual int Isa(char* cna) { return !strcmp(cna, "Rectangle")? 1 : Rectangle::Isa(cna); } 
        static Square* Dynamic_cast(Figure *fg)  { return fg->Isa(Type_na())? (Square*)fg : 0; } 
        void Display() { cout << "888" << endl; } 
    }; 
    // 虚函数Type_na()提供类名称之RTTI﹐而Isa()则提供继承之RTTI﹐用来支持「动态转类型」函数──Dynamic_cast()。例如﹕ 
    
    Figure *f = new Rectangle(); 
    cout << f -> Isa("Square") << endl; 
    cout << f -> Isa("Figure") << endl; 
    // 这些指令可显示出﹕f 所指向之对象并非Square之对象﹐但是Figure之对象（含子孙对象）。再如﹕ 
    Figure *f; Square *s; 
    f = new Rectangle(); 
    s = Square == Dynamic_cast(f); 
    if(!s) 
        cout << "dynamic_cast error!!" << endl; 
    // 此时﹐依RTTI来判断出这转类型是不对的。 
```
### 对象内存布局
#### 1. 简单对象模型
-  class obj
<table>
    <tr><td>成员变量</td><td></td><td></td></tr>
    <tr><td rowspan = "4">虚函数表指针 vptr </td><td rowspan = "4">虚拟表:vtbl</td><td> type_info</td></tr>
    <tr><td>虚析构函数:virtual ~Point();</td></tr>
    <tr><td>虚函数:virtual ostream& print( ostream &os ) const;</td></tr>
</table>

-  class object外
<table>
    <tr><td>静态成员: static int Point::_point_count</td></tr>
</table>

<table>
    <tr><td>静态方法: static int Point::PointCount()</td></tr>
</table>

<table>
    <tr>
        <td>成员函数:<br> Point::point(float) <br>float Point::x()</td>
    </tr>
</table>

#### 2. 带有虚函数的 重复继承(对象模型)


```C++
    class B
    {
    private:
        int a;
        char b;
    public:
        virtual void f(){}
        
        virtual void Bf(){}
    };
    
    class B1: public B
    {
    private:
        int a1;
        char b1;
    public:
        virtual void f(){}
        virtual void f1(){}
        
        virtual void Bf1(){}
    };
    
    class B2: public B
    {
    private:
        int a1;
        char b1;
    public:
        virtual void f(){}
        virtual void f2(){}
        
        virtual void Bf2(){}
    };
    
    
    class D:public B1, public B2
    {
    private:
        int ad;
        char bd;
    public:
        virtual void f(){}
        
        virtual void f1(){}
        virtual void f2(){}
        
        virtual void Df(){}
    };

```

- vptr@B1:
    - D::f//重写
    - B::Bf
    - D::f1//重写
    - B1::Bf1
    - D::Df
    
- vptr@B2:
    - D::f//重写
    - B::Bf
    - D::f2//重写
    - B2::Bf2

<table>
    <tr><td>0</td><td rowspan = "5" >B1</td><td>虚函数表指针:vptr@B1</td><td>D如果还虚函数会在这里添加或者覆盖基类虚函数地址</td></tr>
    <tr><td>4</td><td>a</td><td></td></tr>
    <tr><td>8</td><td>b</td><td></td></tr>
    <tr><td>12</td><td>a1</td><td></td></tr>  
    <tr><td>16</td><td>b1</td><td></td></tr>
    <tr><td>20</td><td rowspan = "5" >B2</td><td>虚函数表指针:vptr@B2</td><td>D如果还虚函数会在这里添加或者覆盖基类虚函数地址</td></tr>
    <tr><td>24</td><td>a</td><td></td></tr>
    <tr><td>28</td><td>b</td><td></td></tr>
    <tr><td>32</td><td>a2</td><td></td></tr>  
    <tr><td>36</td><td>b2</td><td></td></tr>  
    <tr><td>40</td><td rowspan = "3" >D</td><td>ad</td><td></td></tr>
    <tr><td>44</td><td>bd</td><td></td></tr>
</table>


#### 3.带有虚函数的 多重虚拟继承(对象模型)

- 多了vbptr(虚基类指针)来存储到公共基类的偏移


```C++
    class B
    {
    private:
        int a;
        char b;
    public:
        virtual void f(){}
        
        virtual void Bf(){}
    };
    
    class B1:virtual public B
    {
    private:
        int a1;
        char b1;
    public:
        virtual void f(){}
        virtual void f1(){}
        
        virtual void Bf1(){}
    };
    
    class B2:virtual public B
    {
    private:
        int a1;
        char b1;
    public:
        virtual void f(){}
        virtual void f2(){}
        
        virtual void Bf2(){}
    };
    
    
    class D:public B1, public B2
    {
    private:
        int ad;
        char bd;
    public:
        virtual void f(){}
        
        virtual void f1(){}
        virtual void f2(){}
        
        virtual void Df(){}
    };

```
- vptr@B1
    - D::f1()//重写
    - B1::Bf1()
    - D::Df()

- vptr@B2
    - D:f2()//重写
    - B2::Bf2()

- vptr@B
    - D::f()//重写
    - B::f()

<table>
    <tr><td>0</td><td rowspan = "4" >B1</td><td>虚函数表指针:vptr@B1</td><td>D如果还虚函数会在这里添加或者覆盖基类虚函数地址</td></tr>
    <tr><td>4</td><td>虚基类指针:vbptr@B1</td></tr>
    <tr><td>8</td><td>a1</td></tr>
    <tr><td>12</td><td>b1</td></tr>    
    <tr><td>16</td><td rowspan = "4" >B2</td><td>虚函数表指针:vptr@B2</td><td>D如果还虚函数会在这里添加或者覆盖基类虚函数地址</td></tr>
    <tr><td>20</td><td>虚基类指针:vbptr@B2</td></tr>
    <tr><td>24</td><td>a2</td></tr>
    <tr><td>28</td><td>b2</td></tr>
    <tr><td>32</td><td rowspan = "2" >D</td><td>ad</td></tr>
    <tr><td>36</td><td>bd</td></tr>
    <tr><td>40</td><td rowspan = "4" >B</td><td>vtordisp for vbase B</td></tr>
    <tr><td>44</td><td>虚函数表指针:vptr@B</td></tr>
    <tr><td>48</td><td>a</td></tr>
    <tr><td>52</td><td>b</td></tr>
</table>



