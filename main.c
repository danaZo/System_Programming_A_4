#include "graph.h"
#include "nodes.h"

#include <stdio.h>

int main()
{
    pnode p = create_node(1);
    printf("%d", p->node_num);
    return 0;
}