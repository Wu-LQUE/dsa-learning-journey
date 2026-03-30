#include "heap.h"
#include "huffmanTree.h"
#include "stdlib.h"
void BuildMinHeap(MinHeap heap){
    if(!heap||heap->size==0) return;
    for(int notLeafNode = heap->size/2;notLeafNode>=1;notLeafNode--){
        ElementType temp = heap->elements[notLeafNode];
        int parent=notLeafNode,child;
        for(;parent*2<=heap->size;parent=child){
            child = parent * 2;
            if(child+1<=heap->size&&heap->elements[child+1]->weight < heap->elements[child]->weight) child++;
            if(temp->weight<=heap->elements[child]->weight) break;
            heap->elements[parent] = heap->elements[child];
        }
        heap->elements[parent] = temp;
    }
}
//哈夫曼树的构造:不断选取两个权值和最小的树合并
//可以利用最小堆来做到每次选取最小的两个树
HuffmanTree huffman(Heap H){
    if (!H || H->size == 0) return NULL;
    int i;
    HuffmanTree T;
    BuildMinHeap(H);
    /*//有size个节点，只用做size-1此合并
    int size = H->size;
    for(int i = 1;i <= size - 1;i++){
        //从最小堆中(树从权值最小放到权值最大)挑选两个树，合并成新树
        T = malloc(sizeof(struct HuffmanTreeNode));
        T->left = deleteMin(H);
        T->right = deleteMin(H);
        T->weight = T->left->weight + T->right->weight;
        insertToMin(H,T);//将新树放入堆中(在合适的位置)
    }*/

   /*while 更直观、对未来改动更健壮：如果后续实现发生变化（例如某次合并逻辑被条件短路、或出现异常导致某轮未插回新节点），
   
   while 能自然停止在 size<=1；for 固定跑 n-1 次则可能在不满足“有两个可删节点”时继续执行，从而触发错误*/
    while (H->size > 1) {
        HuffmanTree a = deleteMin(H);
        HuffmanTree b = deleteMin(H);
        if (!a || !b) return NULL; // 防御：不应发生
        HuffmanTree t = malloc(sizeof(*t));
        if (!t) return NULL;
        t->left = a;
        t->right = b;
        t->weight = a->weight + b->weight;

        insertToMin(H, t);
    }
    //取出最后构造的哈夫曼树
    T = deleteMin(H);
    return T;
}
