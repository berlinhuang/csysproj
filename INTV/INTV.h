//
// Created by root on 17-11-19.
//

#ifndef CSYSPROJ_INTV_H
#define CSYSPROJ_INTV_H

#define  FLAG -1
typedef int elemtype;
typedef struct node
{
    elemtype data;
    struct node * next;
}LNode, *LinkList;

LinkList InitLinkList_headnode();
LinkList CreateLinkList_headnode();
LinkList CreateListFromHead_headnode();//带头结点的头插法
LinkList CreateListFromTail_headnode();//带头结点的尾插法
void PrnLinkList_headnode(LinkList H);//带头结点的输出
int LenList_headnode(LinkList L);//带头结点的求表长算法
void reverse_headnode(LinkList H);

////////////////////////////////////////////////////
LinkList InitLinkList();//初始化不带头结点的链表
LinkList CreateNoHeadList();//不带头结点的单链表创建
LinkList CreateListFromHead();//不带头结点的头插法
LinkList CreateListFromTail();//不带头结点的尾插法
void PrnLinkList(LinkList H);//不带头结点的输出
int LenList(LinkList L);//不带头结点的求表长算法
LinkList reverse1(LinkList H);//不带头结点的链表逆置
void reverse2(LinkList *H);//不带头结点的逆置，二重指针

LinkList MergerLinkList(LinkList La,LinkList Lb);//升序序链表 合并为升序
///////////////////////////////////////////////////////////////////////////////////////


int my_atoi(const char *str);


#endif //CSYSPROJ_INTV_H
