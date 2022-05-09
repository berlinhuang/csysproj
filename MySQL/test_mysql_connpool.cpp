//
// Created by Berlin Huang on 2022/5/7 0007.
//

#include <memory> //clock_t
#include "MySQLConn.h"
#include "MySQLConnPool.h"

#define MULTITHREADLEN 1024

int main(){
    clock_t begin = clock();
    MySQLConnPool *cp = MySQLConnPool::getInstancePtr();
    for( int i = 0; i<MULTITHREADLEN; ++i){
        shared_ptr<MySQLConn> sp = cp->getConnection();
    }
    clock_t end =clock();
    cout<<(end-begin)<<"ms"<<endl;
    delete cp;
    return 0;
}