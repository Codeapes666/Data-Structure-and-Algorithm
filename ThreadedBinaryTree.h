#include <stdio.h>
#include <stdlib.h>

#define OVERFLOW   -1

typedef char TElemType;

// 线索二叉树的存储结构
typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode* lchild;       // 左孩子指针
    struct BiThrNode* rchild;       // 右孩子指针
    int LTag;                       // 左线索标志，0：lchild域指示结点的左孩子，1：lchild域指示结点的前驱
    int RTag;                       // 右线索标志，0：rchild域指示结点的右孩子，1：rchild域指示结点的后继
} BiThrNode, *BiThrTree;

// pre是全局变量，初始化时其右孩子指针为空，便于在树的最左点开始建线索
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
        InThreading(p->lchild);         // 左子树递归线索化

        if (p->lchild == NULL) {        // p的左孩子为空
            p->LTag = 1;                // 给p加上左线索
            p->lchild = pre;            // p的左孩子指针指向pre（前驱）
        }
    } else {
        p->LTag = 0;
    }

    if (pre->rchild == NULL) {          // pre的右孩子为空
        pre->RTag = 1;                  // 给pre加上右线索
        pre->rchild = p;                // pre的右孩子指针指向p（后继）
    } else {
        p->RTag = 0;
    }

    pre = p;                            // 将pre指向刚访问过的结点p
    InThreading(p->rchild);             // 右子树递归线索化
}

// 带头结点的二叉树中序线索化
void InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{   // 中序遍历二叉树T，并将其中序线索化，Thrt指向头结点
    Thrt = (BiThrNode*)malloc(sizeof(BiThrNode));   // 生成头结点

    if (Thrt == NULL) {                 // 结点空间分配失败
        exit(OVERFLOW);
    }

    Thrt->LTag = 0;                     // 头结点有左孩子，若树非空，则其左孩子为树根
    Thrt->RTag = 1;                     // 头结点的右孩子指针为右线索
    Thrt->rchild = Thrt;                // 初始化时右指针指向自己

    if (T == NULL) {                    // 若树为空，则左指针也指向自己
        Thrt->lchild = Thrt;
    } else {
        Thrt->lchild = T;               // 头结点的左孩子指向根       
        pre = Thrt;                     // pre初值指向头结点

        InThreading(T);                 // 对以T为根的二叉树进行中序线索化
        pre->rchild = Thrt;             // pre为最右结点，pre的右线索指向头结点
        pre->RTag = 1;
        Thrt->rchild = pre;             // 头结点的右线索指向pre
    }
}

// 遍历中序线索二叉树
void InOrderTraverseThr(BiThrTree T)
{   // T指向头结点，头结点的左链lchild指向根结点
    // 中序遍历二叉线索树T的非递归算法，对每个数据元素直接输出
    BiThrTree p = T->lchild;            // p指向根结点

    while (p != T) {                    // 空树或遍历结束时，p==T
        while (p->LTag == 0) {          // 沿左孩子向下
            p = p->lchild;
        }

        Visit(p);                       // 访问其左子树为空的结点

        while (p->RTag == 1 && p ->rchild != T) {
            p = p->rchild;              // 沿左线索访问后继结点
            Visit(p);
        }

        p = p->rchild;                  // 转向p的右子树
    }
}
