//
// Created by Berlin Huang on 2022/4/29 0029.
//

#ifndef CSYSPROJ_MYSQLCONNPOOL_H
#define CSYSPROJ_MYSQLCONNPOOL_H

#include "public.h"
#include "singleton.h"
#include "mysqlconn.h"
#include <thread>
#include <queue>
#include <functional> //std::bind
#include <condition_variable>

using namespace std;

class MySQLConnPool : public Singleton<MySQLConnPool>{
private:
    MySQLConnPool();
    bool loadConfigFile();
    void produceConnectionTask();
    void scannerConnectionTask();

protected:
    friend class Singleton<MySQLConnPool>;


    std::queue<MySQLConn*> _connectionQue;   //连接池队列

    int _initSize;                          // 连接池初始连接量
    int _maxSize;                           // 连接池最大连接量
    int _maxIdleTime;                       // 连接池的最大空闲时间
    int _connectionTimeOut;                 // 连接池获取连接超时时间
    atomic_int _connectionCnt;              // 连接总数

    condition_variable _cv;

//    std::mutex mtx;
//    int m_maxConn;

    mutex _queueMutex;

    string _ip;
    unsigned short _port;
    string _username;
    string _password;
    string _dbname;
public:
    shared_ptr<MySQLConn> getConnection();
};


#endif //CSYSPROJ_MYSQLCONNPOOL_H
