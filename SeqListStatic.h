#include <stdio.h>

#define MaxSize 50				// 定义线性表的最大长度
#define OK 1
#define ERROR 0

typedef int ElemType;

typedef struct 
{
	ElemType data[MaxSize];		// 顺序表的元素		
	int length;					// 顺序表的当前长度
} SeqList;						// 顺序表的类型定义

// 初始化顺序表
int InitList(SeqList* L)
{
	L->length = 0;

	return OK;					
}

// 销毁线性表
int DestroyList(SeqList* L) {
	L->length = 0;

	return OK;
}

// 清空线性表
// 将L重置为空表
int ClearList(SeqList* L)
{
	L->length = 0;

	return OK;
}

// 判空操作
int ListEmpty(SeqList L)
{
	if (L.length == 0) {
		return OK;
	}

	return ERROR;
}

// 求顺序表长度
int ListLength(SeqList L)
{
	return L.length;
}

// 按序查找
// 获取表L中第i个位置的元素值
int GetElem(SeqList L, int i) 
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
int LocateElem(SeqList L, ElemType e) 
{
	if (L.length == 0) {
		return ERROR;
	}

	int i = 0;
	for (i = 0; i < L.length; ++i) {
		if (L.data[i] == e) {
			return i + 1;					// 下表为i的元素等于e，返回其位序i+1
		}
	}

	return ERROR;
}

// 返回前驱元素值
int PriorElem(SeqList L, ElemType cur_e, ElemType* pre_e)
{
    if (L.length == 0) {
        return ERROR;
    }

    int i = 0;
    for (i = 0; i < L.length; ++i) {
        // 当前元素cur_e不是第一个元素则有前驱
        if (i != 0 && (L.data[i] == cur_e)) {
            *pre_e = L.data[i - 1];
            return *pre_e;
        }
    }

    return ERROR;
}

// 返回后继元素值
int NextElem(SeqList L, ElemType cur_e, ElemType* next_e)
{
    if (L.length == 0) {
        return ERROR;
    }

    int i = 0;
    for (i = 0; i < L.length; ++i) {
        // 当前元素cur_e不是最后一个元素则有后继
        if ((i != L.length - 1) && (L.data[i] == cur_e)) {
            *next_e = L.data[i + 1];
            return *next_e;
        }
    }

    return ERROR;
}

// 插入操作
// 在顺序表L的第i（1 ≤ i ≤ length + 1）个位置插入新元素e
// 插入成功返回OK，插入失败返回ERROR
int ListInsert(SeqList* L, int i, ElemType e)
{
	if (i < 1 || i > L->length + 1) {		// 判断i的范围是否有效
		return ERROR;
	}

	if (L->length >= MaxSize) {				// 当前空间已满，不能插入
		return ERROR;
	}

	int j = 0;
	for (j = L->length; j >= i; --j) {	// 将第i个位置及之后的元素后移
		L->data[j] = L->data[j - 1];			
	}

	L->data[i - 1] = e;						// 在位置i处插入e
	++L->length;							// 线性表长度加1

	return OK;
}

// 删除操作
// 删除顺序表L中第i（1 ≤ i ≤ length）个位置的元素
// 删除成功返回OK，删除失败返回ERROR。如删除成功，用e返回删除元素的值
int ListDelete(SeqList* L, int i, ElemType* e) 
{
	if (i < 1 || i > L->length) {			// 判断i的范围是否有效
		return ERROR;
	}

	*e = L->data[i - 1];					// 将要删除的元素赋值给e

	for (int j = i; j < L->length; ++j) {
		L->data[j - 1] = L->data[j];		// 将第i个位置之后的元素前移
	}

	--L->length;							// 线性表长度减1

	return OK;
}

// 遍历操作
int TraverseList(SeqList L)
{
	if (L.length == 0) {
		return ERROR;
	}

	int i = 0;
	for (i = 0; i < L.length; ++i) {
		printf("data[%d] = %d\n", i, L.data[i]);
	}

	printf("\n");

	return OK;
}