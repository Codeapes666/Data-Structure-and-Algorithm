// 二叉树的性质：
// 1.第i层的结点总数至多有2^(i-1)个结点（i >= 1）
// 2.深度为k的二叉树至多有2^(k)-1个结点（k >= 1)
// 3.叶子结点数为n0，度为2的结点数为n2，n0 = n2 + 1
// 4.高度为h的二叉树至多有2^(h)-1个结点（h >= 1)
// 5.具有n个结点的完全二叉树的深度为⌊log2n⌋+1
#include <stdio.h>
#include <stdlib.h>

#define OK          1
#define ERROR       0
#define TRUE        1
#define FALSE       0
#define OVERFLOW   -1

typedef char TElemType;
typedef int Status;

// 二叉树的二叉链表存储结构
typedef struct BiTNode {
    TElemType data;                 // 结点数据域
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

//栈的初始化
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

    return OK;
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

    return OK;
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

// 构造二叉树
Status CreateBiTree(BiTree &T)
{
    char ch;

    scanf("%c", &ch);

    if (ch == '#') {                    // ch是一个“#”字符，表明该二叉树为空树
        T = NULL;
    } else {
        T = (BiTNode*)malloc(sizeof(BiTNode));  // 生成根结点

        if (T == NULL) {                // 根结点内存分配失败
            exit(OVERFLOW);
        }

        T->data = ch;                   // 根结点数据域置为ch

        CreateBiTree(T->lchild);        // 递归创建左子树
        CreateBiTree(T->rchild);        // 递归创建右子树
    }
    
    return OK;
}

// 复制二叉树
Status CopyBiTree(BiTree T, BiTree &NewT)
{   // 复制一棵和T完全相同的二叉树
    if (T == NULL) {                            // 如果是空树，递归结束
        NewT = NULL;
        return ERROR;
    } 

    NewT = (BiTNode*)malloc(sizeof(BiTNode));   // 生成一个新结点

    if (NewT == NULL) {                     // 如果结点内存分配失败
        exit(OVERFLOW);
    }

    NewT->data = T->data;                   // 复制根结点
    CopyBiTree(T->lchild, NewT->lchild);    // 递归复制左子树
    CopyBiTree(T->rchild, NewT->rchild);    // 递归复制右子树
    
    return OK;
}

// 计算二叉树T的深度
int BiTreeDepth(BiTree T)
{
    if (T == NULL) {
        return ERROR;                       // 如果是空树，深度为0，递归结束
    } 

    int m = BiTreeDepth(T->lchild);         // 递归计算左子树的深度记为m
    int n = BiTreeDepth(T->rchild);         // 递归计算左子树的深度记为n

    if (m > n) {                            // 二叉树的深度为m与n的较大者加1
        return (m + 1);                                            
    } else {
        return (n + 1);
    }

}

// 统计二叉树中结点的个数
int NodeCount(BiTree T)
{
    if (T == NULL) {                // 如果是空树，则结点个数为0，递归结束
        return ERROR;
    } 

    // 结点个数为左子树的结点个数 + 右子树的结点个数 + 1
    return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

// 访问根结点
void Visit(BiTree T)
{
    printf("%c ", T->data);
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