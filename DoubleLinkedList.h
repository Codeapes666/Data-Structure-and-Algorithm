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
}DLNode, *DLinkList;            // DLinkList与DLNode*，两者本质上是等价的

// 按序查找
// 取出带头结点的双向链表中第i个位置的结点指针
DLNode* GetElem_DL(DLinkList L, int i)
{
    if (i == 0) {               // 若等于0，则返回头结点
        return L;
    }

    if (i < 1) {
        return NULL;            // 若i无效，则返回NULL
    }

    int j = 1;                  // 计数，初始为1
    DLNode* p = L->next;        // 头结点指针赋给p

    while (p && j < i) {        // 从第i个结点开始查找，查找第i个结点
        p = p->next;
        ++j;
    }

    // 返回第i个结点的指针，如果i大于表长，p=NULL，直接返回p即可
    return p;
}

// 插入操作
// 在带头结点的双向链表L中第i个位置之前插入元素e
int ListInsert_DL(DLinkList &L, int i, ElemType e)
{
    DLinkList p = NULL;
    if (!(p = GetElem_DL(L, i))) {              // 在L中确定第i个元素的位置指针p
        return ERROR;                           // p为NULL时，第i个元素不存在
    }

    DLinkList s = NULL;
    s = (DLinkList)malloc(sizeof(DLNode));      // 生成一个新结点s

    if (s == NULL) {                            // 判断结点内存是否分配成功
        return ERROR;
    }

    s->data = e;                                // 将结点s数据域置为e
    s->prior = p->prior;                        // 将结点s插入L中
    p->prior->next = s;
    s->next = p;
    p->prior = s;

    return OK;
}

// 在第i个位置之后插入元素e，代码片段如下所示：
// s->data = e;
// s->next = p->next;
// p->next->prior = s;
// s->prior = p;
// p->next = s;