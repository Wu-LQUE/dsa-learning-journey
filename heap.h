#ifndef HEAP_H
#define HEAP_H
#include <limits.h>
#define MaxHeapData INT_MAX
#define MinHeapData INT_MIN
typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    ElementType *elements;//存元素的数组
    int size;//当前元素个数
    int capacity;//堆的最大容量
};
MaxHeap create(int maxSize);
#endif