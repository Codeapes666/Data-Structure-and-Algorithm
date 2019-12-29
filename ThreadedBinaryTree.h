#include <stdlib.h>

#define OVERFLOW   -1

typedef int TElemType;

// 线索二叉树的存储结构
typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode* lchild;       // 左孩子指针
    struct BiThrNode* rchild;       // 右孩子指针
    int LTag;                       // 左线索标志
    int RTag;                       // 右线索标志
}BiThrNode, *BiThrTree;

BiThrTree pre = NULL;

// 访问根结点
void Visit(BiThrTree T)
{
    printf("%c ", T->data);
}

// 以结点p为根的子树中序线索化
void InThreading(BiThrTree p)
{
    if (p != NULL) {
        InThreading(p->lchild);

        if (p->lchild == NULL) {
            p->LTag = 1;
            p->lchild = pre;
        }
    } else {
        p->LTag = 0;
    }

    if (pre->rchild == NULL) {
        pre->RTag = 1;
        pre->rchild = p;
    } else {
        p->RTag = 0;
    }

    pre = p;
    InThreading(p->rchild);
}

// 带头结点的二叉树中序线索化
void InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
    Thrt = (BiThrNode*)malloc(sizeof(BiThrNode));

    if (Thrt == NULL) {
        exit(OVERFLOW);
    }

    Thrt->LTag = 0;
    Thrt->RTag = 1;
    Thrt->rchild = Thrt;

    if (T == NULL) {
        Thrt->lchild = Thrt;
    } else {
        Thrt->lchild = T;
        pre = Thrt;

        InThreading(T);
        pre->rchild = Thrt;
        pre->RTag = 1;
        Thrt->rchild = pre;
    }
}

// 遍历中序线索二叉树
void InOrderTraverseThr(BiThrTree T)
{
    BiThrTree p = T->lchild;

    while (p != T) {
        while (p->LTag == 0) {
            p = p->lchild;
        }

        Visit(p);

        while (p->RTag == 1 && p ->rchild != T) {
            p = p->rchild;
            Visit(p);
        }

        p = p->rchild;
    }
}