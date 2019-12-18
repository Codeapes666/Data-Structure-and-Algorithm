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


// Partition为分割函数
int Partition(SeqList &L, int low, int high) {
    // 用子表的第一个记录做基准值
    L.r[0] = L.r[low];

    // 基准值关键字保存在pivotkey中
    int pivotkey = L.r[low].key; 

    // 循环跳出条件
    while (low < high) {
        while (low < high && L.r[high].key >= pivotkey) {
            --high;
        }

        // 将比基准值小的元素移动到左端
        L.r[low] = L.r[high];

        while (low < high && L.r[low].key <= pivotkey) {
            ++low;
        }

        // 将比基准值大的元素移动到右端
        L.r[high] = L.r[low];
    }

    // 基准元素存放到最终位置
    L.r[low] = L.r[0];

    // 返回基准值位置
    return low;
}

// 快速排序
// 平均时间复杂度：O(nlog2n)
// 空间复杂度：O(log2n)
// 稳定性：不稳定
void QuickSort(SeqList &L, int low, int high) {

    // 调用前置初值：low = 1; high = L.length;
    if (low < high) {
        // 将data[low...high]一分为二，pivotpos是基准值
        int pivotpos = Partition(L, low, high);

        // 对左子表进行递归排序
        QuickSort(L, low, pivotpos - 1);

        // 对右子表进行递归排序
        QuickSort(L, pivotpos + 1, high);
    }
}
