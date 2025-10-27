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

/* 内部辅助函数（静态） */
static AdjListNode *find_head_by_vertex_ptr(const GraphAdjList *g, const GraphVertex *v) {
    if (!g || !v) return NULL;
    for (int i = 0; i < g->vertex_count; ++i) {
        //将头节点的vertex指针和参数的vertex指针匹配，检测头节点里是否已经存在vertex
        if (g->heads[i] && g->heads[i]->vertex == v) {
            return g->heads[i];
        }
    }
    return NULL;
}

static int edge_exists(const AdjListNode *head, const GraphVertex *v) {
    for (const AdjListNode *cur = head ? head->next : NULL; cur; cur = cur->next) {
        if (cur->vertex == v) return 1;
    }
    return 0;
}

//新增一条单向边
static int add_edge_oneway(AdjListNode *head, GraphVertex *to) {
    if (!head || !to) return -1;
    if (edge_exists(head, to)) return 0; /* 已存在则忽略，返回0表示“无变更” */
    AdjListNode *node = (AdjListNode *)malloc(sizeof(*node));
    if (!node) return -2;
    node->vertex = to;
    node->next = head->next;
    head->next = node;
    return 1; /* 新增成功 */
}

static int remove_edge_oneway(AdjListNode *head,const GraphVertex *to) {
    if (!head || !to) return -1;
    AdjListNode *pre = head,*cur = head->next;
    while (cur)
    {
        if (cur->vertex = to) {
            pre->next = cur->next;
            free(cur);//vertex是头节点所有，不能在边节点里free;
            return 1;//成功删除一次
        }
        pre = cur;
        cur = cur->next;
    }
    return 0;//未找到
}

GraphAdjList *graph_create() {
    GraphAdjList *g = (GraphAdjList *) malloc(sizeof(*g));//奇妙的写法，长见识了
    if(!g) return NULL;
    g->vertex_count = 0;
    for (int i = 0; i < MAX_GRAPH_SIZE; ++i) g->heads[i] = NULL;//使用i++和++i并没有实质的区别，编码规范推荐++i
    return g;
}

void graph_destroy(GraphAdjList *g) {
    if (!g) return;
    for (int i = 0; i < g->vertex_count; ++i) {
        AdjListNode *head = g->heads[i];
        if (!head) continue;
        //释放头节点后的邻接边节点(不释放其 vertex 指针所指向的对象)
        AdjListNode *e = head->next;
        while (e) {
            AdjListNode *next = e->next;
            free(e);
            e = next;
        }
        //释放头节点所有的vertex和自己
        if (head->vertex) free(head->vertex);
        free(head);
        g->heads[i] = NULL;
    }
    free(g);
}

int graph_add_vertex(GraphAdjList *g,GraphVertex *v) {
    if (!g || !v) return -1;
    if (g->vertex_count >= MAX_GRAPH_SIZE) return -2;
    /* 可选：检查是否重复（基于指针身份） */
    if (find_head_by_vertex_ptr(g, v)) return -3; /* 已存在 */
    AdjListNode *head = (AdjListNode *)malloc(sizeof(*head));
    if (!head) return -4;
    head->vertex = v;
    head->next =NULL;
    g->heads[g->vertex_count++] = head;
    return 0;
}

//无向边：双向插入
int graph_add_edge(GraphAdjList *g,GraphVertex *v1,GraphVertex *v2) {
    if (!g || !v1 || !v2) return -1;
    if (v1 == v2) return -2;//不允许自环
    AdjListNode *head1 = find_head_by_vertex_ptr(g,v1);
    AdjListNode *head2 = find_head_by_vertex_ptr(g,v2);
    if (!head1 || !head2) return -3;
    int r1 = add_edge_oneway(head1,v2);
    if (r1 < 0) return r1;
    int r2 = add_edge_oneway(head2,v1);
    if (r2 < 0) {//回滚已添加的一边，保持一致性
        remove_edge_oneway(head1,v2);
        return r2;
    }
    /* 若两侧均报告0，表示两边都已存在，无变更0，添加成功1 */
    return (r1 > 0 || r2 > 0) ? 1 : 0;
}

int graph_remove_edge(GraphAdjList *g,GraphVertex *v1,GraphVertex *v2) {
    if (!g || !v1 || !v2) return -1;
    AdjListNode *h1 = find_head_by_vertex_ptr(g, v1);
    AdjListNode *h2 = find_head_by_vertex_ptr(g, v2);
    if (!h1 || !h2) return -2;
    int r1 = remove_edge_oneway(h1, v2);//删除成功返回1，否则未找到返回0
    int r2 = remove_edge_oneway(h2, v1);
    return (r1 > 0 || r2 > 0) ? 1 : 0; /* 任意一侧删到就算删除 1 */
}

int graph_remove_vertex(GraphAdjList *g,GraphVertex *v) {
    if (!g || !v) return -1;
    /* 找到头结点及其索引 */
    int idx = -1;
    for (int i = 0; i < g->vertex_count; ++i) {
        if (g->heads[i] && g->heads[i]->vertex == v) {
            idx = i;
            break;
        }
    }
    if (idx < 0) return -2;
    AdjListNode *head = g->heads[idx];

    /* 先从其他顶点的邻接表中移除指向 v 的边（避免使用已释放指针） */
    for (int i = 0; i < g->vertex_count; ++i) {
        if (i == idx) continue;
        AdjListNode *h = g->heads[i];
        if (!h) continue;
        while(remove_edge_oneway(h,v)>0);//循环删干净，返回0即未找到，1是删除一条
    }

    /* 释放该顶点的所有边节点 */
    AdjListNode *edge = head->next;
    while (edge)
    {
        AdjListNode *next = edge->next;
        free(edge);
        edge = next;
    }

    /* 释放顶点与头结点 */
    if (head->vertex) free(head->vertex);
    free(head);

    /* 收缩 heads 数组 */
    for (int i = idx; i < MAX_GRAPH_SIZE - 1; i++) {
        g->heads[i] = g->heads[i+1];
    }
    g->heads[g->vertex_count - 1] = NULL;
    g->vertex_count--;
    return 0;
}

GraphVertex *graph_vertex_create(int id) {
    GraphVertex *v = (GraphVertex *)malloc(sizeof(*v));
    if (!v) return NULL;
    v->id = id;
    return v;
}