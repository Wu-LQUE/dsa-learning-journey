#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 10

//每个heads[i]是一个"头节点",其vertex指向本节点对象,next指向邻接链表
typedef struct GraphAdjList {
    AdjListNode *heads[MAX_GRAPH_SIZE];
    int vertex_count;
} GraphAdjList;

typedef struct GraphVertex {
    int id;//顶点标识
} GraphVertex;

//边节点,有顶点的引用，和指向下一个节点的指针
typedef struct AdjListNode
{
    GraphVertex *vertex;//边节点不拥有vertex,仅引用
    AdjListNode *next;
} AdjListNode;
