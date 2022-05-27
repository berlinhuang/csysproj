//
// Created by Berlin Huang on 2022/4/29 0029.
//

#include "mysqlconnpool.h"

IMPLEMENT_SINGLETON(MySQLConnPool)

bool MySQLConnPool::loadConfigFile() {
    FILE *pf = fopen("./mysql.conf", "r");
    if (!pf) {
        LOG("mysql.conf file is not exist!\n");
        return false;
    }
    while(!feof(pf)){
        char line[1024]={0};
        fgets(line,1024,pf);
        string str = line;
        int idx = str.find('=',0);

        if(idx == -1 ) continue;

        int endidx = str.find('\r',idx);
        string key = str.substr(0,idx);
        string val = str.substr(idx+1,endidx-idx-1);

        if( key=="ip"){
            _ip=val;
        }else if(key=="port"){
            _port = atoi(val.c_str());
        }else if(key == "username"){
            _username = val;
        }else if(key=="password"){
            _password=val;
        }else if(key=="initSize"){
            _initSize = atoi(val.c_str());
        } else if (key == "maxSize") {
            _maxSize = atoi(val.c_str());
        } else if (key == "maxIdleTime") {
            _maxIdleTime = atoi(val.c_str());
        } else if (key == "connectionTimeOut") {
            _connectionTimeOut = atoi(val.c_str());
        } else if (key == "dbname") {
            _dbname = val;
        }

    }
    return true;
}


MySQLConnPool::MySQLConnPool() {

    if(!loadConfigFile()){
        LOG("load config error!\n");
        return;
    }

    for( int i =0; i<_initSize; ++i ){
        MySQLConn *p = new MySQLConn();
        p->connect(_ip.c_str(),_port,_username,_password,_dbname);
        p->start();
        _connectionQue.push(p);
        _connectionCnt ++;
    }

    thread produce(bind(&MySQLConnPool::produceConnectionTask, this));
    produce.detach();

    thread scanner( bind(&MySQLConnPool::scannerConnectionTask, this));
    scanner.detach();

}


shared_ptr<MySQLConn> MySQLConnPool::getConnection(){
    unique_lock<mutex> lock(_queueMutex);
    while (_connectionQue.empty()) {
        if (cv_status::timeout == _cv.wait_for(lock, chrono::milliseconds(_connectionTimeOut))) {
            if (_connectionQue.empty()) {
                LOG("获取空闲连接超时，获取连接失败!\n");
                return nullptr;
            }
        }
    }
    /*
 *智能指针析构时，会直接把资源delete
 这里需要自定义shared_ptr释放资源的方式， 把connection归还到连接池中
 * */
    shared_ptr<MySQLConn> sp(_connectionQue.front(),
                             [&] (MySQLConn *con) {
                                  unique_lock<mutex> lock(_queueMutex);
                                  con->start();
                                  _connectionQue.push(con);
                              });

    _connectionQue.pop();
    if (_connectionQue.empty()) {
        // 谁消费了队列中的最后一个连接，同时生产者生产线程
        _cv.notify_all();
    }
    return sp;
}


void MySQLConnPool::produceConnectionTask(){
    for(;;){
        unique_lock<mutex> lock(_queueMutex);
        while(!_connectionQue.empty()){
            _cv.wait(lock);
        }

        //
        if(_connectionCnt < _maxSize ){
            MySQLConn* p = new MySQLConn();
            p->connect(_ip, _port, _username, _password, _dbname);
            p->start();
            _connectionQue.push(p);
            _connectionCnt ++;
        }
        _cv.notify_all();
    }
}


void MySQLConnPool::scannerConnectionTask() {
    for(;;){
        this_thread::sleep_for(chrono::seconds(_maxIdleTime));

        unique_lock<mutex> lock(_queueMutex);
        while(_connectionCnt > _initSize){
            MySQLConn *p = _connectionQue.front();
            if(p->end()>(_maxIdleTime*1000) ){
                _connectionQue.pop();
                _connectionCnt --;
                delete p;
            }else{
                break;
            }
        }
    }
}