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
    if (mysql_real_connect(this->_conn, hostName.c_str(), user.c_str(), passwd.c_str(),
                           dbname.c_str(), 0, NULL, 0))
    {
        std::cout << "连接成功" << endl;
        mysql_query(_conn, "set names utf8"); // 设置编码
        return true;
    }
    return false;
}


//bool MySQLConn::update(const string &s) {
//    if(mysql_query(_conn,s.c_str())){
//
//    }
//}

MYSQL_RES * MySQLConn::query(string sql) {
    if(mysql_query(_conn,sql.c_str())){
        return nullptr;
    }else{
        return mysql_use_result(_conn);
    }
}

bool MySQLConn::exec(const string &s)
{
    m_hasRead = false;
    m_affected_rows = -1;
    m_curReadValueIndex = -1;
    return (mysql_query(this->_conn, s.c_str()) == 0);
}

int MySQLConn::rowCount()
{
    if (m_affected_rows == -1)
    {
        mysql_read();
        m_hasRead = true;
        m_affected_rows = mysql_affected_rows(this->_conn);
    }

    return m_affected_rows;
}


bool MySQLConn::next()
{
    if (!m_hasRead)
    {
        mysql_read();
        m_hasRead = true;
        m_affected_rows = mysql_affected_rows(this->_conn);
    }

    return (++m_curReadValueIndex < m_affected_rows);
}

int MySQLConn::columnCount()
{
    return m_colCount;
}

void MySQLConn::mysql_read()
{
    // 释放数据
    if (this->m_rowCount != 0)
    {
        for (int i = 0; i < this->m_rowCount; i++)
        {
            delete[] this->m_execResult[i];
        }
        delete[] this->m_execResult;
    }

    MYSQL_RES *result = mysql_store_result(this->_conn);
    if (result != nullptr)
    {
        MYSQL_ROW row;
        int cow_lenth = result->field_count;
        int row_lenth = result->row_count;
        // 数据存储
        this->m_execResult = new string *[row_lenth];
        for (int i = 0; i < row_lenth; i++)
        {
            this->m_execResult[i] = new string[cow_lenth];
        }
        // 行
        this->m_rowCount = row_lenth;
        // 列
        this->m_colCount = cow_lenth;
        for (int i = 0; i < row_lenth; i++)
        {
            row = mysql_fetch_row(result);
            for (int j = 0; j < cow_lenth; j++)
            {
                //若数据库中该字段为空值，那么这里要判断一下row[j]是否为空，否则导致段错误
                if (row[j])
                {
                    this->m_execResult[i][j] = row[j];
                }
                else
                {
                    this->m_execResult[i][j] = "";
                }
            }
        }
        // 释放数据
        mysql_free_result(result);
    }
}