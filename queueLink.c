#include "queueLink.h"
Queue createQueue(){
    Queue queue = (Queue) malloc(sizeof(struct QNode));
    if (!queue) {
        perror("createQueue: malloc failed");
        return NULL;
    }
    queue->front=NULL;
    queue->rear=NULL;
    return queue;
}
ElementType addQ(Queue queue,ElementType val){
    if (!queue) {
        fprintf(stderr, "addQ: queue is NULL, cannot add\n");
        return val;
    }
    Node newNode = (Node) malloc(sizeof(struct ANode));
    if (!newNode) {
        perror("addQ: malloc failed");
        return val;
    }
    newNode->data = val;
    newNode->nextNode=NULL;
    if(queue->rear==NULL){//如果队列为空，首尾都指向新增节点
        queue->rear=newNode;
        queue->front=newNode;
    }else{
        //队尾的下一个节点
        queue->rear->nextNode = newNode;
        //排到队尾
        queue->rear = newNode;
    }
    return NULL;
}
ElementType deleteQ(Queue queue){
    ElementType data;
    if (!queue || queue->front == NULL) {
        fprintf(stderr, "deleteQ: queue is empty\n");
        data = NULL; /* 作为出错返回值 */
    }else if(queue->front==queue->rear){
        //只有一个元素
        data = queue->front->data;
        free(queue->front);
        // queue->front==NULL;
        queue->rear=NULL;
        queue->front=NULL;
    }else{
        Node nextNode = queue->front->nextNode;
        data = queue->front->data;
        free(queue->front);
        queue->front=nextNode;
    }
    return data;
}
int isEmptyQueue(Queue queue) {
    return (queue == NULL) || (queue->front == NULL);
}

void destroyQueue(Queue queue) {
    if (!queue) return;
    Node cur = queue->front;
    while (cur) {
        Node next = cur->nextNode;
        free(cur);
        cur = next;
    }
    free(queue);
}