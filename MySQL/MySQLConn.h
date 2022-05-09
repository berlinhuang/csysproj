//
// Created by Berlin Huang on 2022/4/29 0029.
//

#ifndef CSYSPROJ_MYSQLCONN_H
#define CSYSPROJ_MYSQLCONN_H

#include <string>
#include <cstring>
#include "mysql/mysql.h"

using namespace  std;

class MySQLConn {
private:
    MYSQL * _conn; //mysql 数据库连接句柄
    clock_t _alivetime;
//    MYSQL * m_dbHandle = nullptr;
public:
    MySQLConn();
    ~MySQLConn();
    bool connect( string ip, unsigned short port, string username, string password, string dbname);
    bool update(const string &s );
    MYSQL_RES * query(string sql);

    void start() {
        _alivetime = clock();
    }

    // 返回存活的时间
    clock_t end() const {
        return clock() - _alivetime;
    }
};


#endif //CSYSPROJ_MYSQLCONN_H
