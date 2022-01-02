#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

char build_graph_cmd(pnode* head);
char insert_node_cmd(pnode* head, char from);
char delete_node_cmd(pnode* head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
char shortsPath_cmd(pnode head);
char TSP_cmd(pnode head);
int dijkstra(pnode head, int src, int dest);
int ShortestArray(pnode head, int *arr, int len);

#endif
