#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define InitSize    100             // 定义线性表的初始长度
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

// 顺序表的存储结构
typedef struct 
{
    ElemType* data;                 // 动态分配数组的指针
    int MaxSize;                    // 线性表的最大容量
    int length;                     // 线性表的当前长度
} SeqList;                          // 动态分配数组顺序表的类型定义

// 初始化顺序表
Status InitList(SeqList* L)
{
    L->data = (ElemType*)malloc(sizeof(ElemType) * InitSize);

    // 判断内存是否分配成功
    if (L->data == NULL) {
        exit(OVERFLOW);
    }

    // 内存分配成功，开始是空表，故当前长度置为0
    L->length = 0;

    // 初始化表的存储容量，即当前表最大的存储量
    L->MaxSize = InitSize;

    return OK;
}

// 销毁线性表
// 用malloc函数分配的空间在释放时是连续释放的，即将物理地址相邻的若干空间全部释放
// 所以顺序表销毁可以只释放基址，就会自动释放所有空间，而链表要一个一个的把节点删除
Status DestroyList(SeqList* L)
{
    if (L->data == NULL) {          // 若当前表为空，直接return
        return ERROR;
    }

    free(L->data);                	// 释放内存
    L->data = NULL;               	// 指针置空

    L->length = 0;                	// 线性表长度置为0
    L->MaxSize = 0;               	// 线性表最大容量置为0

    return OK;
}

// 清空线性表
Status ClearList(SeqList* L)
{
    L->length = 0;

    return OK;
}

// 判空
bool ListEmpty(SeqList L)
{
    // 线性表为空返回true
    if (L.length == 0) {
        return true;
    }

    return false;
}

// 求顺序表长度
int ListLength(SeqList L)
{
    return L.length;
}

// 按序查找
// 获取表L中第i个位置的元素值
Status GetElem(SeqList L, int i ,ElemType* e)
{
    if (L.length == 0) {
        return ERROR;
    }
    if (i < 1 || i > L.length) {
        return ERROR;
    }

    *e = L.data[i - 1];

    return OK;
}

// 按值查找
// 在顺序表L中查找第一个值等于e的元素，并返回其位序
int LocateElem(SeqList L, ElemType e)
{
    if (L.length == 0) {
        return ERROR;
    }

    for (int i = 0; i < L.length; ++i) {
        if (L.data[i] == e) {
            // 下表为i的元素等于e，返回其位序i+1
            return i + 1;
        }
    }

    return ERROR;
}

// 返回前驱元素值
Status PriorElem(SeqList L, ElemType cur, ElemType* pre)
{
    if (L.length == 0) {
        return ERROR;
    }

    // 当前元素cur不是第一个元素则有前驱值
    for (int i = 1; i < L.length; ++i) {
        if (L.data[i] == cur) {
            *pre = L.data[i - 1];
            return OK;
        }
    }

    return ERROR;
}

// 返回后继元素值
Status NextElem(SeqList L, ElemType cur, ElemType* next)
{
    if (L.length == 0) {
        return ERROR;
    }

    // 当前元素cur不是最后一个元素则有后继值
    for (int i = 0; i < L.length - 1; ++i) {
        if (L.data[i] == cur) {
            *next = L.data[i + 1];
            return OK;
        }
    }

    return ERROR;
}

// 插入操作
// 在顺序表L的第i（1 ≤ i ≤ length + 1）个位置插入新元素e
// 插入成功返回OK，插入失败返回ERROR
Status ListInsert(SeqList* L, int i, ElemType e)
{
    ElemType* newBase = NULL;

    // 判断i的范围是否有效
    if (i < 1 || i > L->length + 1) {
        return ERROR;
    }
    
    // 当前空间已满，再分配容量
    if (L->length >= L->MaxSize) {

        newBase = (ElemType*)realloc(L->data, (L->MaxSize + InitSize) * sizeof(ElemType));

        if (newBase == NULL) {
            exit(OVERFLOW);
        }
        
        // 新基址
        L->data = newBase;
        // 增加空间容量
        L->MaxSize += InitSize;
    }
    
    if (i != L->length + 1) {
        for (int j = L->length - 1; j >= i - 1; --j) {
            L->data[j + 1] = L->data[j];
        }
    }

    L->data[i - 1] = e;
    
    // 线性表长度加1
    ++L->length;

    return OK;

}

// 删除操作
// 删除顺序表L中第i（1 ≤ i ≤ length）个位置的元素
// 删除成功返回OK，删除失败返回ERROR。如删除成功，用e返回删除元素的值
Status ListDelete(SeqList* L, int i, ElemType* e)
{
    // 判断i的范围是否有效
    if (i < 1 || i > L->length) {
        return ERROR;
    }

    *e = L->data[i -1];

    for (int j = i; j < L->length; ++j) {
        // 将第i个位置之后的元素前移
        L->data[j - 1] = L->data[j];
    }

    // 线性表长度减1
    --L->length;

    return OK;
}

// 遍历操作
Status TraverseList(SeqList L, Status (*Visit)(ElemType))
{
    if (L.length == 0) {
        return ERROR;
    }

    for (int i = 0; i < L.length; ++i) {
        Visit (L.data[i]);
    }

    printf("\n");

    return OK;
}