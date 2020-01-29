typedef int KeyType;

// 待查找的数据元素类型定义
typedef struct {
    KeyType key;        // 关键字域
}ElemType;

typedef struct {
    ElemType* elem;     // 存储空间基地址，建表时按实际长度分配，ST.elem[0]闲置不用
    int length;         // 当前表长度
}SSTable;

// 顺序查找
// 适用于线性表的顺序存储结构、链式存储结构
// 时间复杂度：O(n)
int SeqSearch(SSTable ST, KeyType key)
{   // 在顺序表ST中顺序查找其关键字等于key的数据元素。
    // 若找到，则函数值为该元素在表中的位置，否则为0
    ST.elem[0].key = key;                                   // 哨兵

    int i = 0;
    for (int i = ST.length; ST.elem[i].key != key; --i);        // 从后往前找

    return i;
}
