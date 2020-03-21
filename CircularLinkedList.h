#include <stdio.h>

#define OK      1
#define ERROR   0

typedef int ElemType;
typedef int Status;

Status Visit(ElemType e)
{
    printf("%d ", e);

    return OK;
}

// 定义循环链表结点类型
typedef struct LNode 
{
    ElemType data;          // 数据域
    struct LNode* next;     // 指针域
} LNode, *LinkList;         // LinkList为指向结构体LNode的指针类型

// 循环单链表的操作和单链表基本一致，差别仅在于：
// 当链表遍历时，判别当前指针p是否指向表尾结点的终止条件不同

// 遍历操作
Status ListTraverse (LinkList L, Status (*Visit)(ElemType))
{
    if (L == NULL) {
        return ERROR;
    }

    LNode* p = L->next;

    while (p != L) {
        Visit (p->data);
        p = p->next;
    }
    
    return OK;
}
