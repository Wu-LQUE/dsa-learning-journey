#ifndef QUEUELINK_H
#define QUEUELINK_H

#include "BinTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef BinTree ElementType;
typedef struct QNode * Queue;
typedef struct ANode * Node;

struct ANode {
    ElementType data;
    Node nextNode;
};

struct QNode {
    Node front;
    Node rear;
};

/* 创建一个空队列，失败返回 NULL */
Queue createQueue(void);

/* 入队，返回入队的值（若 queue 为 NULL 或分配失败，返回传入 val） */
ElementType addQ(Queue queue, ElementType val);

/* 出队，若队列为空返回 INT_MIN（并打印错误信息），否则返回出队元素 */
ElementType deleteQ(Queue queue);

/* 判断队列是否为空，返回 1 表示空，0 表示非空 */
int isEmptyQueue(Queue queue);

/* 释放队列及其所有结点 */
void destroyQueue(Queue queue);

#endif /* QUEUELINK_H */