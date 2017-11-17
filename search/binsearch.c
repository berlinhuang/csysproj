//
// Created by root on 17-11-17.
//

#include "search.h"
#include <stdio.h>

int main()
{
    RecNode RNode[MAXNODENUM];
    KeyType a[] ={1,2,3,4,5,6,77};
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
    printf("%d",SqSearch(st,77));

    return 0;
}