//
// Created by root on 17-12-2.
//


/**

Desc:
    Given a sorted array, remove the duplicates in place such that each element appear only
    once and return the new length.
    Do not allocate extra space for another array, you must do this in place with constant memory.
    For example, Given input array A = [1,1,2],
    Your function should return length = 2, and A is now [1,2].

 */

#include <stdio.h>
#include <iostream>
#include <algorithm>
using std::cout ;
using std::endl;
using std::distance;
using std::unique;

void printArr(int A[],int len)
{
    for( int i = 0; i<len;i++)
    {
        cout<<A[i]<<" ";
    }
}

class Solution{
public:
    int removeDuplicates(int A[], int n)
    {
        if(n == 0 ) return 0;

        int index = 0;

        for(int i =1; i<n; i++)
        {
            if(A[index]!=A[i])
                A[++index] = A[i];
        }
        return index + 1;
    }

};



void code1()
{
    int A[] ={1,2,2,2,3,3,4,4,5,6,6};
    int len = (sizeof(A) / sizeof(A[0]));
    Solution *s = new Solution();
    printArr(A,len);
    cout<<endl;
    int newlen = s->removeDuplicates(A,len);
    cout<<"new arr len = "<<newlen<<endl;
    printArr(A,newlen);
}



//////////////////////////////////////////////////////////////
class Solution2{
public:
    int removeDuplicates(int A[],int n)
    {
        return distance(A,unique(A,A+n));//<algorithm>
    }
};



void code2()
{
    int A[] ={1,2,2,2,3,3,4,4,5,6,6};
    int len = (sizeof(A) / sizeof(A[0]));
    Solution2 *s = new Solution2();
    printArr(A,len);
    cout<<endl;
    int newlen = s->removeDuplicates(A,len);
    cout<<"new arr len = "<<newlen<<endl;
    printArr(A,newlen);
}

///////////////////////////////////////////////////////////////


class Solution3{
public:
    int removeDuplicates(int A[], int n)
    {
        return removeDuplicates(A,A+n,A) -A;
    }

    template<typename InIt, typename OutIt>
    OutIt removeDuplicates(InIt first, InIt last, OutIt output)
    {
        while(first !=last){
            *output++ = *first;
            /**
             *  template <class ForwardIterator, class T>
             *  ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val)
             *  //指向[first , last)中第一个>val的元素；需要保证[begin , end)中元素已经有序
             */
            first = std::upper_bound(first,last,*first);
        }
        return output;

    };
};


void code3()
{
    int A[] ={1,2,2,2,3,3,4,4,5,6,6};
    int len = (sizeof(A) / sizeof(A[0]));
    Solution3 *s = new Solution3();
    printArr(A,len);
    cout<<endl;
    int newlen = s->removeDuplicates(A,len);
    cout<<"new arr len = "<<newlen<<endl;
    printArr(A,newlen);
}



int main()
{

//    code1();
//    code2();
    code3();

    return 0;
}