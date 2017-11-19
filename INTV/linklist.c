//
// Created by root on 17-11-19.
//

#include "INTV.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    LinkList L,L1,L2;
    printf("请输入第一个链表的数据，升序并以-1结束：\n");
    L1=CreateLinkList_headnode();
    printf("第一个链表为：\n");
    PrnLinkList_headnode(L1);
//    printf("len of L1:%d \n",LenList_headnode(L1));
//    printf("reverse：\n");
//    reverse_headnode(L1);
//    PrnLinkList_headnode(L1);
    printf("请输入第二个链表的数据，升序并以-1结束：\n");
    L2=CreateLinkList_headnode();
    printf("第二个链表为：\n");
    PrnLinkList_headnode(L2);
    L=MergerLinkList(L1,L2);
    printf("合并后的升序链表为：\n");
    PrnLinkList_headnode(L);
    system("pause");
    return 0;
}

//
//
//int main()
//{
//    LinkList L,L1,L2;
//    printf("请输入第一个链表的数据，升序并以-1结束：\n");
//    L1=CreateNoHeadList();
//    printf("第一个链表为：\n");
//    PrnLinkList(L1);
//    printf("len of L1:%d \n",LenList(L1));
//    printf("reverse：\n");
//    reverse2(&L1);
//    PrnLinkList(L1);
//    system("pause");
//    return 0;
//}




