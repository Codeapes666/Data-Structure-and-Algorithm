// 二叉排序树的性质
// 1.若左子树非空，则左子树上所有结点的值均小千它的根结点的值
// 2.若右子树非空，则右子树上所有结点的值均大千它的根结点的值
// 3.左、 右子树也分别为二叉排序树
// 中序遍历一棵二叉树时可以得到一个结点值递增的有序序列
#include <stdio.h>

typedef int KeyType;

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
{   // 在跟指针T所指二叉树中递归地查找某关键字等于key的数据元素
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