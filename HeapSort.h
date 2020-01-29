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

// 向下调整堆
void HeapAdjustDown(SeqList &L, int s, int m)
{// 假设r[s+1...m]已经是堆，将r[s...m]调整为以r[s]为根的大根堆
    L.r[0] = L.r[s];

    // 沿key较大的子结点向下筛选
    for (int i = 2 * s; i <= m; i *= 2) {
        if (i < m && L.r[i].key < L.r[i + 1].key) {
            // i为key较大的记录的下标
            ++i;
        }

        if (L.r[0].key >= L.r[i].key) {
            break;
        }
        // 将L.r[i]调整到双亲结点上
        L.r[s] = L.r[i];

        // 修改s值，以便继续向下筛选
        s = i;
    }
    // 被筛选结点的值放入最终位置
    L.r[s] = L.r[0];
}

// 向上调整堆
void HeapAdjustUp(SeqList &L, int m) 
{// 参数m为向上调整的结点，也为堆的元素个数
    L.r[0] = L.r[m];

    // 若结点值大于双亲结点，则将双亲结点向下调，并继续向上比较
    int i = m / 2;

    // 循环跳出条件
    while (i > 0 && L.r[i].key < L.r[0].key) {
        // 双亲结点下调
        L.r[m] = L.r[i];
        m = i;
        // 继续向上比较
        i = m / 2;
    }
    // 复制到最终位置
    L.r[m] = L.r[0];
}

// 初始建堆
void CreatHeap(SeqList &L)
{
    int n = L.length;

    for (int i = n / 2; i > 0; --i) {
        HeapAdjustDown(L, i, n);
    }
}

// 堆排序
// 时间复杂度：O(nlog2n)
// 空间复杂度：O(1)
// 稳定性：不稳定
void HeapSort(SeqList &L)
{
    CreatHeap(L);

    for (int i = L.length; i > 1; --i) {
        // 将堆顶记录和当前未经排序子序列L.r[1...i]中最后一个记录互换
        RedType temp = L.r[1];
        L.r[1] = L.r[i];
        L.r[i] = temp;

        // 将L.r[1...i-1]重新调整为大根堆
        HeapAdjustDown(L, 1, i - 1);
    }
}