#include "heap.h"
typedef struct TreeNode * HuffmanTree;
struct TreeNode
{
    int weight;
    HuffmanTree left,right;
};



//哈夫曼树的构造:不断选取两个权值和最小的树合并
//可以了利用最小堆来做到每次选取最小的两个树
HuffmanTree huffman(MinHeap H){
    int i;
    HuffmanTree T;
    BuildMinHeap(H);
    //有size个节点，只用做size-1此合并
    for(int i = 1;i <= H->size - 1;i++){
        //从最小堆中(树从权值最小放到权值最大)挑选两个树，合并成新树
        T = malloc(sizeof(struct TreeNode));
        T->left = deleteMin(H);
        T->right = deleteMin(H);
        insert(H,T);//将新树放入堆中(在合适的位置)
    }
    //取出最后构造的哈夫曼树
    T = deleteMin(H);
}
