/* CLASS NODE: */

#include "graph.h"
#include "nodes.h"

#include <stdlib.h>
#include <stdio.h>

pnode create_node(int id)
{
    //create new node, and allocate memory for the pointer of the node
    node node1 = {id,NULL,NULL};
    pnode pn = malloc(sizeof (node));
    if(!pn)// check if the allocation was successful
    {
        printf("malloc failed\n");
        exit(1);
    }
    *pn = node1;// set the pointer to the address of the node and return it
    return pn;
}

void add_edge(node *this, node *other, int weight)
{
    pedge head = this->edges;// save the edges so we don't lose them
    while(this->edges != NULL && this->edges->next != NULL)// go over all the edge if not null, and get to the last one
    {
        this->edges = this->edges->next;
    }
    // create new edge and allocate memory to its pointer
    edge e = {weight, other, NULL};
    pedge pe = malloc(sizeof(edge));
    if(!pe)// check if the allocation was successful
    {
        printf("malloc failed\n");
        exit(1);
    }
    //change the pointer to the address of the edge
    *pe = e;
    if(this->edges == NULL)// if the list is empty, the head will be the new pointer
    {
        this->edges = pe;
        return;
    }
    //else, set the pointer as the next one, and return the head
    this->edges->next = pe;
    this->edges = head;
}