#include "graph.h"
#include "nodes.h"

#include <stdio.h>

int main()
{
    pnode p1 = create_node(1);
    pnode p2 = create_node(2);
    pnode p3 = create_node(3);
    add_edge(p1,p2,1);
    add_edge(p1,p3,2);
    p1->next = p2;
    printf("%d\n", p1->next->node_num);
    printf("%d\n",p1->edges->weight);
    printf("%d\n",p1->edges->endpoint->node_num);
    return 0;
}