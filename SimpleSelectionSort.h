// 待排序记录的数据类型定义
#define MAXSIZE 50              // 顺序表的最大长度

typedef int KeyType;            // 定义关键字类型为整型

typedef struct {
    KeyType key;                // 关键字项
}RedType;                       // 记录类型

typedef struct {
    RedType r[MAXSIZE + 1];     // r[0]闲置或用做哨兵
    int length;                 // 顺序表长度
}SeqList;                       // 顺序表类型

// 简单选择排序
// 时间复杂度：O(n²)
// 空间复杂度：O(1)
// 稳定性：不稳定
void SelectSort(SeqList &L)
{
    for (int i = 1; i < L.length; ++i) {            // 一共进行L.length - 1趟
        int min = i;                                // 记录最小元素位置
        for (int j = i + 1; j < L.length; ++j) {
            if (L.r[j].key < L.r[min].key) {
                min = j;                        // min指向此趟排序中关键字最小的记录
            }
        }

        if (min != i) {
            // 交换r[i]与r[k]
            RedType temp = L.r[i];
            L.r[i] = L.r[min];
            L.r[min] = temp;
        }
    }
}