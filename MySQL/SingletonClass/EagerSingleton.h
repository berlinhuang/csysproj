//
// Created by Berlin Huang on 2022/4/26 0026.
//

//恶汉模式
#ifndef CSYSPROJ_EAGERSINGLETON_H
#define CSYSPROJ_EAGERSINGLETON_H
#include <istream>
template <typename T>
class EagerSingleton {
private:
    static T* t_;
public:
    static T& GetInstance()
    {
        return *t_;
    }
    EagerSingleton( T&&)=delete;
    EagerSingleton( T&) =delete;
    void operator=(const T&)=delete;

protected:
    EagerSingleton()=default;
    virtual ~EagerSingleton()=default;
};

template<typename T>
T* EagerSingleton<T>::t_=new(std::nothrow) T;

#endif //CSYSPROJ_EAGERSINGLETON_H
