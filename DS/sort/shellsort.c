//
// Created by root on 17-11-18.
//




#include "sort.h"
#include <stdio.h>


int main()
{
    RecNode RNode[10];
    KeyType a[] ={12,7,1,20,5,6,3,2,40,39};
//    printf("%ld",sizeof(a)/sizeof(a[0]));
//    printf("%ld",sizeof(RNode)/ sizeof(RNode[0]));
    int i ;
    int len = sizeof(a)/sizeof(a[0]);
    for( i =1;i<=len ;i++)
    {
        RNode[i].key = a[i-1];//RNode[0] 当成观察哨
    }
    ShellSort(RNode,len);
    for( i = 1;i<=len;i++)
    {
        printf("%d ",RNode[i].key);
    }

    return 0;
}