#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 10
typedef struct AGraphAdjMat {
    int vertices[MAX_GRAPH_SIZE];
    int adjMat[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
    int size;
} GraphAdjMat;
GraphAdjMat *newGraphAdjMat() {
    GraphAdjMat *graph = (GraphAdjMat*) malloc(sizeof(GraphAdjMat));
    graph->size=0;
    for(int i = 0;i<MAX_GRAPH_SIZE;i++) {
        graph->vertices[i] = 0;
        for (int j = 0; j < MAX_GRAPH_SIZE; j++) {
            graph->adjMat[i][j] = 0;
        }
    }
    return graph;
}

void delGraphAdjMatrix(GraphAdjMat *graph) {
    free(graph);
}

void addVertex(GraphAdjMat *graph, int val) {
    if (graph->size == MAX_GRAPH_SIZE) {
        fprintf(stderr,"图的节点数量已达最大\n");
        return;
    }
    int n = graph->size;
    graph->vertices[n] = val;
    for (int i = 0; i <= n; i++) {
        graph->adjMat[n][i] = graph->adjMat[i][n] = 0;
    }
    graph->size++;
}

void removeVertex(GraphAdjMat *graph,int index) {
    if (index < 0 || index >= graph->size) {
        fprintf(stderr,"顶点索引越界\n");
        return;
    }
    //index的下面所有值向上覆盖一行
    for (int i = index; i < graph->size-1; i++) {
        graph->vertices[i] = graph->vertices[i+1];
    }
    for (int i = index; i < graph->size-1; i++) {
        for (int j = 0; j < graph->size; j++) {
            graph->adjMat[i][j] = graph->adjMat[i+1][j];
        }
    }
    //已经少了一行,i<graph.size-1即可
    for (int j = index; j < graph->size-1; j++) {
        for (int i = 0; i < graph->size - 1; i++) {
            graph->adjMat[i][j] = graph->adjMat[i][j+1];
        }
    }
    graph->size--;
}

void addEdge(GraphAdjMat *graph,int i,int j) {
    if (i < 0 || j < 0|| i >= graph->size || j >= graph->size) {
        fprintf(stderr,"顶点索引越界\n");
        return;
    }
    graph->adjMat[i][j] = graph->adjMat[j][i] = 1;
}

void removeEdge(GraphAdjMat *graph,int i,int j) {
    if (i < 0 || j < 0|| i >= graph->size || j >= graph->size) {
        fprintf(stderr,"顶点索引越界\n");
        return;
    }
    graph->adjMat[i][j] = graph->adjMat[j][i] = 0;
}

void printArray(int *array,int size) {
    printf("[");
    for(int i = 0;i<size;i++) {
        printf("%d",array[i]);
        if(i<size-1) {
            printf(",");
        }
    }
    printf("]\n");
}

void printGraphAdjMat(GraphAdjMat *graph) {
    printf("顶点列表 = ");    
    printArray(graph->vertices,graph->size);
    printf("邻接矩阵");
    for (int i = 0; i < graph->size; i++) {
        printArray(graph->adjMat[i],graph->size);
    }
}

