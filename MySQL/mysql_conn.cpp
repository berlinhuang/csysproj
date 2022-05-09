//
// Created by Berlin Huang on 2022/4/22 0022.
//

#include "mysql_conn.h"
#include <cstring>
#include <iostream>
using namespace std;

IMPLEMENT_SINGLETON(Mysql)

Mysql::Mysql() { this->m_dbHandle = mysql_init(NULL); }

Mysql::~Mysql() {
    if(m_instance!=NULL){
        delete m_instance;
    }
    mysql_close(this->m_dbHandle);
}


bool Mysql::connectToDatabase(const char *hostName, const char *user, const char *passwd, const char *dbname)
{
    if (mysql_real_connect(this->m_dbHandle, hostName, user, passwd, dbname, 0, NULL, 0))
    {
        //cout << "连接成功" << endl;
        mysql_query(m_dbHandle, "set names utf8"); // 设置编码
        return true;
    }
    return false;
}

bool Mysql::exec(const string &s)
{
    m_hasRead = false;
    m_affected_rows = -1;
    m_curReadValueIndex = -1;
    return (mysql_query(this->m_dbHandle, s.c_str()) == 0);
}

bool Mysql::next()
{
    if (!m_hasRead)
    {
        mysql_read();
        m_hasRead = true;
        m_affected_rows = mysql_affected_rows(this->m_dbHandle);
    }

    return (++m_curReadValueIndex < m_affected_rows);
}

string Mysql::values(int index)
{
    string ret;

    if (m_curReadValueIndex < m_affected_rows)
    {
        ret = this->m_execResult[m_curReadValueIndex][index];
    }

    return ret;
}

int Mysql::rowCount()
{
    if (m_affected_rows == -1)
    {
        mysql_read();
        m_hasRead = true;
        m_affected_rows = mysql_affected_rows(this->m_dbHandle);
    }

    return m_affected_rows;
}

int Mysql::columnCount()
{
    return m_colCount;
}

void Mysql::mysql_read()
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

    MYSQL_RES *result = mysql_store_result(this->m_dbHandle);
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

int Mysql::databaseClose()
{
    mysql_close(m_dbHandle);
    return 0;
}
