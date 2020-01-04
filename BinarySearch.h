typedef int KeyType;

// 待查找的数据元素类型定义
typedef struct {
    KeyType key;        // 关键字域
}ElemType;

typedef struct {
    ElemType* elem;     // 存储空间基地址，建表时按实际长度分配，ST.elem[0]闲置不用
    int length;         // 当前表长度
}SSTable;

// 折半查找（二分查找）
// 必须采用顺序存储结构
// 时间复杂度：O(log2n)
int BinarySearch(SSTable ST, KeyType Key)
{   // 在有序表ST中折半查找其关键字等于key的数据元素。
    // 若找到，则函数值为该元素在表中的位置，否则为0
    int low = 1;
    int high = ST.length;

    while (low <= high) {
        int mid = (low + high) / 2;             // 取中间值
        if (ST.elem[mid].key == Key) {          // 找到待查元素
            return mid;
        } else if(ST.elem[mid].key > Key) {     // 从前半部分继续查找
            high = mid - 1;
        } else {
            low = mid + 1;                      // 从后半部分继续查找
        }
    }

    return 0;
}