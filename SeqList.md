```c
#include <stdio.h>
#define MaxSize 50				// 定义线性表的最大长度

typedef int DataType;

typedef struct 
{
	DataType data[MaxSize];		// 顺序表的元素		
	int length;					// 顺序表的当前长度
} SeqList;						// 顺序表的类型定义

// 初始化顺序表
void InitList(SeqList* L)
{
	L->length = 0;					
}

// 求顺序表长度
int Length(SeqList L)
{
	return L.length;
}

// 插入操作
// 在顺序表L的第i（1 ≤ i ≤ length + 1）个位置插入新元素e
// 插入成功返回0，插入失败返回1
int ListInsert(SeqList* L, int i, DataType e)
{
	if (i < 1 || i > L->length + 1) {		// 判断i的范围是否有效
		return 1;
	}

	if (L->length >= MaxSize) {				// 当前空间已满，不能插入
		return 1;
	}

	for (int j = L->length; j >= i; --j) {	// 将第i个位置及之后的元素后移
		L->data[j] = L->data[j-1];			
	}

	L->data[i-1] = e;						// 在位置i处插入e
	++L->length;							// 线性表长度加1

	return 0;
}

// 删除操作
// 删除顺序表L中第i（1 ≤ i ≤ length）个位置的元素
// 删除成功返回0，删除失败返回1。如删除成功，用e返回删除元素的值
int ListDelete(SeqList* L, int i, DataType* e) 
{
	if (i < 1 || i > L->length) {			// 判断i的范围是否有效
		return 1;
	}

	*e = L->data[i-1];						// 将要删除的元素赋值给e

	for (int j = i; j < L->length; ++j) {
		L->data[j-1] = L->data[j];			// 将第i个位置之后的元素前移
	}

	--L->length;							// 线性表长度减1

	return 0;
}

// 按值查找
// 在顺序表L中查找第一个值等于e的元素，并返回其位序
int LocateElem(SeqList L, DataType e) 
{
	for (int i = 0; i < L.length; ++i) {
		if (L.data[i] == e) {
			return i+1;						// 下表为i的元素等于e，返回其位序i+1
		}
	}

	return 0;								// 退出循环，说明查找失败
}

// 按位查找
// 获取表L中第i个位置的元素值
int GetElem(SeqList L, int i) 
{
	if (i < 1 || i > L.length) {
		return 1;
	}

	return L.data[i-1];
}

// 输出操作
int PrintList(SeqList L)
{
	if (L.length == 0) {
		return 1;
	}

	for (int i = 0; i < L.length; ++i) {
		printf("data[%d] = %d\n", i, L.data[i]);
	}

	printf("\n");

	return 0;
}

// 判空操作
int Empty(SeqList L)
{
	if (L.length == 0) {
		return 1;
	}

	return 0;
}
```



