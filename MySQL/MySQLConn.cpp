//
// Created by Berlin Huang on 2022/4/29 0029.
//

#include "MySQLConn.h"

//初始化连接
MySQLConn::MySQLConn() {
    _conn = mysql_init(NULL);
}

// 释放数据库连接资源
MySQLConn::~MySQLConn() {
    if (!_conn) mysql_close(_conn);
}

// 连接数据库
bool MySQLConn::connect(string hostName, unsigned short port, string user,  string passwd, string dbname) {
    if (mysql_real_connect(this->_conn, hostName.c_str(), user.c_str(), passwd.c_str(), dbname.c_str(), 0, NULL, 0))
    {
        mysql_query(_conn, "set names utf8"); // 设置编码
        return true;
    }
    return false;
}


bool MySQLConn::update(const string &s) {
    if(mysql_query(_conn,s.c_str())){

    }
}

MYSQL_RES * MySQLConn::query(string sql) {
    if(mysql_query(_conn,sql.c_str())){
        return nullptr;
    }else{
        return mysql_use_result(_conn);
    }
}