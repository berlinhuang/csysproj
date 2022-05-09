//
// Created by Berlin Huang on 2022/4/22 0022.
//

#include "mysql_conn.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cstring>
#include "mysql_conn.h"

#include <iostream>

using namespace std;

int main()
{
    Mysql* pInstall = Mysql::getInstancePtr();
    pInstall->connectToDatabase("192.168.31.232","berlin", "Berlin.4399", "mysql");
    pInstall->exec("select * from user");
    cout << "行数:" << pInstall->rowCount() << endl;
    cout << "列数:" << pInstall->columnCount() << endl;
    while(pInstall->next())
    {
        for(int i = 0;i < pInstall->columnCount();++i)
        {
            cout << pInstall->values(i) << " ";
        }
        cout << endl;
    }

    return 0;
}
