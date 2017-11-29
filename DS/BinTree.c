//
// Created by root on 17-11-29.
//
//#include <stdio.h>
//#include <malloc.h>
//
//typedef int elemtype;
//typedef struct node
//{
//    elemtype data;
//    struct node * lchild;
//    struct node * rchild;
//    // struct node * parent;//三叉链表
//} BinNode,*BinTree;
//
////初始化带头结点
//BinTree InitTree()
//{
//    BinTree bt;
//    bt=(BinTree)malloc(sizeof(BinNode));
//    if (bt==NULL) return NULL;
//    bt->lchild=NULL;
//    bt->rchild=NULL;
//    return bt;
//}
//
////初始化不带头结点
////BinTree bt=NULL;
//void Visited(BinTree bt)
//{
//    printf(" %d ",bt->data);
//}
//
//void PreOrder(BinTree bt)
//{
//    if (bt==NULL) return ;
//    Visited(bt);//访问bt指向的结点
//    PreOrder(bt->lchild);
//    PreOrder(bt->rchild);
//}
//
//void InOrder(BinTree bt)
//{
//    if (bt==NULL) return ;
//    InOrder(bt->lchild);
//    Visited(bt);//访问bt指向的结点
//    InOrder(bt->rchild);
//}
//
//void PostOrder(BinTree bt)
//{
//    if (bt==NULL) return ;
//    PostOrder(bt->lchild);
//    PostOrder(bt->rchild);
//    Visited(bt);//访问bt指向的结点
//}


#include <stdio.h>
#include <stdlib.h>
#define MAXNODE 100

//二叉链表的存储结构
typedef char datatype;
typedef struct node
{
    datatype data;
    struct node *lchild,*rchild;
} BinNode,*BinTree;

//定义栈的存储结构
typedef struct
{
    BinTree link;
    int flag;
}StackType;

//先序遍历输入二叉树
void CreateBinTree(BinTree *t)
{
    char ch;
    ch=getchar();
//    printf("%d",ch);
    if (ch=='\n')
    {
        *t=NULL;
        return;
    }
    (*t)=(BinNode *)malloc(sizeof(BinNode));
    (*t)->data=ch;
    CreateBinTree(&((*t)->lchild));
    CreateBinTree(&((*t)->rchild));
}

//先序遍历输出二叉树
void PreOrder(BinTree bt)
{
    if (bt==NULL) return;
    printf(" %c ",bt->data);
    PreOrder(bt->lchild);
    PreOrder(bt->rchild);
}

//中序遍历输出二叉树
void InOrder(BinTree bt)
{
    if (bt==NULL) return;
    InOrder(bt->lchild);
    printf(" %c ",bt->data);
    InOrder(bt->rchild);
}

//后序遍历输出二叉树
void PostOrder(BinTree bt)
{
    if (bt==NULL) return ;
    PostOrder(bt->lchild);
    PostOrder(bt->rchild);
    printf(" %c ",bt->data);
}

void Visited(BinTree bt)
{
    printf(" %c ",bt->data);
}


//层次遍历二叉树
void LevelOrder(BinTree bt)
{
    BinNode *Queue[MAXNODE];
    int front,rear;
    if (bt==NULL) return;
    front=-1;
    rear=0;
    Queue[rear]=bt;
    while(front!=rear) //队列非空时
    {
        front++;//出队列
        Visited (Queue[front]); //访问队首结点的数据域
        if (Queue[front]->lchild!=NULL) //将队首结点的左孩子结点入队列
        {
            rear++;
            Queue[rear]= Queue[front] ->lchild;
        }
        if (Queue[front]->rchild!=NULL)//将队首结点的右孩子结点入队列
        {
            rear++;
            Queue[rear]= Queue[front]->rchild;
        }
    }
}

//非递归先序遍历二叉树
void NRPreOrder(BinTree bt)
{
    BinTree p,stack[MAXNODE];
    int top=0;
    if(bt==NULL) return;
    p=bt;
    while(!(p==NULL&&top==0))
    {
        while(p!=NULL)
        {
            printf("%c",p->data);//访问结点的数据域
            if(top<MAXNODE-1)
            {
                stack[top]=p;//将当前指针p压栈
                top++;
            }
            else
            {
                printf("栈溢出");
                return;
            }
            p=p->lchild;//指针指向p的左孩子
        }
        if(top<=0) return;//栈空时结束
        else
        {
            top--;
            p=stack[top];//从栈中弹出栈顶元素
            p=p->rchild;//指针指向p的右孩子结点
        }
    }
}

//非递归中序遍历二叉树
void NRInOrder(BinTree bt)
{
    BinTree p,stack[MAXNODE];
    int top=0;
    if(bt==NULL) return;
    p=bt;
    while(!(p==NULL&&top==0))
    {
        while(p!=NULL)
        {
            if(top<MAXNODE-1)
            {
                stack[top]=p;
                top++;
            }
            else
            {
                printf("栈溢出");
                return;
            }
            p=p->lchild;
        }
        if(top<=0) return;
        else
        {
            top--;
            p=stack[top];
            printf("%c",p->data);
            p=p->rchild;
        }
    }
}


//非递归后序遍历二叉树
void NRPostOrder(BinTree bt) {
    StackType stack[MAXNODE];
    BinTree p;
    int top, sign;
    if (bt == NULL) return;
    top = -1;//栈顶位置初始化
    p = bt;
    while (!(p == NULL && top == -1)) {
        if (p != NULL)//结点第一次进栈
        {
            top++;
            stack[top].link = p;
            stack[top].flag = 1;
            p = p->lchild;//找出结点的左孩子
        } else {
            p = stack[top].link;
            sign = stack[top].flag;
            top--;
            if (sign == 1)//结点第二次进栈
            {
                top++;
                stack[top].link = p;
                stack[top].flag = 2;//标记第二次出栈
                p = p->rchild;
            } else {
                printf("%c", p->data);//访问节点的数据域
                p = NULL;
            }
        }
    }
}

//二叉树查找
BinNode *Search(BinTree bt,datatype x)
{
    BinNode *p;
    if (bt==NULL) return NULL;
    if (bt->data==x) return bt;
    if (bt->lchild!=NULL)
    {
        p= Search(bt->lchild,x);
    }
    if (p!=NULL) return p;
    if (bt->rchild!=NULL)
    {
        p= Search(bt->rchild,x);
    }
    if (p!=NULL) return p;
}

//利用全局变量计算二叉树叶子
int c=0;
void countleaf1(BinTree bt)
{
    if (bt==NULL) return;
    if(bt->lchild==NULL &&bt->rchild==NULL)
        c++;
    countleaf1(bt->lchild);
    countleaf1(bt->rchild);
}

int countleaf2(BinTree bt)
{
    if (bt==NULL) return 0;
    if(bt->lchild==NULL &&bt->rchild==NULL)
        return 1;
    return countleaf2(bt->lchild)+countleaf2(bt->rchild);
}

//计算二叉树深度
int Depth(BinTree bt)
{
    int lh,rh;
    if (bt==NULL) return 0;
    lh=Depth(bt->lchild);
    rh=Depth(bt->rchild);
    return (lh>rh?lh+1:rh+1);
}


//凹入法输出二叉树
void AoRuFa(BinTree bt,int L)
{
    int i;
    if (bt==NULL)
        return;
    for(i=0;i<3*L;i++)
        printf("  ");
    printf("%c",bt->data);
    for(i=0;i<15-3*L;i++)
        printf("■");
    printf("\n");
    AoRuFa(bt->lchild,L+1);
    AoRuFa(bt->rchild,L+1);
}
//主函数

int main()
{
    BinTree bt;
    printf("输入一串字符\n");
    CreateBinTree(&bt);
    printf("先序遍历\n");
    PreOrder(bt);
    printf("\n中序遍历\n");
    InOrder(bt);
    printf("\n后序遍历\n");
    PostOrder(bt);
    printf("\n凹入法输出二叉树：\n");
    AoRuFa(bt,0);
    printf("\n非递归先序遍历:\n");
    NRPreOrder(bt);
    printf("\n非递归中序遍历:\n");
    NRInOrder(bt);
    printf("\n非递归后序遍历:\n");
    NRPostOrder(bt);
    printf("\n层次遍历\n");
    LevelOrder(bt);
    printf("\n叶子数为%d\n",countleaf2(bt));
    printf("\n深度为%d\n",Depth(bt));
    return 0;
}