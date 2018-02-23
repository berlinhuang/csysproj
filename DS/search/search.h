//
// Created by root on 17-11-17.
//

#ifndef CSYSPROJ_SEARCH_H
#define CSYSPROJ_SEARCH_H

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

int SqSearch(SeqTable st, KeyType kx);
int BinSearch(SeqTable st, KeyType kx);

#endif //CSYSPROJ_SEARCH_H
