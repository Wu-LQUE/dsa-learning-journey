#ifndef HEAP_H
#define HEAP_H
#include <limits.h>
#define MaxHeapData INT_MAX
#define MinHeapData INT_MIN
typedef struct HuffmanTreeNode *ElementType;
typedef struct HeapStruct *MaxHeap;
typedef struct HeapStruct *MinHeap;
typedef struct HeapStruct *Heap;
struct HeapStruct
{
    ElementType *elements; // 存元素的数组
    int size;              // 当前元素个数
    int capacity;          // 堆的最大容量
};
MinHeap createMinHeapBySequence(int size, int *array);
MaxHeap createMaxHeapBySequence(int size, int *array);
MaxHeap createMaxHeap(int maxSize);
MinHeap createMinHeap(int maxSize);
ElementType deleteMax(MaxHeap H);
ElementType deleteMin(MinHeap heap);
void insertToMin(MinHeap heap, ElementType item);
void insertToMax(MaxHeap H,ElementType item);
#endif