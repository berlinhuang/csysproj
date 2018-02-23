//
// Created by root on 18-2-23.
//

#include "BinTree.h"
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