#define MAXSIZE 50              // 顺序表的最大长度

#define TRUE 1
#define FALSE 0

typedef int KeyType;            // 定义关键字类型为整型

typedef struct {
    KeyType key;                // 关键字项
    InfoType otherinfo;         // 其它数据项
}RedType;                       // 记录类型

typedef struct {
    RedType r[MAXSIZE + 1];     // r[0]闲置或用做哨兵
    int length;                 // 顺序表长度
}SeqList;                       // 顺序表类型

// 冒泡排序
// 平均时间复杂度：O(n²)
// 空间复杂度：O(1)
// 稳定性：稳定
void BubbleSort(SeqList &L)
{
    int i = 0;
    int m = L.length - 1;
    int flag = 1;               // flag用来标记某一趟排序是否发生交换

    while (m > 0 && flag == 1) {
        // flag置为0，如果本趟排序没有发生交换，则不会执行下一趟排序
        flag = 0;

        for (i = 1; i <= m; ++i) {
            if (L.r[i].key > L.r[i + 1].key) {
                // flag置为1，表示本趟排序发生交换
                flag = 1;

                // 交换前后两个记录
                RedType temp = L.r[i];
                L.r[i] = L.r[i + 1];
                L.r[i] = temp;
            }
        }
        --m;
    }
}

// 冒泡排序第2种方法
void BubbleSort2(SeqList &L)
{
    int i = 0;
    int j = 0;
    int m = L.length - 1;
    int flag = TRUE;               // flag用来标记某一趟排序是否发生交换

    for (i = 0; i < m; ++i) {
        // flag置为0，如果本趟排序没有发生交换，则不会执行下一趟排序
        flag = FALSE;

        for (j = m; j > i; --j) {
            if (L.r[j - 1].key > L.r[j].key) {
                // flag置为1，表示本趟排序发生交换
                flag = TRUE;

                // 交换前后两个记录
                RedType temp = L.r[j - 1];
                L.r[j - 1] = L.r[j];
                L.r[j] = temp;
            }
        }
        if (flag == FALSE) {
            return ;                // 本趟遍历后没有发生交换，说明表已经有序
        }
    }
}