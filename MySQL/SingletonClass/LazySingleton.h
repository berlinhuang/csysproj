//
// Created by Berlin Huang on 2022/4/26 0026.
//

//懒汉单例模式

#ifndef CSYSPROJ_LAZYSINGLETON_H
#define CSYSPROJ_LAZYSINGLETON_H
#include <memory> //unique_ptr
#include <mutex>
using namespace std;

template<typename T,bool is_thread_safe=true>
class LazySingleton {
private:
    static unique_ptr<T> t_;//防止线程销毁时发生内存泄漏，也可以在析构函数中销毁指针。避免多指针指向同一个资源
    static mutex mtx_;
public:
    static T& GetInstance()
    {
        if(is_thread_safe==false)
        {
            if(t_==nullptr)
                t_ = unique_ptr<T>(new T);
            return *t_;
        }
        if(t_==nullptr)
        {
            unique_lock<mutex> unique_locker(mtx_);//对mutex锁的独占,unique_locker对象生命周期结束后自动解锁。
            if(t_== nullptr)
                t_=unique_ptr<T>(new T);
            return *t_;
        }
    }
    LazySingleton( T&& )=delete;
    LazySingleton(const T&)=delete;
    void operator=(const T&)=delete;

protected:
    LazySingleton()=default;
    virtual ~LazySingleton()=default;
};

template<typename T,bool is_thread_safe>
unique_ptr<T> LazySingleton<T, is_thread_safe>::t_;

template<typename T, bool is_thread_safe>
mutex LazySingleton<T,is_thread_safe>::mtx_;


#endif //CSYSPROJ_LAZYSINGLETON_H
