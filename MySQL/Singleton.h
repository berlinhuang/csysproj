//
// Created by Berlin Huang on 2022/4/26 0026.
//

/**
 * 模板类： std::lock_guard
 * template<class Mutex> class lock_guard;
 * lock_guard 通常用来管理一个 std::mutex 类型的对象，
 * 通过定义一个 lock_guard 一个对象来管理 std::mutex 的上锁和解锁。
 *
 * unique_lock 和 lock_guard 一样，对 std::mutex 类型的互斥量的上锁和解锁进行管理，
 * 一样也不管理 std::mutex 类型的互斥量的声明周期。但是它的使用更加的灵活，支持的构造函数如下：
 *
 * template< class T > struct atomic;
 *
 *
 */

#ifndef CSYSPROJ_SINGLETON_H
#define CSYSPROJ_SINGLETON_H

#include <atomic>
#include <mutex>

template <typename T>
class Singleton {
protected:
    //静态成员变量
    static std::atomic<T*> m_instance;//指针对象
    static std::mutex m_mtx;


    Singleton() = default;              //构造
    virtual ~Singleton() = default;     //析构

    Singleton(const T&) noexcept = delete; //拷贝构造
    T& operator = (const T&) = delete; //赋值

public:
    // 双重检查(double-checked)锁模式
    static T* getInstancePtr() {
        T * tmp = m_instance.load(std::memory_order_acquire); //读操作 返回m_instance
        if(nullptr==tmp)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            tmp=m_instance.load(std::memory_order_relaxed);
            if(nullptr==tmp){
//                    tmp=new T;
//                    m_instance.store(tmp,std::memory_order_release);
                m_instance.store(new T(),std::memory_order_release); //写操作 把m_instance设置为new T()
            }
        }
        return m_instance;
    }

    static T getInstance(){
        T * tmp = m_instance.load(std::memory_order_acquire); //读操作 返回m_instance
        if(nullptr==tmp)
        {
            std::unique_lock<std::mutex> lock(m_mtx);
            tmp=m_instance.load(std::memory_order_relaxed);
            if(nullptr==tmp){
//                    tmp=new T;
//                    m_instance.store(tmp,std::memory_order_release);
                m_instance.store(new T(),std::memory_order_release); //写操作 把m_instance设置为new T()
            }
        }
        return *m_instance;
    }



};

//类外初始化静态成员变量
//template <typename T>
//std::atomic<T*>Singleton<T>::m_instance{nullptr};
//
//template <typename T>
//std::mutex Singleton<T>::m_mtx{};


//宏定义
#define IMPLEMENT_SINGLETON(ClassName) \
    template<> std::atomic<ClassName*> Singleton<ClassName>::m_instance(0); \
    template<> std::mutex Singleton<ClassName>::m_mtx{};



#endif //CSYSPROJ_SINGLETON_H




