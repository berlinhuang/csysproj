//
// Created by Berlin Huang on 2022/4/26 0026.
//

#ifndef CSYSPROJ_MAYERSINGLETON_H
#define CSYSPROJ_MAYERSINGLETON_H



/*
 * =default 关键来声明构造函数，告诉编译器为该类生成一个默认的版本
 *
 * =delete的几处作用
 * 1. 禁止编译器默认生成的函数,只能显式explicit 进行调用拷贝，移动，赋值
 * 不想使用其中某个，可以将其定义为private，或者使用=delete。
 * 建议既定义成private,同时使用=delete
 * 2. delete 关键字也可以禁用其它类成员函数
 */

template <typename T>
class MayerSingleton {
protected: // 可以被其他子类继承使用
    MayerSingleton()=default;                        // 默认构造 default constructor
    virtual ~MayerSingleton()=default;               // 默认析构 default destructor
public:
    MayerSingleton(T&&) =delete;                    // C++ 11 移动构造 move constructor 返回含有指针成员的对象
    MayerSingleton(const T&) =delete;                // 拷贝构造 copy constructor
    void operator = (const T &)=delete;         // copy assignment operator 拷贝赋值
    T *operator &() =delete;                    // 取址


    static T& GetInstance()
    {
        static T instance;
        return instance;
    }

};


#endif //CSYSPROJ_MAYERSINGLETON_H
