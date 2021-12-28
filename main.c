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
    pnode* head = malloc(sizeof (pnode));// list of nodes in a graph
     if(head == NULL)
     {
         exit(1);
     }
     char response = 'y';// holds the input char

    response = getc(stdin);
    while(response != 'E'){        // while the input char is valid
         // we receive the char response that will hold which case it is.
         switch (response) {
             /* case A: Create a new graph */
             case 'A':
                 response = build_graph_cmd(head);
                 break;
             case 'B':
                 break;
             case 'D':
                 break;
             case 'S':
                 break;
             case 'T':
                 printf("got here");
                 exit(1);
                 //break;
             default:
                 break;
         }
     }

//    insert_node_cmd(head,1);
//    insert_node_cmd(head,2);
//    insert_node_cmd(head,3);
//    pnode p1 = *head;
//    pnode p2 = (*head)->next;
//    pnode p3 = (*head)->next->next;
//    add_edge(p1,p2,1);
//    add_edge(p1,p3,2);
//    add_edge(p2,p3,2);
    return 0;
}
