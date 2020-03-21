#include <stdio.h>
#include <stdbool.h>

#define MaxSize 100             // 定义线性表的最大长度
#define OK      1
#define ERROR   0

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
    ElemType data[MaxSize];     // 顺序表的元素
    int length;                 // 顺序表的当前长度
} SeqList;                      // 顺序表的类型定义

// 初始化顺序表
Status InitList (SeqList* L)
{
    L->length = 0;

    return OK;
}

// 清空线性表
Status ClearList (SeqList* L)
{
    if (L->length != 0) {
        L->length = 0;
        return OK;
    }
    
    return ERROR;
}

// 判空操作
bool ListEmpty (SeqList L)
{
    if (L.length == 0) {
        return true;
    }

    return false;
}

// 求顺序表长度
int ListLength (SeqList L)
{
    return L.length;
}

// 按序查找
// 获取表L中第i个位置的元素值
Status GetElem (SeqList L, int i) 
{
    if (L.length == 0) {
        return ERROR;
    }

    if (i < 1 || i > L.length) {
        return ERROR;
    }

    return L.data[i - 1];
}

// 按值查找
// 在顺序表L中查找第一个值等于e的元素，并返回其位序
Status LocateElem (SeqList L, ElemType e) 
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
Status PriorElem (SeqList L, ElemType cur, ElemType* pre)
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
Status NextElem (SeqList L, ElemType cur, ElemType* next)
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
Status ListInsert (SeqList* L, int i, ElemType e)
{
    if (i < 1 || i > L->length + 1) {           // 判断i的范围是否有效
        return ERROR;
    }

    if (L->length >= MaxSize) {                 // 当前空间已满，不能插入
        return ERROR;
    }

    for (int j = L->length; j >= i; --j) {      // 将第i个位置及之后的元素后移
        L->data[j] = L->data[j - 1];
    }

    L->data[i - 1] = e;                         // 在位置i处插入e
    ++L->length;                                // 线性表长度加1

    return OK;
}

// 删除操作
// 删除顺序表L中第i（1 ≤ i ≤ length）个位置的元素
// 删除成功返回OK，删除失败返回ERROR。如删除成功，用e返回删除元素的值
Status ListDelete (SeqList* L, int i, ElemType* e) 
{
    if (i < 1 || i > L->length) {               // 判断i的范围是否有效
        return ERROR;
    }

    *e = L->data[i - 1];                        // 将要删除的元素赋值给e

    for (int j = i; j < L->length; ++j) {
        L->data[j - 1] = L->data[j];            // 将第i个位置之后的元素前移
    }

    --L->length;                                // 线性表长度减1

    return OK;
}

// 遍历操作
Status TraverseList (SeqList L, Status (*Visit)(ElemType))
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
