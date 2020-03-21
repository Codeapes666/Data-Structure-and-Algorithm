#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK          1
#define ERROR       0
#define OVERFLOW   -1

typedef int ElemType;
typedef int Status;

Status Visit (ElemType e)
{
    printf("%d ", e);

    return OK;
}

// 队列的链式存储结构
typedef struct QNode                // 链式队列结点
{                                   
    ElemType data;                  // 数据域
    struct QNode* next;             // 指针域
} QNode, *QueuePtr;

typedef struct                      // 链式队列
{                    
    QueuePtr front;                 // 队头指针，等价于QNode* front
    QueuePtr rear;                  // 队尾指针，等价于QNode* rear
} LinkQueue;

// 链队的初始化
Status InitQueue (LinkQueue* Q)      // 构造一个只有头结点的空队
{   // 生成新结点作为头结点，队头和队尾指针指向头结点
    Q->front = Q->rear = (QNode*)malloc(sizeof(QNode));

    if (Q->front == NULL) {         // 若内存分配失败
        exit(OVERFLOW);
    }

    Q->front->data = 0;             // 头结点的数据域置空
    Q->front->next = NULL;          // 头结点的指针域置空

    return OK;
}

// 判空
bool QueueEmpty (LinkQueue Q)
{
    if (Q.front == NULL) {          // 此时队列被销毁
        exit(1);
    }
    
    if (Q.front == Q.rear) {        // 或Q.front->next == NULL
        return true;
    }
    
    return false;
}

// 销毁链队
Status DestroyQueue (LinkQueue* Q)
{
    if (Q->front == NULL) {
        return ERROR;
    }
    
    QueuePtr p = Q->front->next;
    QueuePtr q = NULL;
    
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    
    free(Q->front);
    Q->front = NULL;

    return OK;
}

// 清空链队
Status ClearQueue (LinkQueue* Q)
{
    if (Q->front == NULL) {
        return ERROR;
    }
    
    QueuePtr p = Q->front->next;
    QueuePtr q = NULL;

    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }

    Q->front = Q->rear;
    Q->front->next = NULL;

    return OK;
}

// 求链队长度
int QueueLength (LinkQueue Q)
{
    int length = 0;
    QueuePtr p = Q.front;
    QueuePtr q = Q.rear;

    while (p != q) {
        p = p ->next;
        ++length;
    }

    return length;
}

// 取队头元素
ElemType GetHead (LinkQueue Q)
{
    if (Q.front != Q.rear) {            // 队列非空
        return Q.front->next->data;     // 返回队头元素的值，队头指针不变
    }
}

// 入队
Status EnQueue (LinkQueue* Q, ElemType e)
{   // 为入队元素分配结点空间，用指针p指向
    QNode* p = (QNode*)malloc(sizeof(QNode));

    p->data = e;                        // 将新结点数据域置为e
    
    // 将新结点插入到队尾
    p->next = NULL;
    Q->rear->next = p;

    Q->rear = p;                        // 修改队尾指针

    return OK;
}

// 出队
Status DeQueue (LinkQueue* Q, ElemType* e)
{   
    // 删除Q的队头元素，用e返回其值
    if (Q->front == Q->rear) {          // 若队列空，则返回ERROR
        return ERROR;
    }

    QueuePtr p = Q->front->next;        // p指向队头元素
    *e = p->data;                       // e保存队头元素的值
    Q->front->next = p->next;           // 修改头指针

    if(Q->rear == p) {                  // 最后一个元素被删，队尾指针指向头结点
        Q->rear = Q->front;
    }

    free(p);                            // 释放原队头元素的空间
    p = NULL;

    return OK;
}

// 遍历链列
Status QueueTraverse (LinkQueue Q, Status (*Visit)(ElemType))
{
    if (Q.front == NULL) {
        return ERROR;
    }

    QueuePtr p = Q.front->next;

    while (p != NULL) {
        Visit (p->data);
        p = p->next;
    }

    printf("\n");

    return OK;
}
