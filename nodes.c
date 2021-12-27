/* CLASS NODE: */

#include "graph.h"
#include "nodes.h"

#include <stdlib.h>
#include <stdio.h>

pnode create_node(int id)
{
    //struct GRAPH_NODE_ node = {id, NULL, NULL};
    pnode pn = {id, NULL, NULL};
    return pn;
}