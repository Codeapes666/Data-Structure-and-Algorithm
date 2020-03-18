#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK          1
#define ERROR       0
#define OVERFLOW   -1

typedef int ElemType;
typedef int Status;

// 链栈的存储结构
typedef struct StackNode{
    ElemType data;              // 数据域
    struct StackNode* next;     // 指针域
} StackNode, *LinkStack;

// 栈的初始化
// 这里规定链栈没有头结点
Status InitStack(LinkStack* S)
{   // 构造一个空栈S，栈顶指针置空
    *S = NULL;

    return OK;
}

// 销毁栈
Status DestoryStack(LinkStack* S)
{
    LinkStack p = NULL;

    while (*S != NULL) {
        p = *S;
        *S = (*S)->next;
        free(p);
    }

    return OK;
}

// 清空栈
Status ClearStack(LinkStack* S)
{
    LinkStack p = NULL;

    while (*S != NULL) {
        p = *S;
        *S = (*S)->next;
        free(p);
    }
    
    *S = NULL;
    
    return OK;
}

// 判空
bool StackEmpty(LinkStack S)
{
    if (S == NULL) {
        return true;
    }

    return false;
}

// 求栈长度
Status StackLength(LinkStack S)
{
    int length = 0;

    while (S->next != NULL) {
        ++length;
        S = S->next;
    }

    return length;
}

// 取栈顶元素
ElemType GetTop(LinkStack S)
{
    if (S != NULL) {        // 栈非空
        return S->data;     // 返回栈顶元素的值，栈顶指针不变
    }
}

// 入栈
Status Push(LinkStack* S, ElemType e)
{   // 生成新结点
    LinkStack p = (StackNode*)malloc(sizeof(StackNode));
    if (p == NULL) {        // 若内存分配失败
        exit(OVERFLOW);
    }

    p->data = e;            // 将新结点数据域置为e
    p->next = *S;           // 将新结点插入栈顶
    *S = p;                 // 修改栈顶指针为p

    return OK;
}

// 出栈
Status Pop(LinkStack* S, ElemType* e)
{   // 栈空
    if (*S == NULL) {
        return ERROR;
    }

    *e = (*S)->data;        // 将栈顶元素赋给e

    LinkStack p = *S;       // 用p临时保存栈顶元素空间，以备释放
    *S = (*S)->next;        // 修改栈顶指针

    free(p);                // 释放原栈顶元素的空间
    p = NULL;               // 指针置空

    return OK;
}

// 遍历栈
Status StackTraverse(LinkStack S)
{
    while (S != NULL) {
        printf("%d ", S->data);
        S = S->next;
    }
    printf("\n");

    return OK;
}

