//
// Created by root on 17-12-2.
//
/**
    Desc:
    Follow up for ”Remove Duplicates”: What if duplicates are allowed at most twice?
    For example, Given sorted array A = [1,1,1,2,2,3],
    Your function should return length = 5, and A is now [1,1,2,2,3]
 */
#include <iostream>
using std::endl;
using std::cout;


void printArr(int A[], int len)
{
    for( int i = 0; i<len;i++)
    {
        cout<<A[i]<<" ";
    }
}


class Solution{
public:
    int removeDuplicates(int A[],int n)
    {
        if(n<=2) return n;
        int index = 2;
        for(int i = 2;i<n;i++)
        {
            if(A[i] != A[index-2])
                A[index++]=A[i];
                //index-2      i
                //1        2   2   2 3 3 4 4 5 6 6
        }
        return index;
    }
};

void code1(){
    int A[] ={1,2,2,2,3,3,4,4,5,6,6};
    int len = (sizeof(A) / sizeof(A[0]));
    Solution *s = new Solution();
    printArr(A,len);
    cout<<endl;
    int newlen = s->removeDuplicates(A,len);
    cout<<"new arr len = "<<newlen<<endl;
    printArr(A,newlen);
}
//////////////////////////////////////////////////////////


class Solution2{
public:
    int removeDuplicates(int A[], int n)
    {
        int index = 0;
        for(int i = 0;i< n;++i)
        {
            if(i>0 && i<n-1 && A[i]==A[i-1] && A[i]==A[i+1])
                continue;
            //       index              i
            //1,  2   ,2,  2,2,2,2,  2, 2, 3,3,4,4,5,6,6

            A[index++] = A[i];
        }
        return index;
    }
};


void code2(){
    int A[] ={1,2,2,2,2,2,2,2,2,3,3,4,4,5,6,6};
    int len = (sizeof(A) / sizeof(A[0]));
    Solution2 *s = new Solution2();
    printArr(A,len);
    cout<<endl;
    int newlen = s->removeDuplicates(A,len);
    cout<<"new arr len = "<<newlen<<endl;
    printArr(A,newlen);
}

int main()
{
//    code1();
    code2();
    return 0;
}