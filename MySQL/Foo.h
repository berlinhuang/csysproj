//
// Created by Berlin Huang on 2022/4/26 0026.
//

#ifndef CSYSPROJ_FOO_H
#define CSYSPROJ_FOO_H
#include "MayerSingleton.h"
#include "LazySingleton.h"

#include <iostream>
#include <thread>

using namespace std;

class Foo :public MayerSingleton<Foo>
{
public:
    void operator()()//重载
    {
        cout<<&GetInstance<<endl;
    }
};

class LazyFoo:public LazySingleton<LazyFoo,false>
{
public:
    void operator()(){
        cout<<&GetInstance<<endl;
    }
};

class ThreadSafeLazyFoo:public LazySingleton<ThreadSafeLazyFoo>
{
public:
    void operator()(){
        cout<<&GetInstance<<endl;
    }
};


void SingletonTest()
{
//    thread t1((Foo()));
//    thread t2((Foo()));
//


    std:thread t1,t2;
    t1= thread((ThreadSafeLazyFoo()));
    t2= thread((ThreadSafeLazyFoo()));
    t1.join();
    t2.join();
    this_thread::sleep_for(chrono::milliseconds(100));

}

#endif //CSYSPROJ_FOO_H
