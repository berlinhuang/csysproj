//
// Created by root on 17-11-17.
//

#include "search.h"

int SqSearch(SeqTable st, KeyType kx)
{
    int i = st.length;
    st.elem[0].key = kx;
    while(st.elem[i].key!=kx)
        i--;
    return i;
}


int BinSearch(SeqTable st, KeyType kx)
{
    int mid;
    int low = 1;
    int high = st.length;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(kx==st.elem[mid].key)
            return mid;
        if(kx>st.elem[mid].key)
            low = mid+1;
        else
            high = mid -1;
    }
    return 0;
}