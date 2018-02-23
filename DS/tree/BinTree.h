//
// Created by root on 18-2-23.
//

#ifndef CSYSPROJ_BINTREE_H
#define CSYSPROJ_BINTREE_H

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
void CreateBinTree(BinTree *t);
//先序遍历输出二叉树
void PreOrder(BinTree bt);
//中序遍历输出二叉树
void InOrder(BinTree bt);
//后序遍历输出二叉树
void PostOrder(BinTree bt);

void Visited(BinTree bt);

//层次遍历二叉树
void LevelOrder(BinTree bt);

//非递归先序遍历二叉树
void NRPreOrder(BinTree bt);

//非递归中序遍历二叉树
void NRInOrder(BinTree bt);

//非递归后序遍历二叉树
void NRPostOrder(BinTree bt);

//二叉树查找
BinNode *Search(BinTree bt,datatype x);

//利用全局变量计算二叉树叶子
void countleaf1(BinTree bt);
int countleaf2(BinTree bt);

//计算二叉树深度
int Depth(BinTree bt);


//凹入法输出二叉树
void AoRuFa(BinTree bt,int L);

#endif //CSYSPROJ_BINTREE_H
