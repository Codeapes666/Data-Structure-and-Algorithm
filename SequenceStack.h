#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE     100             // 顺序栈存储空间的初始分配量
#define OK          1
#define ERROR       0
#define OVERFLOW   -1

typedef int ElemType;
typedef int Status;

Status Visit(ElemType e)
{
    printf("%d ", e);

    return OK;
}

// S->top有两种可能，一种是指向栈顶元素，一种是指向比栈顶元素更高一层的空元素

/*======== 第 1 种 ========*/

// 顺序栈的存储结构
typedef struct 
{
    ElemType data[MAXSIZE];
    int top;                        // 用来存放栈顶元素的下标
} SqStack;

// 栈的初始化
Status InitStack (SqStack* S)
{
    S->top = -1;
    return OK;
}

// 清空栈
Status ClearStack (SqStack* S)
{
    if (S->top != -1) {
        S->top = -1;
        return OK;
    }
    
    return ERROR;
}

// 判空
bool StackEmpty (SqStack S)
{
    if (S.top == -1) {
        return true;
    }
    
    return false;
}

// 求栈长度
int StackLength(SqStack S)
{
    return S.top + 1;
}

// 取栈顶元素
Status GetTop (SqStack S, ElemType* e)
{
    if (S.top == -1) {
        return ERROR;
    }
    
    *e = S.data[S.top];
    
    return OK;
}

// 入栈
Status Push (SqStack* S, ElemType e)
{
    if (S->top == MAXSIZE - 1) {                // 栈满
        return ERROR;
    }
    
    S->data[++S->top] = e;                      // 指针先加1，再入栈
    
    return OK;
}

// 出栈
Status Pop (SqStack* S, ElemType* e)
{
    if (S->top == -1) {                         // 栈空
        return ERROR;
    }
    
    *e = S->data[S->top--];                     // 栈顶指针减1，将栈顶元素赋给e
    
    return OK;
}

// 遍历栈
Status StackTraverse (SqStack S, Status (*Visit)(ElemType))
{   
    if (S.top == -1) {
        return ERROR;
    }

    while (S.top != -1) {
        Visit (S.data[S.top--]);
    }

    printf("\n");

    return OK;
}

/*======== 第 2 种 ========*/

// 顺序栈的存储结构
typedef struct 
{
    ElemType* base;                             // 栈底指针
    ElemType* top;                              // 栈顶指针
    int stacksize;                              // 栈可用的最大容量
} SeqStack;

// 栈的初始化
Status InitStack (SeqStack* S)
{   
    // 为顺序栈动态分配一个最大容量为MAXSIZE的数组空间
    S->base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);

    if (S->base == NULL) {                      // 空间分配失败
        exit(OVERFLOW);
    }

    S->top = S->base;                           // top初始化为base，空栈
    S->stacksize = MAXSIZE;                     // stacksize置为栈的最大容量MAXSIZE

    return OK;
}

// 销毁栈
Status DestoryStack (SeqStack* S)
{
    if (S->base != NULL) {
        free(S->base);                          // 释放空间
        S->base = NULL;                         // 指针置空
        S->top = NULL;
        S->stacksize = 0;

        return OK;
    }
    
    return ERROR;
}

// 清空栈
Status ClearStack (SeqStack* S)
{
    if (S->base != NULL) {
        S->top = S->base;
        return OK;
    }

    return ERROR;
}

// 判空
bool StackEmpty (SeqStack S)
{
    if (S.top == S.base) {
        return true;
    }

    return false;
}

// 求栈长度
int StackLength (SeqStack S)
{
    return S.top - S.base;
}

// 取栈顶元素
Status GetTop(SeqStack S, ElemType* e)
{
    if (S.top == S.base) {                      // 栈为空
        return ERROR;
    }

    *e = *(S.top - 1);                          // 将栈顶元素赋给e

    return OK;
}

// 入栈
Status Push(SeqStack* S, ElemType e)
{
    if (S->top - S->base == S->stacksize) {     // 栈满
        return ERROR;
    }

    *(S->top++) = e;                            // 元素e压入栈顶，栈顶指针加1

    return OK;
}

// 出栈
Status Pop (SeqStack* S, ElemType* e)
{
    if (S->top == S->base) {                    // 栈空
        return ERROR;
    }

    *e = *(--S->top);                           // 栈顶指针减1，将栈顶元素赋给e

    return OK;
}

// 遍历栈
Status StackTraverse (SeqStack S, Status (*Visit)(ElemType))
{
    if (S.top == S.base) {
        return ERROR;
    }

    while (S.top != S.base) {
        Visit (*(--S.top));
    }

    printf("\n");
    
    return OK;
}
