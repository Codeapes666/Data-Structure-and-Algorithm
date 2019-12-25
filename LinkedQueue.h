#include <stdio.h>
#include <stdlib.h>

#define OK          1
#define ERROR       0
#define TRUE        1
#define FALSE       0
#define OVERFLOW   -1

typedef int ElemType;
typedef int Status;

// 队列的链式存储结构
typedef struct QNode {          // 链式队列结点
    ElemType data;
    struct QNode* next;
}QNode, *QueuePtr;

typedef struct {                // 链式队列
    QueuePtr front;             // 队头指针，等价于QNode* front
    QueuePtr rear;              // 队尾指针，等价于QNode* rear
}LinkQueue;

// 链队的初始化
Status InitQueue(LinkQueue &Q)  // 构造一个只有一个头结点的空队
{   // 生成新结点作为头结点
    QNode* p = (QNode*)malloc(sizeof(QNode));

    if (p == NULL) {            // 空间分配失败
        exit(OVERFLOW);
    }

    Q.front = Q.rear = p;       // 队头和队尾指针指向此结点

    Q.front->next = NULL;       // 头结点的指针域置空

    return OK;
}

// 销毁链队
Status DestroyQueue(LinkQueue &Q)
{
    while (Q.front != NULL) {
        Q.rear = Q.front->next;

        free(Q.front);
        Q.front = Q.rear;
    }

    return OK;
}

// 清空链队
Status ClearQueue(LinkQueue &Q)
{
    QueuePtr q = NULL;
    QueuePtr p = NULL;
    p = Q.front->next;
    Q.front->next = NULL;

    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }

    Q.rear = Q.front;

    return OK;
}

// 判空
Status QueueEmpty(LinkQueue Q)
{
    if (Q.front->next == NULL) {
        return TRUE;
    }

    return FALSE;
}

// 求链队长度
Status QueueLength(LinkQueue Q)
{
    int length = 0;
    QueuePtr p = NULL;
    p = Q.front->next;

    while (p != NULL) {
        length++;
        p = p ->next;
    }

    return length;
}

// 取队头元素
ElemType GetHead(LinkQueue Q)
{
    if (Q.front != Q.rear) {            // 队列非空
        return Q.front->next->data;     // 返回队头元素的值，队头指针不变
    }
}

// 入队
Status EnQueue(LinkQueue &Q, ElemType e)
{   // 为入队元素分配结点空间，用指针p指向
    QNode* p = (QNode*)malloc(sizeof(QNode));

    p->data = e;                // 将新结点数据域置为e
    
    // 将新结点插入到队尾
    p->next = NULL;
    Q.rear->next = p;

    Q.rear = p;                // 修改队尾指针                  

    return OK;
}

// 遍历链列
Status QueueTraverse(LinkQueue Q)
{
    QueuePtr p = NULL;
    p = Q.front->next;

    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");

    return OK;
}