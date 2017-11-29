//
// Created by root on 17-11-17.
//

#ifndef CSYSPROJ_SORT_H
#define CSYSPROJ_SORT_H

#define MAXNODENUM  1000

typedef int KeyType;
typedef struct
{
    KeyType key;

}RecNode;

//insert sort
void InsertSort( RecNode r[], int n);
void BinInseSort( RecNode r[], int n);//折半插入 排序
void ShellSort( RecNode r[], int n);

//swap sort
void BubbleSort( RecNode r[], int n);
void QuickSort( RecNode r[], int m, int n);

//select sort
void SelectSort( RecNode r[], int n);
void HeapSort( RecNode r[], int n);


//merge
void MergeSort(RecNode r[], int n);

//base

#endif //CSYSPROJ_SORT_H
