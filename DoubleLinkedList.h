#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int ElemType;

// 定义双链表结点类型
typedef struct DLNode {
    ElemType data;              // 数据域
    struct DLNode* prior;       // 直接前驱
    struct DLNode* next;        // 直接后继
}DLNode, *DLinkList;

DLinkList GetElem_DL(DLinkList L, int i)
{

}

// 插入操作
// 在带头结点的双向链表L中第i个位置之前插入元素e
int ListInsert_DL(DLinkList &L, int i, ElemType e)
{
    DLinkList p = NULL;
    if (!(p = GetElem_DL(L, i))) {
        return ERROR;
    }

    DLinkList s = NULL;
    s = (DLinkList)malloc(sizeof(DLNode));
    
}