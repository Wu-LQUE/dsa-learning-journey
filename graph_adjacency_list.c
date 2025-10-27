#include <stdio.h>
#include <stdlib.h>
#define MAX_GRAPH_SIZE 10

typedef struct AGraphtAdjList {
    AdjListNode *heads[MAX_GRAPH_SIZE];
    int size;
} GraphtAdjList;

typedef struct AVertex {
    int vertex;
} Vertex;

typedef struct A_AdjListNode
{
    Vertex *vertex;
    AdjListNode *next;
} AdjListNode;

AdjListNode *findNode(GraphtAdjList *graph,Vertex *vet) {
    for (int i = 0; i < graph->size; i++) {
        if (graph->heads[i]->vertex == vet) {
            return graph->heads[i];
        }
    }
    return NULL;
}

void addEdgeHelper(AdjListNode *head,Vertex *vet) {
    AdjListNode *node = (AdjListNode *) malloc(sizeof(AdjListNode));
    node->vertex = vet;
    node->next = head->next;
    head->next = node;
}

void removeEdgeHelper(AdjListNode *head,Vertex *vet) {
    AdjListNode *pre = head;
    AdjListNode *cur = head->next;
    while (cur !=NULL && cur->vertex != vet) {
        pre = cur;
        cur = cur->next;
    }
    if(cur == NULL) {
        return;
    }
    pre->next = cur->next;
    free(cur);
}

GraphtAdjList *newGraphAdjList() {
    GraphtAdjList *graph = (GraphtAdjList*) malloc(sizeof(GraphtAdjList));
    if (!graph) return NULL;
    graph->size = 0;
    for (int i = 0; i < MAX_GRAPH_SIZE; i++) {
        graph->heads[i] = NULL;
    }
    return graph;
}

void delGraphAdjList(GraphtAdjList *graph) {
    if(!graph) return;
    for(int i = 0;i < graph->size;i++){
        AdjListNode *cur = graph->heads[i];
        while (cur) {
            AdjListNode *next = cur->next;
            free(cur->vertex);
            if(cur != graph->heads[i]) {
                 free(cur);
            }
            cur = next;
        }
        free(graph->heads[i]->vertex);
        free(graph->heads[i]);
    }
    free(graph);
}

AdjListNode *findNode(GraphtAdjList *graph,Vertex *vet) {
    for (int i = 0; i < graph->size; i++) {
        if (graph->heads[i]->vertex == vet) {
            return graph->heads[i];
        }
    }
    return NULL;
}

void addEdge(GraphtAdjList *graph,Vertex *vet1,Vertex *vet2) {
    AdjListNode *head1 = findNode(graph,vet1);
    AdjListNode *head2 = findNode(graph,vet2);
    assert(head1 != NULL && head2 != NULL && head1 != head2);
    addEdgeHelper(head1,vet2);
    addEdgeHelper(head2,vet1);
}

void removeEdge(GraphtAdjList *graph,Vertex *vet1,Vertex *vet2) {
    AdjListNode *head1 = findNode(graph,vet1);
    AdjListNode *head2 = findNode(graph,vet2);
    assert(head1 != NULL && head2 != NULL);
    removeEdgeHelper(head1,head2->vertex);
    removeEdgeHelper(head2,head1->vertex);
}

void addVertex(GraphtAdjList *graph,Vertex *vet) {
    assert(graph !=NULL&&graph->size < MAX_GRAPH_SIZE);
    AdjListNode *head = (AdjListNode *) malloc(sizeof(AdjListNode));
    head->vertex= vet;
    head->next =NULL;
    graph->heads[graph->size++] = head;
}

void removeVertex(GraphtAdjList *graph,Vertex *vet) {
    AdjListNode *node = findNode(graph,vet);
    asser(node !=NULL);
    AdjListNode *cur = node,*pre = NULL;
    while (cur) {
        pre = cur;
        cur = cur->next;
        free(pre);
    }
    for (int i = 0; i < graph->size; i++) {
        cur = graph->heads[i];
        pre = NULL;
        while (cur) {
            pre = cur;
            cur = cur->next;
            if (cur && cur->vertex == vet) {
                pre->next = cur->next;
                free(cur);
            }
        }
    }
    int i;
    for(i = 0;i < graph->size; i++) {
        if (graph->heads[i] == node) break;
    }
    for(int j = i; j < graph->size - 1; j++) {
        graph->heads[j] = graph->heads[j+1];
    }
    graph->size--;
    free(vet);
}