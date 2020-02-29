#include <stdlib.h>
#include <stdbool.h>

#define OK          1
#define ERROR       0
#define OVERFLOW   -1

typedef int Status;

#define HASHSIZE 12             // 定义散列表长为数组的长度
#define NULLKEY   0             // 单元为空的标记

typedef struct {
    int* elem;                  // 数据元素存储基址，动态分配数组
    int count;                  // 当前数据元素个数
}HashTable;

int m = 0;                      // 散列表表长，全局变量

// 初始化散列表
Status initHashTable(HashTable* HT)
{
    int i = 0;
    m = HASHSIZE;
    HT->count = m;
    HT->elem = (int*)malloc(sizeof(int) * m);
    if (HT->elem == NULL) {     // 若内存分配失败
        exit(OVERFLOW);
    }

    for (i = 0; i < m; ++i) {
        HT->elem[i] = NULLKEY;
    }

    return OK;
}

// 构造散列函数
Status Hash(int key)
{
    return key % m;                         // 构造方法为除留余数法
}

// 插关键字进入散列表
Status InsertHash(HashTable* HT, int key)
{
    int addr = Hash(key);                   // 求散列函数

    while (HT->elem[addr] != NULLKEY) {     // 如果不为空，则冲突
        addr = (addr + 1) % m;              // 开放定址法的线性探测
    }

    HT->elem[addr] = key;                   // 直到有空位后插入关键字

    return OK;
}

// 散列表的查找
bool SearchHash(HashTable HT, int key, int* addr)
{
    *addr = Hash(key);                      // 求散列地址

    while (HT.elem[*addr] != key) {         // 若HT.elem[*addr] == key，则说明查找成功，直接返回
        *addr = (*addr + 1) % m;            // 开放定址法的线性探测

        // 如果查找到NULLKEY或循环回到原点，则说明关键字不存在，返回FALSE
        if (HT.elem[*addr] == NULLKEY || *addr == Hash(key)) {
            return false;
        }
    }

    return true;
}