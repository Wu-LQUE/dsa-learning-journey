#ifndef HEAP_H
#define HEAP_H
#define MaxHeapData 2147483647
#define MinHeapData -2147483648
typedef int ElementType;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct{
    ElementType *elements;//存元素的数组
    int size;//当前元素个数
    int capacity;//堆的最大容量
};
MaxHeap create(int maxSize);
#endif