// 二叉树的性质：
// 1.第i层的结点总数至多有2^(i-1)个结点（i >= 1）
// 2.深度为k的二叉树至多有2^(k)-1个结点（k >= 1)
// 3.叶子结点数为n0，度为2的结点数为n2，n0 = n2 + 1
// 4.高度为h的二叉树至多有2^(h)-1个结点（h >= 1)
// 5.具有n个结点的完全二叉树的深度为⌊log2n⌋+1
#include <stdio.h>
#include <stdlib.h>

#define TRUE        1
#define FALSE       0
#define OVERFLOW   -1

typedef int ElemType;
typedef int Status;

// 二叉树的二叉链表存储结构
typedef struct BiTNode {
    ElemType data;                  // 结点数据域
    struct BiTNode* lchild;         // 左孩子结点
    struct BiTNode* rchild;         // 右孩子结点
}BiTNode, *BiTree;

/**************************栈方法****************************/

typedef BiTNode* StackElemType;

// 链栈的存储结构
typedef struct StackNode{
    StackElemType data;         // 数据域
    struct StackNode* next;     // 指针域
}StackNode, *LinkStack;

//栈的函数定义
Status InitStack(LinkStack &S)
{   // 生成新结点作为头结点
    S = (StackNode*)malloc(sizeof(StackNode));
    
    if(S == NULL) {             // 内存分配失败
        exit(OVERFLOW);
    }
 
    S->next = NULL ;
}

// 入栈
Status Push(LinkStack &S, StackElemType e)
{   // 生成新结点
    LinkStack q = (StackNode*)malloc(sizeof(StackNode)) ;
    
    if(q == NULL) {             // 内存分配失败
        exit(OVERFLOW);
    }
    
    // 前插法
    q->data = e ;
    q->next = S->next ;
    S->next = q ;
}

// 出栈
Status Pop(LinkStack &S, StackElemType &e)
{
    LinkStack  q = NULL;

    if(S->next != NULL) {
        q = S->next ;
        e = q->data ;
        S->next = q->next ;
        free(q) ;
    }
}
 
// 判空
Status StackEmpty(LinkStack &S)
{
    if(S->next == NULL) {
        return TRUE;
    }

    return FALSE;
}

/**************************二叉树方法****************************/

// 访问根结点
void Visit(BiTree T)
{
    printf("%d ", T->data);
}

// 先序遍历
void PreOrderTraverse(BiTree T)
{
    if (T != NULL) {
        Visit(T);                       // 访问根结点
        PreOrderTraverse(T->lchild);    // 递归遍历左子树
        PreOrderTraverse(T->rchild);    // 递归遍历右子树
    }
}

// 中序遍历
void InOrderTraverse(BiTree T)
{
    if (T != NULL) {
        InOrderTraverse(T->lchild);     // 递归遍历左子树
        Visit(T);                       // 访问根结点
        InOrderTraverse(T->rchild);     // 递归遍历右子树
    }
}

// 中序遍历非递归算法
// 需要借助一个栈
void InOrderTraverseNonRecursion(BiTree T)
{   LinkStack S = NULL;
    InitStack(S);                       // 初始化栈
    BiTree p = T;                       // p是遍历指针
    
    while (p || !StackEmpty(S)) {       // 栈不空或p不空时循环
        if (p != NULL) {                // 根指针进栈，遍历左子树
            Push(S, p);
            p = p->lchild;              // 每遇到非空二叉树先向左走
        } else {                        
            Pop(S, p);                  // 退栈
            Visit(p);                   // 访问根结点
            p = p->rchild;              // 再向右子树走
        }
    }
}

// 后序遍历
void PostOrderTraverse(BiTree T)
{
    if (T != NULL) {
        PostOrderTraverse(T->lchild);   // 递归遍历左子树
        PostOrderTraverse(T->rchild);   // 递归遍历右子树
        Visit(T);                       // 访问根结点
    }
}