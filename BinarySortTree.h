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
    ElemType e = {0};
    while (scanf("%d", &e.key) != EOF) {
        InsertBST(T, e);                        // 将此结点插入二叉排序树T中
    }
}