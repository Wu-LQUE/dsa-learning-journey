#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//最大堆是一个完全二叉树，放数组里，从1开始放
MaxHeap create(int maxSize){
    MaxHeap H = malloc(sizeof(struct HeapStruct));
    //从堆下标为1开始放 
    H->elements = malloc((maxSize+1)*sizeof(ElementType));
    H->size = 0;
    H->capacity = maxSize;
    H->elements[0] = MaxHeapData;
    //定义哨兵为大于堆中所有可能元素的值，便于以后更快操作
    return H;
}
static int isFull(MaxHeap H){
    if(H->size==H->capacity) return 1;
    else return 0;
}
static int isEmpty(MaxHeap H){
    return H->size==0;
}
//size从0开始
static void insert(MaxHeap H,ElementType item){
    int i;
    if(isFull(H)){
        printf("最大堆已满");
        return;
    }
    H->size = H->size + 1;
    i = H->size;//i指向要插入item的位置(原最后一个元素的下一个)
    //相当于一个冒泡排序，item不断上浮，最高到elements[1]<=maxSignedInt
    for(;H->elements[i/2]<item;i/=2){
        H->elements[i] = H->elements[i/2];
    }
    H->elements[i] = item;
}
// static int deleteMax(MaxHeap H){
//     if(isEmpty(H)){
//         printf("最大堆已空");
//         return MinHeapData;
//     }
//     int maxElement = H->elements[1];
//     //取出最后一个值放首位，size-1
//     int lastElement = H->elements[(H->size)--];
//     H->elements[1] = lastElement;
//     //将lastElement放在合适的位置
//     int i = 1;
//     while(1){
//         int leftChild = 2 * i <= H->size ? H->elements[2*i] : MinHeapData;
//         int rightChild = 2 * i + 1 <= H->size ? H->elements[2*i+1] : MinHeapData;
//         int maxChild = leftChild > rightChild ? leftChild : rightChild;
//         if(maxChild <= lastElement){
//             break;
//         }else if (leftChild == maxChild)
//         {
//             H->elements[2*i] = lastElement;
//             H->elements[i] = leftChild;
//             i = 2*i;
//             continue;
//         }else{
//             H->elements[2*i+1] = lastElement;
//             H->elements[i] = rightChild;
//             i = 2*i+1;
//             continue;
//         }
//     }
//     return maxElement;
// }

/*“标准下滤”写法：不必先把 lastElement 放到根再与子节点两两交换，直接用一个临时变量一路下滤，
赋值次数更少、逻辑更清晰，也避免使用 MinHeapData 作为“哨兵子节点”的技巧。*/
static int deleteMax(MaxHeap H){
    if(isEmpty(H)){
        printf("最大堆已空");
        return MinHeapData;
    }
    ElementType maxItem = H->elements[1];
    ElementType temp = H->elements[H->size--];
    int parent = 1,child;
    //只要存在左儿子
    for(;parent*2<=H->size;parent=child){
        child = parent * 2;
        // 选出最大的孩子
        if(child != H->size && H->elements[child] < H->elements[child+1]){
            child++;
        }
        //找到tmp的位置
        if(temp >= H->elements[child]) break;
        H->elements[parent] = H->elements[child];
    }
    H->elements[parent] = temp;
    return maxItem;
}
static MaxHeap createMaxHeapBySequence(int size,int *array){
    MaxHeap heap = create(size);
    if (!heap) return NULL;
    if (size <= 0) return heap;
    if (!array) { // 防御式检查
        heap->size = 0;
        return heap;
    }
    for(int i = 1;i<=size;i++){
        //array[0到size-1] =>elements[1到size]
        heap->elements[i]=array[i-1];
    }
    heap->size = size;
    if(heap->size==1) return heap;
    int idx = heap->size;
    int parentNode = idx/2;
    while (1)
    {
        int parent = parentNode;
        ElementType tmp = heap->elements[parent];
        int child;
        while(1){
            child = parent * 2;
            if(child>heap->size) break;
            if(child != heap->size&&heap->elements[child]<heap->elements[child+1]){
                child++;
            }
            if(tmp>=heap->elements[child]) break;
            heap->elements[parent] = heap->elements[child];
            parent=child;
        }
        heap->elements[parent] = tmp;
        if(parentNode == 1) break;
        idx-=2;
        parentNode = idx/2;
    }
    return heap;
}