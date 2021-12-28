/* MAIN:
   In this class we receive the inputs
   -CASE A: create a graph-
           Input format: source node, than pairs of destination node and weight.
           This represents the edges from the source node, to destination nodes, with a given weight.
           End of this source node and a start of a new source node represented by the char 'n'.
           We save the nodes of the graph at... , and the edges from every node we save at... */

           
/* included libraries we created */
#include "graph.h"
#include "nodes.h"

/* included built-in libraries */ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
    // pnode nodes_list = NULL;       // list of nodes in a graph 
    // char response;                 // holds the input char
    // int index = 2;                 // index of string of specific node input
    
    // printf("choose action:\n"); /*DELETE LATER*/

    // while(response != 'E'){        // while the input char is valid
    //     scanf("%c",&response);     // we receive the char response that will hold which case it is.
    //     switch (response) { 
    //         /* case A: Create a new graph */
    //         case 'A': 
    //             build_graph_cmd(&nodes_list);
    //             break;
    //         case 'B':
    //             break;
    //         case 'D':
    //             break;
    //         case 'S':
    //             break;
    //         case 'T':
    //             break;    
    //     }
    // }
    pnode* node_list = NULL;
    insert_node_cmd(node_list); 
    insert_node_cmd(node_list); 
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
