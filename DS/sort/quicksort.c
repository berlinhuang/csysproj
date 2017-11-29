//
// Created by root on 17-11-14.
//
#include <stdio.h>
#include "sort.h"



int main()
{
    RecNode RNode[10];
    KeyType a[] ={12,3,1,20};
//    printf("%ld",sizeof(a)/sizeof(a[0]));
//    printf("%ld",sizeof(RNode)/ sizeof(RNode[0]));
    int i ;
    int len = sizeof(a)/sizeof(a[0]);
    for( i =0;i<len ;i++)
    {
        RNode[i].key = a[i];
    }
    QuickSort(RNode, 0, len-1);
    for( i = 0;i<len;i++)
    {
        printf("%d ",RNode[i].key);
    }

    return 0;
}