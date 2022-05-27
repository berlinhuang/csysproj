//
// Created by Berlin Huang on 2022/5/7 0007.
//

#include <memory> //clock_t
#include "mysqlconn.h"
#include "mysqlconnpool.h"

#define MULTITHREADLEN 1024

int main(){
    clock_t begin = clock();
    MySQLConnPool *cp = MySQLConnPool::getInstancePtr();
    for( int i = 0; i<MULTITHREADLEN; ++i){
        shared_ptr<MySQLConn> sp = cp->getConnection();
        sp->exec("select * from user");
        cout << "行数:" << sp->rowCount() << endl;
        cout << "列数:" << sp->columnCount() << endl;
    }
    clock_t end =clock();
    cout<<(end-begin)<<"ms"<<endl;
    delete cp;
    return 0;
}