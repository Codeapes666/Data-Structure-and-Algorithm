#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK          1
#define ERROR       0
#define OVERFLOW   -1

typedef int ElemType;
typedef int Status;

// 定义单链表结点类型
typedef struct LNode {
    ElemType data;          // 数据域
    struct LNode* next;     // 指针域
}LNode, *LinkList;          // LinkList为指向结构体LNode的指针类型

// LinkList与LNode*，两者本质上是等价的

// 初始化单链表
Status InitList(LinkList* L)
{
    *L = (LinkList)malloc(sizeof(LNode));

    if (*L == NULL ) {
        exit(OVERFLOW);
    }

    (*L)->data = 0;
    (*L)->next = NULL;

    return OK;
}

// 前插法创建单链表
LinkList CreatList_H(LinkList* L)
{
    // 从表尾到表头逆向建立单链表L，每次均在头结点之后插入元素
    *L = (LinkList)malloc(sizeof(LNode));           // 创建头结点

    if (*L == NULL) {
        exit(OVERFLOW);
    }

    (*L)->next = NULL;                              // 初始化为空链表

    LNode* p = NULL;
    int x = 0;
    
    while (scanf("%d", &x) != EOF) {
        p = (LNode*)malloc(sizeof(LNode));          // 创建新结点

        // 判断内存是否分配成功
        if (p == NULL) {
            exit(OVERFLOW);
        }

        p->data = x;                                // 输入元素值赋给新结点*p的数据域
        p->next = (*L)->next;
        (*L)->next = p;
    }

    return *L;
}

// 后插法创建单链表
LinkList CreatList_R(LinkList* L)
{
    // 从表头到表尾正向建立单链表L，每次均在表尾插入元素
    *L = (LinkList)malloc(sizeof(LNode));            // 创建头结点

    if (*L == NULL) {
        exit(OVERFLOW);
    }

    (*L)->next = NULL;                               // 初始化为空链表

    LNode* p = NULL;
    LNode* r = *L;
    int x = 0;
    
    while (scanf("%d", &x) != EOF) {
        p = (LNode*)malloc(sizeof(LNode));          // 生成新结点

        if (p == NULL) {
            exit(OVERFLOW);
        }

        p->data = x;                                // 输入元素值赋给新结点*p的数据域
        r->next = p;
        r = p;                                      // r指向新的表尾结点*p
    }
    
    r->next = NULL;                                 // 尾结点指针置空
    return *L;
}

// 求单链表的长度
Status Length(LinkList L)
{
    int length = 0;
    LNode* p = L->next;

    while (p != NULL) {
        ++length;
        p = p->next;
    }

    return length;
}

// 按序查找
// 在带头结点的单链表L中根据序号i获取元素的值，用e返回L中第i个数据元素的值
Status GetElem(LinkList L, int i ,ElemType* e)
{
    LinkList p = L->next;                           // 初始化，p指向首原结点
    int j = 1;                                      // 计数器j初值赋为1

    // 顺链域向后扫描，直到p为空或p指向第i个元素
    while (p && j < i) {                            
        p = p->next;                                // p指向下一个结点
        ++j;                                        // 计数器j相应加1
    }

    if (!p || j > i) {                              
        return ERROR;
    }

    *e = p->data;                                   // 取第i个结点的数据域
    return OK;
}

// 按值查找
// 在带头结点的单链表L中查找值为e的元素
LinkList LocateElem(LinkList L, ElemType e)
{
    LinkList p = L->next;                           // 初始化，p指向首原结点
    
    // 顺链域向后扫描。直到p为空或p所指结点的数据域等于e
    while (p && p->data != e) {                     
        p = p->next;                                // p指向下一个结点
    }

    // 查询成功返回值为e的结点地址p，查找失败p为NULL
    return p;                       
}

// 插入操作
// 在带头结点的单链表L中第i个位置插入值为e的新结点
Status ListInsert(LinkList* L, int i, ElemType e)
{
    LinkList p = *L;
    int j = 0;

    // 查找第i-1个结点，p指向该结点
    while (p && j < i - 1) {
        p = p->next;
        ++j;
    }

    if (p == NULL || j > i - 1) {
        return ERROR;
    }

    LNode* s = (LNode*)malloc(sizeof(LNode));       // 生成新结点*s

    if (s == NULL) {
        exit(OVERFLOW);
    }

    s->data = e;                                    // 将结点*s的数据域置为e
    s->next = p->next;                              // 将结点*s的指针域指向第i个结点
    p->next = s;                                    // 将结点*p的指针域指向结点*s

    return OK;
}


// 删除操作
// 在带头结点的单链表L中，删除第i个元素
Status ListDelete(LinkList* L, int i)
{
    LinkList p = *L;
    int j = 0;

    // 查找第i-1个结点，p指向该结点
    while ((p->next != NULL) && (j < i -1)) {
        p = p->next;
        ++j;
    }

    if ((p->next == NULL) || (j > i - 1)) {
        return ERROR;
    }

    LinkList q = p->next;                           // 令q指向被删除结点
    p->next = q->next;                              // 将*q结点从链中“断开”
    
    free(q);                                        // 释放删除结点的空间
    p = NULL;
    
    return OK;
}

// 判空操作
bool Empty(LinkList L)
{
    // 若头结点指向的下一个结点是NULL，则链表为空
	if (L->next == NULL) {
		return true;
	}

	return false;
}

// 遍历操作
Status PrintList(LinkList L)
{
    if (L == NULL) {
        return ERROR;
    }

    // p指向头结点的下一个结点
    LinkList p = L->next;

    while (p != NULL) {
        printf("%d", p->data);

        p = p->next;
    }
    
    return OK;
}

// 销毁操作
Status DestroyList(LinkList* L)
{
    if (*L == NULL) {
        return ERROR;
    }
    
    LinkList p = (*L)->next;
    LinkList q = NULL;
    
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    
    free(*L);
    *L = NULL;

    return OK;
}

// 清空操作
Status ClearList(LinkList L)
{
    if (L == NULL) {
        return ERROR;
    }

    // p指向头结点的下一个结点
    LinkList p = L->next;
    LinkList q = NULL;

    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    
    L->next = NULL;

    return OK;
}
