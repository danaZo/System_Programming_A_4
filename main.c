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


int main() {
    pnode* head = (pnode *) malloc(sizeof(pnode));// list of nodes in a graph
    if (head == NULL) {
        exit(1);
    }
    *head = NULL;
    char response = 'y';// holds the input char

    scanf("%c",&response);
    while (1) {        // while the input char is valid
        // we receive the char response that will hold which case it is.
        switch (response) {
            /* case A: Create a new graph */
            case 'A':
                response = build_graph_cmd(head);
                break;
                /* case B: create new node */
            case 'B':
                response = insert_node_cmd(head, 'B');
                break;
                /* case D: delete node */
            case 'D':
                response = delete_node_cmd(head);
                break;
                /* case S: finds the shortest path between 2 nodes */
            case 'S':
                response = shortsPath_cmd(*head);
                break;
            case 'T':
                response = TSP_cmd(*head);
                break;
            case EOF:
                deleteGraph_cmd(head);
                return 0;
            case '\n':
                deleteGraph_cmd(head);
                return 0;
            default:
                break;
        }
    }
}