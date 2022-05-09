//
// Created by Berlin Huang on 2022/4/29 0029.
//

#ifndef CSYSPROJ_MYSQLCONN_H
#define CSYSPROJ_MYSQLCONN_H

#include <string>
#include <cstring>
#include "mysql/mysql.h"
#include <iostream>

using namespace  std;

class MySQLConn {
private:
    MYSQL * _conn; //mysql 数据库连接句柄
    clock_t _alivetime;
//    MYSQL * m_dbHandle = nullptr;
protected:
    int m_affected_rows = -1;     //mysql_read
    bool m_hasRead = false;       //执行exec后，是否已调用过mysql_read
    int m_curReadValueIndex = -1; //执行mysql_read后，下次取第几行的数据
    // 存储读取数据
    string **m_execResult;
    int m_rowCount;
    int m_colCount;
public:
    MySQLConn();
    ~MySQLConn();
    bool connect( string ip, unsigned short port, string username, string password, string dbname);
    bool next();
//    bool update(const string &s );
    MYSQL_RES * query(string sql);
    bool exec(const string &s); //执行SQL语句，末尾不需要加分号

    // 获取更新行列数
    int rowCount();
    int columnCount();
    // 数据读取
    void mysql_read();

    void start() {
        _alivetime = clock();
    }

    // 返回存活的时间
    clock_t end() const {
        return clock() - _alivetime;
    }

};


#endif //CSYSPROJ_MYSQLCONN_H
