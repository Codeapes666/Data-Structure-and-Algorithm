#include <stdio.h>
#include <stdlib.h>

// 哈夫曼树的存储表示
typedef struct {
    int weight;                 // 结点的权值
    int parent;                 // 结点双亲的下标
    int lchild;                 // 结点左孩子的下标
    int rchild;                 // 结点右孩子的下标
}HTNode, *HuffmanTree;          // 动态分配数组存储哈夫曼树

// 选择
void Select(HuffmanTree &HT, int n, int &s1, int &s2)
{
    int minum = 0;              // 定义一个临时变量保存最小值
    int i = 0;
    for (i = 1; i <= n; ++i) {  // 以下是找到第一个最小值
    
        if (HT[i].parent == 0) {
            minum = i;
            break;
        }
    }
    for (i = 1; i <= n; ++i) {
        if (HT[i].parent == 0) {
            if (HT[i].weight < HT[minum].weight) {
                minum = i;
            }
        }
    }

    s1 = minum;
    // 以下是找到第二个最小值，且与第一个不同
    for (i = 1; i <= n; ++i) {
        if (HT[i].parent == 0 && i != s1) {
            minum = i;
            break;
        }
    }
    for (i = 1; i <= n; ++i) {
        if (HT[i].parent == 0 && i != s1) {
            if (HT[i].weight < HT[minum].weight) {
                minum = i;
            }
        }
    }
    s2 = minum;
}

// 构造哈夫曼树
void CreateHuffmanTree(HuffmanTree &HT, int n)
{   
    int i = 0;
    int m = 0;
    int s1 = 0;
    int s2 = 0;

    if (n <= 1) {
        return;
    }

    m = 2*n - 1;
    HT = (HTNode*)malloc(sizeof(HTNode) * (m + 1));     // 0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根结点
    if (HT == NULL) {
        return;
    }

    for (i = 1; i <= m; ++i) {      // 将1~m号单元中的双亲、左孩子、右孩子的下标都初始化为0
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }

    for (i = 1; i <= n; ++i) {      // 输入前n个单元中叶子结点的权值
        scanf("%d", &HT[i].weight);
    }
    
    /*---------- 初始化工作结束，下面开始创建哈夫曼树 ----------*/

    for (i = n + 1; i <= m; ++i) {  // 通过n-1次的选择、删除、合并来创建哈夫曼树
        
        // 在HT[k]（1 ≤ k ≤ i-1）中选择两个其双亲域为0且权值最小的结点，并返回它们在HT中的序号s1和s2
        Select(HT, i - 1, s1, s2);

        // 得到新结点i，从森林中删除s1、s2，将s1和s2的双亲域由0改为i
        HT[s1].parent = i;
        HT[s2].parent = i;

        // s1、s2分别作为i的左右孩子
        HT[i].lchild = s1;
        HT[i].rchild = s2;

        // i的权值为左右孩子权值之和
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}