//
// Created by root on 17-11-17.
//
#include "search.h"
#include <stdio.h>


int main()
{
    RecNode RNode[MAXNODENUM];
    KeyType a[] ={12,3,1,20};
//    printf("%ld",sizeof(a)/sizeof(a[0]));
//    printf("%ld",sizeof(RNode)/ sizeof(RNode[0]));
    int i ;
    int len = sizeof(a)/sizeof(a[0]);
    SeqTable st;
    st.length = len;
    for( i =1;i<=len ;i++)
    {
        st.elem[i].key = a[i-1];//RNode[0] 当成观察哨
    }
    printf("%d",SqSearch(st,1));

    return 0;
}