//
// Created by root on 17-11-17.
//

#include "sort.h"
#include <stdio.h>




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




void InsertSort(RecNode r[], int n)
{
    int  i,j;
    for(i=2;i<=n;i++)
    {
        r[0] = r[i];
        for(j=i-1;r[0].key<r[j].key;j--)
            r[j+1]=r[j];
        r[j+1]=r[0];
    }
}


void BinInseSort(RecNode r[], int n)
{
    int i, j, low, high, mid;
    for (i = 2; i <= n; i++)
    {
        r[0]=r[i];
        low =1;
        high=i-1;
        while(low<=high)
        {
            mid=(low+high)/2;
            if(r[0].key<r[mid].key)
                high = mid -1;
            else
                low = mid + 1;
        }
        for(j=i-1;j>=low;j--)
            r[j+1]=r[j];
        r[low] =r[0];
    }
}


void BubbleSort( RecNode r[], int n)
{
    int i,j;
    int swap;
    for(i=1;i<n;i++)
    {
        swap = 0;
        for(j=1;j<=n-i;j++)
            if(r[j].key>r[j+1].key)
            {
                r[0]=r[j+1];
                r[j+1]=r[j];
                r[j]=r[0];
                swap = 1;
            }
        if(swap == 0)
            break;
    }
}


void SelectSort(RecNode r[],int n)
{
    int i,j,k;
    for(i=1;i<n;i++)
    {
        k=i;
        for(j=i+1;j<=n;j++)
        {
            if(r[j].key<r[k].key)
                k=j;
        }
        if(k!=i)
        {
            r[0]=r[k];
            r[k]=r[i];
            r[i]=r[0];
        }
    }
}

