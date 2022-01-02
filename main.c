/* MAIN:
   In this class we receive the inputs
   -CASE A: create a graph-
           Input format: source node, than pairs of destination node and weight.
           This represents the edges from the source node, to destination nodes, with a given weight.
           End of this source node and a start of a new source node represented by the char 'n'.
           We save the nodes of the graph at... , and the edges from every node we save at... 
           
   -CASE B: create a new node-
            The first input number after 'B' will be the id of the new node we will create.
            The next input number is the destination node of the edge from this node.
            The next input number is the weight of the edge.
            If there are more input number they come as pairs of dstination node and weight of edge.  

    -CASE D: delete a node-
            The number after 'D' is the id of the node we need to delete.      
           */
       
           
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
    int counter = 0;
    while(response != 'E'){        // while the input char is valid
         // we receive the char response that will hold which case it is.
         switch (response) {
             /* case A: Create a new graph */
             case 'A':
                response = build_graph_cmd(head);
                printGraph_cmd(*head);
                break;
             /* case B: create new node */    
             case 'B':
                insert_node_cmd(head);
                counter++;
                 printGraph_cmd(*head);
                break;
             /* case D: delete node */   
             case 'D':
                delete_node_cmd(head);
                 printGraph_cmd(*head);
                 break;
             /* case S: finds the shortest path between 2 nodes */    
             case 'S':
                 break;
             case 'T':
                 printf("got here T");
                 //exit(1);
                 break;
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
