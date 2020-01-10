#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 哈夫曼树的存储表示
typedef struct {
    int weight;                 // 结点的权值
    int parent;                 // 结点双亲的下标
    int lchild;                 // 结点左孩子的下标
    int rchild;                 // 结点右孩子的下标
}HTNode, *HuffmanTree;          // 动态分配数组存储哈夫曼树

// 哈夫曼树中的查找
// HT数组中存放的哈夫曼树，end表示HT数组中存放结点的最终位置，s1和s2传递的是HT数组中权重值最小的两个结点在数组中的位置
void Select(HuffmanTree HT, int end, int &s1, int &s2)
{
    int min1 = 0;
    int min2 = 0;
    int i = 1;                  // 遍历数组初始下标为 1
    
    // 找到还没构建树的结点
    while (HT[i].parent != 0 && i <= end) {
        ++i;
    }

    min1 = HT[i].weight;
    s1 = i;

    i++;
    while (HT[i].parent != 0 && i <= end) {
        ++i;
    }

    // 对找到的两个结点比较大小，min2为大的，min1为小的
    if (HT[i].weight < min1) {
        min2 = min1;
        s2 = s1;
        min1 = HT[i].weight;
        s1 = i;
    } else {
        min2 = HT[i].weight;
        s2 = i;
    }
    // 两个结点和后续的所有未构建成树的结点做比较
    for (int j = i + 1; j <= end; ++j) {
        // 如果有父结点，直接跳过，进行下一个
        if (HT[j].parent != 0) {
            continue;
        }

        // 如果比最小的还小，将min2 = min1，min1赋值新的结点的下标
        if (HT[j].weight < min1) {
            min2 = min1;
            min1 = HT[j].weight;
            s2 = s1;
            s1 = j;
        } else if (HT[j].weight >= min1 && HT[j].weight < min2) {
            // 如果介于两者之间，min2赋值为新的结点的位置下标
            min2 = HT[j].weight;
            s2 = j;
        }
    }
}

// 构造哈夫曼树
// HT为地址传递的存储哈夫曼树的数组，w为存储结点权重值的数组，n为结点个数
void CreateHuffmanTree(HuffmanTree &HT, int &w, int n)
{   
    int i = 0;
    int m = 0;

    if (n <= 1) {                   // 如果只有一个编码就相当于0
        return;
    }

    m = 2*n - 1;                    // m为哈夫曼总结点数，n为叶结点数

    // 0号单元未用，所以需要动态分配m+1个单元，HT[m]表示根结点
    HT = (HTNode*)malloc(sizeof(HTNode) * (m + 1));     
    if (HT == NULL) {               // 内存若分配失败
        return;
    }

    for (i = 1; i <= n; ++i) {      // 初始化哈夫曼树中的所有结点
        HT[i].weight = w + i - 1;
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }

    for (i = n + 1; i <= m; ++i) {  // 从数组的下标n+1开始初始化哈夫曼树中除叶子结点外的结点
        HT[i].weight = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }

    
    /*---------- 初始化工作结束，下面开始创建哈夫曼树 ----------*/

    for (i = n + 1; i <= m; ++i) {  // 通过n-1次的选择、删除、合并来创建哈夫曼树
        int s1 = 0;
        int s2 = 0;

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


// 哈夫曼编码表的存储表示
typedef char **HuffmanCode;         // 动态分配数组存储哈夫曼编码表

// 求哈夫曼编码
void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{   // 从叶子到根逆向求每个字符的哈弗曼编码，存储在编码表HC中
    HC = (HuffmanCode)malloc(sizeof(char *) * (n + 1));         // 分配存储n个字符编码的编码表空间
    char* cd = (char*)malloc(sizeof(char) * n);                 // 分配临时存放每个字符编码的动态数组空间
    cd[n - 1] = '\0';                                           // 编码结束符
    int i = 0;                  
    for (i = 1; i <= n; ++i) {                                  
        // 从叶子结点出发，得到的哈夫曼编码是逆序的，需要在字符串数组中逆序存放
        int start = n - 1;                                      // start开始时指向最后，即编码结束符位置
        int c = i;                                              // 当前结点在数组中的位置
        int f = HT[i].parent;                                   // 当前结点的父结点在数组中的位置

        while (f != 0) {                                        // 从叶子结点开始向上回溯，直到根结点
            --start;                                            // 回溯一次start向前指一个位置
            if (HT[f].lchild == c) {                            // 结点c是f的左孩子，则生成代码0
                cd[start] = '0';
            } else {                                            // 结点c是f的右孩子，则生成代码1
                cd[start] = '1';
            }

            c = f;                                              // 以父结点为孩子结点，继续向上回溯
            f = HT[f].parent;                                 
        }

        // 跳出循环后，cd数组中从下标start开始，存放的就是该结点的哈夫曼编码
        HC[i] = (char*)malloc(sizeof(char) * (n - start));      // 为第i个字符编码分配空间
        strcpy(HC[i], &cd[start]);                              // 将求得的编码从临时空间cd复制到HC的当前行中
    }

    free(cd);                                                   // 释放临时空间
}