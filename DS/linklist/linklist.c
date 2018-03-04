//
// Created by root on 17-11-19.
//

#include "linklist.h"
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdlib.h>

LinkList  InitLinkList_headnode()
{
    LinkList H;
    H = (LinkList)malloc(sizeof(LNode));
    H->next = NULL;
    return H;
}

LinkList CreateLinkList_headnode()
{
    LinkList L;
    LNode *s,*r;
    elemtype x;
    L=(LinkList )malloc(sizeof(LNode));
    L->next=NULL;
    r=L;
    scanf("%d",&x);
    while(x!=FLAG)
    {
        s=(LNode *)malloc(sizeof(LNode));
        s->data=x;
        // if(L==NULL) L=s;
        // else
        r->next=s;
        r=s;
        scanf("%d",&x);
    }
    if(r!=NULL)r->next=NULL;
    return (L);
}

LinkList CreateListFromHead_headnode()
{
    elemtype x;
    LNode *s;
    LinkList H;
    H=InitLinkList_headnode();
    scanf("%d",&x);
    while(x!=FLAG)
    {
        s=(LinkList )malloc(sizeof(LNode));
        s->data=x;
        s->next=H->next;//让s指空
        H->next=s;//将s接到H
        scanf("%d",&x);
    }
    return H;
}

LinkList CreateListFromTail_headnode()
{
    elemtype x;
    LNode *s,*r;
    LinkList H;
    H=InitLinkList_headnode();
    r=H;
    scanf("%d",&x);
    while(x!=FLAG)
    {
        s=(LinkList )malloc(sizeof(LNode));
        s->data=x;
        s->next=NULL;
        r->next=s;
        r=s;
        scanf("%d",&x);
    }
    return H;
}


//带头结点的输出
void PrnLinkList_headnode(LinkList H)
{
    LNode *p=H->next;
    while(p!=NULL)   //while(p)
    {
        printf("-->%d",p->data);
        p=p->next;
    }
    printf("\n");
}


//带头结点的求表长算法
int LenList_headnode(LinkList L)
{
    LNode *p=L->next;
    int len=0;
    while(p!=NULL)
    {
        len++;
        p=p->next;
    }
    return len;
}


void reverse_headnode(LinkList H)
{
    LNode  *p,*q;
    p=H->next;
    H->next=NULL;
    while(p)
    {
        q=p;
        p=p->next;
        //insert from head
        q->next=H->next;
        H->next=q;
    }
}

////////////////////////////////////////////////////////////////////////////////////////



//初始化不带头结点的链表
LinkList  InitLinkList()
{
    LinkList  H;
    H=NULL;
    return H;
}


//不带头结点的单链表创建
LinkList CreateNoHeadList()
{
    LinkList L=NULL;
    LNode *s,*r=NULL;
    elemtype x;
    scanf("%d",&x);
    while(x!=FLAG)
    {
        s=(LNode *)malloc(sizeof(LNode));
        s->data=x;
        if(L==NULL) L=s;
        else r->next=s;
        r=s;
        scanf("%d",&x);
    }
    if(r!=NULL) r->next=NULL;
    return (L);
}

//不带头结点的头插法
LinkList CreateListFromHead()
{
    elemtype x;
    LNode *s;
    LinkList H=NULL;
    scanf("%d",&x);
    while(x!=FLAG)
    {
        s=(LinkList )malloc(sizeof(LNode));
        s->data=x;
        s->next=H;
        H=s;
        scanf("%d",&x);
    }
    return H;
}


//不带头结点的尾插法
LinkList CreateListFromTail()
{
    elemtype x;
    LNode *s,*r=NULL;
    LinkList H=NULL;
    scanf("%d",&x);
    while(x!=FLAG)
    {
        s=(LinkList )malloc(sizeof(LNode));
        s->data=x;
        s->next=NULL;
        if(H==NULL) H=s;
        else r->next=s;
        r=s;
        scanf("%d",&x);
    }
    return H;
}


//不带头结点的输出
void PrnLinkList(LinkList H)
{
    LinkList p=H;  //LinkList p;p=H;
    while(p!=NULL)   //while (p)
    {
        printf("-->%d",p->data);
        p=p->next;
    }
    printf("\n");
}


//不带头结点的求表长算法
int LenList(LinkList L)
{
    LNode *p=L;
    int len=0;
    while(p!=NULL)
    {
        len++;
        p=p->next;
    }
    return len;
}


//不带头结点的链表逆置
LinkList reverse1(LinkList H)
{
    LNode  *p,*q;
    p=H;
    H=NULL;
    while(p)
    {
        q=p;
        p=p->next;
        q->next=H;
        H=q;
    }
    return H;
}

//不带头结点的逆置，二重指针
void reverse2(LinkList *H)
{
    LNode  *p,*q;
    p=(*H);
    (*H)=NULL;
    while(p)
    {
        q=p;
        p=p->next;
        q->next=(*H);
        (*H)=q;
    }
}

//带头结点的 升序序链表合并为升序
LinkList MergerLinkList(LinkList La,LinkList Lb)
{
    LNode*pa,*pb,*pc,*Lc ;
    pa=La->next;
    pb=Lb->next;
    Lc=pc=La;
    while(pa&&pb)
    {
        if(pa->data<=pb->data)
        {
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else
        {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
    pc->next=pa?pa:pb;
    free(Lb);
    return Lc;
}


/////////////////////////////////////////////////////////

int my_atoi(const char *str)
{
    int s=0;
    int falg=0;

    while(*str==' ')
    {
        str++;
    }
    if(*str=='-'||*str=='+')
    {
        if(*str=='-')
            falg=1;
        str++;
    }
    while(*str>='0'&&*str<='9')
    {
        s = s*10 + *str-'0';// *str-'0' = '3'-'0' = 3
        str++;
        if(s<0)
        {
            s=2147483647;//梅森素数 = 2^31-1
            break;
        }
    }
    return s*(falg?-1:1);
}