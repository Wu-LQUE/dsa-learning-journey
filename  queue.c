#include <stdio.h>
#define MAXSIZE 3
typedef struct QNode * Queue;
struct QNode
{
    int data[MAXSIZE];
    int front;//头，删除位置的前一个，指向空，+1后删除
    int rear;//队列的尾巴，+1后入队
};
//为了避免front == rear时无法区分是空还是满的状况，只存入MAXSIZE-1个元素
void addQ(Queue que,int val){
    if((que->rear+1)%MAXSIZE==que->front){
        printf("队列满");
        return;
    }
    //为了实现循环，用求余。
    que->rear=(que->rear+1)%MAXSIZE;
    que->data[que->rear] = val;
}
int deleteQ(Queue que){
    if(que->front==que->rear){
        printf("队列满");
        return -1;
    }else{
        que->front=(que->front+1)%MAXSIZE;
        return que->data[que->front];
    }
}
int main(){
}