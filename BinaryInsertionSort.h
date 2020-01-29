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

// 折半插入排序
// 平均时间复杂度：O(n²)
// 空间复杂度：O(1)
// 稳定性：稳定
void BInserSort(SeqList &L)
{
    // 依次将L.r[2]~L.r[L.length]插入到前面已排序序列
    for (int i = 2; i <= L.length; ++i) {
        // 将L.r[i]暂存到L.r[0]
        L.r[0] = L.r[i]; 

        // 设置折半查找的范围       
        int low = 1;
        int high = i - 1;

        // 折半查询（默认递增有序）
        while (low <= high) {
            // 取中间点
            int mid = (low + high) / 2;

            if (L.r[0].key < L.r[mid].key) {
                high = mid - 1;                 // 查找左半子表
            } else {
                low = mid + 1;                  // 查找右半子表
            }
        }
        
        for (int j = i - 1; j >= high + 1; --j) {
            L.r[j + 1] = L.r[j];                // 统一后移元素，空出插入位置
        }

        // 将r[0]即原r[i]，插入到正确位置
        L.r[high + 1] = L.r[0];
    }
}