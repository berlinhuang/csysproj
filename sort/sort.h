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

typedef struct
{
    RecNode elem[MAXNODENUM];
    int length;
}SeqTable;


int Partition(RecNode r[], int low, int high );

void InsertSort(RecNode r[], int n);
void QuickSort( RecNode r[], int m, int n);

#endif //CSYSPROJ_SORT_H
