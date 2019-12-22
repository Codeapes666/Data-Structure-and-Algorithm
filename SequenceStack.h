#include <stdlib.h>

#define MAXSIZE 50          // 顺序栈存储空间的初始分配量

#define OK 1
#define ERROR 0

typedef int ElemType;

// 顺序栈的存储结构
typedef struct {
    ElemType* base;         // 栈底指针
    ElemType* top;          // 栈顶指针
    int stacksize;          // 栈可用的最大容量
}SeqStack;

// 栈的初始化
int InitStack(SeqStack &S)
{   // 为顺序栈动态分配一个最大容量为MAXSIZE的数组空间
    S.base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);

    if (!S.base) {          // 若内存分配失败
        return ERROR;
    }

    S.top = S.base;         // top初始化为base，空栈
    S.stacksize = MAXSIZE;  // stacksize置为栈的最大容量MAXSIZE

    return OK;
}

// 销毁栈
int DestoryStack(SeqStack &S)
{
    if (S.base) {
        free(S.base);
        S.base = NULL;
        S.top = NULL;
        S.stacksize = 0;

        return OK;
    }
}

// 判空
int StackEmpty(SeqStack S)
{
    if (S.top == S.base) {
        return OK;
    }

    return ERROR;
}

// 清空栈
int ClearStack(SeqStack &S)
{
    if (S.base) {
        S.top = S.base;
    }

    return OK;
}

// 求栈长度
int StackLength(SeqStack S)
{
    return S.top - S.base;
}

// 入栈
int Push(SeqStack &S, ElemType e)
{
    if (S.top - S.base == S.stacksize) {        // 栈满
        return ERROR;
    }

    *S.top++ = e;                   // 元素e压入栈顶，栈顶指针加1

    return OK;
}

// 出栈
int Pop(SeqStack &S, ElemType &e)
{
    if (S.top == S.base) {          // 栈空
        return ERROR;
    }

    e = *(--S.top);                 // 栈顶指针减1，将栈顶元素赋给e

    return OK;
}

// 取栈顶元素
ElemType GetTop(SeqStack S)
{
    if (S.top != S.base) {         // 栈非空
        return *(S.top - 1);       // 返回栈顶元素的值，栈顶指针不变
    }
}

// 若栈顶指针初始化为S.top = -1，即栈顶指针指向栈顶元素所在位置
// 入栈操作变为：*(++S.top) = e；出栈操作变为：e = *(S.top--)