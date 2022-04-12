//
// Created by root on 17-11-17.
//

#include "sort.h"
#include <stdio.h>

/**
 * 插入排序
 * @param r
 * @param n
 */
void InsertSort(RecNode r[], int n)  //stable
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
/**
 * 二分插入排序
 * @param r
 * @param n
 */
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

/**
 * 希尔排序（缩小增量排序）
 * @param r
 * @param n
 */
void ShellSort(RecNode r[], int n)   // no stable
{
    printf("-----------------------total element=%d\n",n);
    int i,j, dk;//dk记录前后位置的增量
    int t = 0;
    dk = n/2;
    while(dk>0)//一趟增量为dk的插入排序
    {
        printf("-----------------------dk=%d\n",dk);
        for(i = dk+1;i<=n;++i)
        {
            printf("---------------i=%d\n",i);
            if(r[i].key < r[i-dk].key)//将r[i]插入有序增量子表
            {
                r[0]=r[i];//r[0]为暂存单元(    a.......b.......   //r[0] = r[b])     ***************
                for(j=i-dk;         j>0 && r[0].key<r[j].key;        j-=dk)
                {
                    printf("--insert j=%d\n",j);
                    r[j+dk] = r[j];//记录后移，查找插入位置     //r[b] = r[a]     ***************
                }
                r[j+dk]=r[0];//r[a] = r[b]   cause j-=dk      ***************
            }
        }
        dk=dk/2;//增量改为原来的一半
        t++;
    }
}



///////////////////////////////////////////////////////////////////////////////////
//swap sort
/**
 * 冒泡排序
 * @param r
 * @param n
 */
void BubbleSort( RecNode r[], int n)  //stable
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


///////////////////////////////////////////////////////////////////////////////////

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
/**
 * 堆排序
 * @param r
 * @param m
 * @param n
 */
void QuickSort( RecNode r[], int m, int n)   //no stable
{
    int i;
    if(m<n)
    {
        i = Partition(r,m,n);
        QuickSort(r,m,i-1);
        QuickSort(r,i+1,n);
    }
}

///////////////////////////////////////////////////////////////////////////////////////

/**
 * 选择排序
 * @param r
 * @param n
 */
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




void Sift(RecNode r[],int i,int m)
{
    int j;
    RecNode temp;
    temp=r[i];
    j=2*i;

    while(j<=m) //沿key较大的孩子结点向下筛选
    {
        if(j<m && (r[j].key<r[j+1].key)) //j为key较大的记录的下标
        {
            j++;
        }
        if(temp.key<r[j].key)
        {
            r[i]=r[j];
            i=j;
            j=2*i;
        }
        else
            break;
    }
    r[i]=temp;
}

/**
 * 堆排序
 * @param r
 * @param n
 */
void HeapSort( RecNode r[], int n)
{
    int i;
    RecNode tmp;
    for(i = n/2;i>=1;--i)
    {
        Sift(r,i,n);
    }
    for(i=n;i>=2;--i)
    {
        tmp = r[1];
        r[1] = r[i];
        r[i] =tmp;
        Sift(r,1,i-1);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void merge(RecNode r[], int low, int m, int high)
{
    RecNode rs[MAXNODENUM];
    int i, j, k;
    i = low;
    j = m+1;
    k = 0;
    while(i<=m && j<= high)
        if(r[i].key<= r[j].key)
        {
            rs[k] = r[i];
            i++;
            k++;
        }
        else
        {
            rs[k] = r[j];
            j++;
            k++;
        }
    while(i<=m)
    {
        rs[k] = r[i];
        i++;
        k++;
    }
    while(j<=high)
    {
        rs[k]=r[j];
        j++;
        k++;
    }
    for(i=low,k=0;i<=high;i++,k++)
        r[i] = rs[k];
}

void merge_one( RecNode r[], int len, int n)
{
    int i = 0;
    while(i+2*len-1<n)
    {
        merge(r,i,i+len-1,i+2*len-1);
        i=i+2*len;
    }
    if(i+len-1<n-1)
        merge(r,i,i+len-1,n-1);
}
/**
 * 归并排序
 * @param r
 * @param n
 */
void MergeSort(RecNode r[], int n)
{
    int len = 1;
    while(len< n)
    {
        merge_one(r,len,n);
        len = 2*len;
    }
}