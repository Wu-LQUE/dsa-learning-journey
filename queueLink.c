//不带头节点的链表实现的队列
#include <stdio.h>
typedef struct QNode * Queue;
typedef struct ANode * Node;
struct ANode
{
    int data;
    Node nextNode;
};
struct QNode{
    Node front;
    Node rear;
};
int deleteQ(Queue queue){
    int data;
    if(queue->front==NULL){
        printf("队列空");
        data=-1;
    }else if(queue->front==queue->rear){
        //只有一个元素
        data = queue->front->data;
        free(queue->front);
        queue->front==NULL;
        queue->rear=NULL;
    }else{
        Node nextNode = queue->front->nextNode;
        data = queue->front->data;
        free(queue->front);
        queue->front=nextNode;
    }
    return data;
}