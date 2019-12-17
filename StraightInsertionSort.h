// 待排序记录的数据类型定义
#define MAXSIZE 50              // 顺序表的最大长度

typedef int KeyType;            // 定义关键字类型为整型

typedef struct {
    KeyType key;                // 关键字项
    InfoType otherinfo;         // 其它数据项
}RedType;                       // 记录类型

typedef struct {
    RedType r[MAXSIZE + 1];     // r[0]闲置或用做哨兵
    int length;                 // 顺序表长度
}SeqList;                       // 顺序表类型

// 直接插入排序
// 时间复杂度：O(n²)
// 空间复杂度：O(1)
// 稳定性：稳定
void InsertSort(SeqList &L)
{
    int i = 0;
    int j = 0;
    for (i = 2; i <= L.length; ++i) {       // 依次将A[2]~A[L.length]插入到前面已排序序列
        if (L.r[i].key < L.r[i - 1].key) {  // 若A[i]的关键码小于其前驱，需将A[i]插入有序表
            L.r[0] = L.r[i];                // 复制为哨兵，L.r[0]不存放元素
            // 从后往前查找待插入位置
            for (j = i - 1; L.r[0].key < L.r[j].key; --j) {
                L.r[j + 1] = L.r[j];        // 向后挪位
            }

            L.r[j + 1] = L.r[0];            // 将r[0]即原r[i]，插入到正确位置
        }

    }
}


