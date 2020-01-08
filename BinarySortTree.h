// 二叉排序树的性质
// 1.若左子树非空，则左子树上所有结点的值均小千它的根结点的值
// 2.若右子树非空，则右子树上所有结点的值均大千它的根结点的值
// 3.左、 右子树也分别为二叉排序树
// 中序遍历一棵二叉树时可以得到一个结点值递增的有序序列
#include <stdio.h>
#include <stdlib.h>

#define OK          1
#define ERROR       0

typedef int KeyType;
typedef int Status;

// 二叉排序树的二叉链表存储表示
typedef struct {
    KeyType key;                // 关键字项
}ElemType;                      // 每个结点的数据域的类型

typedef struct BSTNode {
    ElemType data;              // 结点数据域
    struct BSTNode* lchild;     // 左孩子指针
    struct BSTNode* rchild;     // 右孩子指针
}BSTNode, *BSTree;

// 二叉排序树的查找
BSTree BSTSearch(BSTree T, KeyType key)
{   // 在根指针T所指二叉树中递归地查找某关键字等于key的数据元素
    // 若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
    if (T == NULL || T->data.key == key) {      // 查找结束
        return T;
    } else if (T->data.key > key) {             // 在左子树中继续查找
        return BSTSearch(T->lchild, key);
    } else {
        return BSTSearch(T->rchild, key);       // 在右子树中继续查找
    }
}

// 二叉排序树的查找（非递归）
BSTree BSTSearchNonRecursion(BSTree T, KeyType key)
{   // 查找函数返回指向关键字值为key的结点指针，若不存在，返回NULL
    BSTree p = NULL;                            // p指向被查找结点的双亲，用于插入和删除操作中
    while (T != NULL && T->data.key != key) {
        p = T;
        if (T->data.key > key) {
            T = T->lchild;
        } else {
            T = T->rchild;
        }
    }

    return T;
}

// 二叉排序树的插入
Status InsertBST(BSTree &T, ElemType e)
{   // 当二叉树T中不存在关键字等于e.key的数据元素时，则插入该元素
    if (T == NULL) {                            // 原树为空，新插入的记录为根结点
        T = (BSTree)malloc(sizeof(BSTNode));    
        T->data = e;                           
        T->lchild = T->rchild = NULL;           
        return OK;                      
    } else if (T->data.key > e.key) {           // 插入到T的左子树中
        InsertBST(T->lchild, e);
    } else if (T->data.key < e.key) {           // 插入到T的右子树中
        InsertBST(T->rchild, e);
    } else {                                    // 树中存在相同关键字的结点
        return ERROR;
    }
}

// 二叉排序树的创建
Status CreatBST(BSTree &T)
{
    T = NULL;                                   // 将二叉排序树T初始化为空树
    ElemType e;
    while (scanf("%d", &e.key) != EOF) {
        InsertBST(T, e);                        // 将此结点插入二叉排序树T中
    }

    return OK;
}

// 二叉排序树的删除
Status DeleteBST(BSTree &T, KeyType key) 
{   // 从二叉排序树T中删除关键字等于key的结点
    BSTree p = T;                           // 指针p指向待待删结点
    BSTree q = NULL;
    BSTree f = NULL;                        // 指针f为p的双亲结点

    /*------------ 下面的while循环从根开始查找关键字等于key的结点*p ------------*/
    while (p != NULL) {
        if (p->data.key == key) {           // 找到关键字等于key的结点*p，结束循环
            break;
        }

        f = p;                              // *f为*p的双亲结点
        if (p->data.key > key) {            // 在*p的左子树中继续查找
            p = p ->lchild;
        } else {                            // 在*p的右子树中继续查找
            p = p->rchild;
        }
    }

    if (p == NULL) {                        // 找不到被删除结点则返回
        return ERROR;
    }

    /*---- 考虑3种情况，实现p所指子树内部的处理： *p左右子树均不空、无右子树、无左子树 ----*/
    if ((p->lchild) && (p->rchild)) {       // 被删除结点*p左右子树均不空
        q = p;
        BSTree s = p->lchild;

        while (s->rchild != NULL) {         // 在*p的左子树中继续查找其前驱结点，即最右下结点
            q = s;
            s = s->rchild;                
        }

        p->data = s->data;                  // s指向被删结点的“前驱”，即用*s替代*p

        if (q != p) {
            q ->rchild = s->lchild;         // 重接*q的右子树
        } else {
            q->lchild = s->lchild;          // 重接*q的左子树
        }

        return ERROR;
    } else if (p->rchild == NULL) {         // 被删结点*p无右子树，只需重接其左子树
        q = p;
        p = p->lchild;
    } else if (p->lchild == NULL) {         // 被删结点*p无左子树，只需重接其右子树
        q = p;
        p = p->rchild;
    }

    /*-------- 将p所指的子树挂接到其双亲结点*f相应的位置 --------*/
    if (f == NULL) {                        // 被删除结点为根结点
        T = p;
    } else if (f->lchild == q) {            // 挂接到*f的左子树位置
        f->lchild = p;
    } else {                                // 挂接到*f的右子树位置
        f->rchild = p;
    }

    return OK;
}