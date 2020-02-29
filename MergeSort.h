#include <stdlib.h>

#define MAXSIZE 50              // 顺序表的最大长度

// 待排序记录的数据类型定义
typedef int KeyType;            // 定义关键字类型为整型

typedef struct {
    KeyType key;                // 关键字项
}RedType;                       // 记录类型

typedef struct {
    RedType* r;                 // r[0]闲置或用做哨兵
    int length;                 // 顺序表长度
}SeqList;                       // 顺序表类型

// 归并相邻两个有序子序列
// 将有序表R.r[low...mid]和R.r[mid + 1...high]归并为有序表L->r[low...high]
void Merge(SeqList R, SeqList* L, int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = low;

    // 将R中记录由小大并入L中
    while (i <= mid && j <= high) {
        if (R.r[i].key <= R.r[j].key) {
            L->r[k] = R.r[i++];
        } else {
            L->r[k] = R.r[j++];
        }
    }

    // 将剩余的R.r[low...mid]复制到L中
    while (i <= mid) {
        L->r[k++] = R.r[i++];
    }

    // 将剩余的R.r[j...high]复制到L中
    while (j <= high) {
        L->r[k++] = R.r[j++];
    }   
}

// 归并排序
// 时间复杂度：O(nlog2n)
// 空间复杂度：O(n)
// 稳定性：稳定
void MergeSort(SeqList R, SeqList* L, int low, int high)
{
    if (low == high) {
        L->r[low] = R.r[low];
    } else {
        // 初始化结构体对象
        SeqList S = {NULL, 0};

        S.r = (RedType*)malloc(sizeof(RedType) * MAXSIZE);

        // 若内存分配失败，直接return
        if (S.r == NULL) {
            return;
        }

        // 将当前序列一分为二，求中间位置
        int mid = (low + high) / 2;
        
        // 对子序列R.r[low...mid]递归归并排序，结果放入S.r[low...mid]
        MergeSort(R, &S, low, mid);

        // 对子序列R.r[mid + 1...high]递归归并排序，结果放入S.r[mid + 1...high]
        MergeSort(R, &S, mid + 1, high);

        // 将S.r[low...mid]和S.r[mid + 1...high]归并到L->r[low...high]
        Merge(S, L, low, mid, high);

        if (S.r != NULL) {
            // 释放内存
            free(S.r);
            // 指针置空
            S.r = NULL;
        }
    }

}