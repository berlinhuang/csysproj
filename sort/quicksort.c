//
// Created by root on 17-11-14.
//
#include <stdio.h>
#define MAXNODENUM  1000


typedef int KeyType;
typedef struct
{
    KeyType key;

}RecNode;

typedef struct
{
    RecNode elem[MAXNODENUM];
    int length;
}SqTable;





int Partition(RecNode r[], int low, int high )
{
    if (low > high) return 0;
    if (low==high) return low;

//    r[0] = r[low];
    RecNode x = r[low];//拿最小的来作为比较的基点 找寻存放的位置
    while(low<high)
    {
        //
        while( low<high && r[high].key >= x.key )//比x大下标high往左边移动
            high--;
        if(low<high)
        {
            r[low]=r[high];//将比x键值小的记录移到低端
            low++;
        }
        while( low<high && r[low].key<x.key)//比x小下标low往右边移动
            low++;
        if(low<high)
        {
            r[high]=r[low];//将比x键值大的记录移到高端
            high--;
        }
    }
    r[low] = x;//找到x 存放的点low 左边都比x小，右边都比x大
    return low;
}

void QuickSort( RecNode r[], int m, int n)
{
    int i;
    if(m<n)
    {
        i = Partition(r,m,n);
        QuickSort(r,m,i-1);
        QuickSort(r,i+1,n);
    }
}


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