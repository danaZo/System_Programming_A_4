/* CLASS GRAPH:
   In this class we create a graph, using linked list that holds the nodes of the graph.
   Each node holds the information about the edges that goes from the node and the next node.*/

#include "graph.h"
#include "nodes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define True 1
#define False 0

int numOfNodes = 0; // will hold the number of the nodes in the graph

void printGraph_cmd(pnode head) {
    printf("\ncurrent state:\n");
    pnode holder = head;
    while (holder != NULL) {
        printf("%d", holder->node_num);
        pedge p_edges = holder->edges;
        while (p_edges != NULL) {
            printf("->%d(%d)", p_edges->endpoint->node_num, p_edges->weight);
            p_edges = p_edges->next;
        }
        printf("\n");
        holder = holder->next;
    }
}

/* Function to insret a new node to the graph */
char insert_node_cmd(pnode *head, char from) {
    int id = 0;
    char c = getc(stdin);
    int isExist = 0;
    scanf("%d",&id);
    /* At this code block we check if the node with the id we got
       already exists in the nodes list of this graph.
       If not -> we create one with this id and insert it to the list. */

    if (*head == NULL) // there is no head -> list is empty
    {
        pnode new_node_p = (pnode)malloc(sizeof(node)); // new nodes list
        if (new_node_p == NULL) {
            exit(1);
        }

        new_node_p->next = NULL;
        new_node_p->edges = NULL;
        new_node_p->node_num = id;

        // allocating memory to the pointer of head pointer that points at the head node
        // the pointer to the head receives the value of the pointer to the new node (source node)
        *head = new_node_p;
    }
    else // list isn't empty
    {
        // temporary pointer, saves the head node value while we promote head
        // and going over all the nodes in the list using it
        pnode holder = *head;
        while ((*head)->next != NULL) // while it's not the end of the list
        {
            if ((*head)->node_num == id) {
                while((*head)->edges != NULL)
                {
                    removeEdge(*head,(*head)->edges->endpoint->node_num);
                }
                isExist = True; // check if the node already exists 
            }
            (*head) = (*head)->next;
        }
        if ((*head)->node_num == id) // checking the last node
        {
            (*head)->edges = NULL;
            isExist = True;
        }
        if (!isExist) // not exist
        {
            // creating new node

            pnode new_node_p = (pnode)malloc(sizeof(node));
            if (new_node_p == NULL) {
                exit(1);
            }

            new_node_p->next = NULL;
            new_node_p->edges = NULL;
            new_node_p->node_num = id;
            if (from == 'B') {
                numOfNodes++;
            }
            (*head)->next = new_node_p;
        }
        *head = holder; // turning the head value to be the value we stored in holder
    }

    /*
     * At this loop we will run while we get more numbers until a char is hitted.
     * Here we create any new node we need and add edges that we receive.
     */
    int destNode = 0;
    int weight = 0;
    while (scanf("%d %d", &destNode, &weight)) {
        isExist = False;
        // Go over the current list we have, if the node doesn't exist there,
        // we will create a new one and will add it.
        pnode holder = *head;
        while ((*head)->next != NULL) {
            if ((*head)->node_num == destNode) {
                isExist = True;
            }
            (*head) = (*head)->next;
        }
        if ((*head)->node_num == destNode) {
            isExist = True;
        }
        if (!isExist) // we don't have this node, so we create new node 
        {
            pnode new_node_p = (pnode)malloc(sizeof(node));
            if (new_node_p == NULL) {
                exit(1);
            }
            new_node_p->next = NULL;
            new_node_p->edges = NULL;
            new_node_p->node_num = destNode;
            if (from == 'B') {
                numOfNodes++;
            }
            (*head)->next = new_node_p;
        }
        *head = holder;

        // At this block we will get the weight of the edge, find the 2 nodes of the edge and create the edge.
        pnode src;
        pnode dest;
        pnode temp = *head;

        // running over the nodes of the graph and checking if it's the source node
        // of the edge or the destination node.
        while ((*head) != NULL) // while it's not the end of the list
        {
            if ((*head)->node_num == id) {
                src = *head;
            }
            if ((*head)->node_num == destNode) {
                dest = *head;
            }
            (*head) = (*head)->next;
        }
        add_edge(src, dest, weight);
        *head = temp;
    }
    scanf("%c",&c);
    return c;
}


/* At this function we create the graph */
char build_graph_cmd(pnode *head) {
    /* getting  the number of nodes */
    char c;
    c = getc(stdin);
    c = 'a';
    scanf("%d",&numOfNodes);
    // Here we go over the input and create what is needed until we get nothing.
    int n_counter = 0; // counts the number of the char 'n' we received
    c = getc(stdin);
    if(c == ' ')
    {
        c = getc(stdin);
    }
    // if the number of 'n' is the same as the number of the nodes, it means we finished 
    // working on all the source nodes.
    while (n_counter != numOfNodes) {
        if (c == 'n') {
            n_counter++;
            c = insert_node_cmd(head, 'A');
        } else {
            return c;
        }
    }
    return c;
}


/* At this function we delete a node and all the edges that connected to it */
char delete_node_cmd(pnode *head) {
    char c = getc(stdin);
    int node_to_del = 0;
    scanf("%d",&node_to_del);
    pnode temp = *head;
    pnode toDelete = getNode(*head, node_to_del);

    // STEPS:
    // First, we need to check if there are edges that goes to the node to delete.
    // note: we need to free space of every edge we delete.
    // Second, we need to delete the edges from the node itself.
    // Third, we need to delete the node itself. free the space of the node.
    while (temp != NULL) {
        if (temp->next != NULL && temp->next->node_num == node_to_del) {
            temp->next = temp->next->next;
        }
        removeEdge(temp, node_to_del);
        temp = temp->next;
    }
    while (toDelete->edges != NULL) {
        pedge currEdge = toDelete->edges;
        toDelete->edges = currEdge->next;
        free(currEdge);

    }
    free(toDelete);



    c = getc(stdin);
    if(c == ' ')
    {
        c = getc(stdin);
    }

    return c;

}

int min_distance(pnode head,const int* distance,const bool* shortest_paths) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < findMaxID(head) + 1; v++)
        if (shortest_paths[v] == false && distance[v] <= min)
            min = distance[v], min_index = v;
    if (min == INT_MAX) {
        return -1;
    }
    return min_index;
}


int dijkstra(pnode head, int src, int dest) {
    int distance[findMaxID(head) + 1]; //distance[i] will hold the shortest distance from src to i

    bool shortest_path[findMaxID(head) + 1]; // shortestpath[i] will be true if vertex i is included in shortest
    // path or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and shortest_path[] as false
    for (int i = 0; i < findMaxID(head) + 1; i++)
        distance[i] = INT_MAX, shortest_path[i] = false;

    // Distance of source vertex from itself is always 0
    distance[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < findMaxID(head); count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = min_distance(head, distance, shortest_path);
        if (u == -1) {
            break;
        }
        // Mark the picked vertex as processed
        shortest_path[u] = true;
        pnode source = getNode(head, u);
        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < findMaxID(head) + 1; v++) {
            pedge currEdge = getEdge(source, v);

            // Update distance[v] only if is not in shortest_path, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of distance[v]
            if (!shortest_path[v] && currEdge != NULL && distance[u] + currEdge->weight < distance[v]) {
                distance[v] = distance[u] + currEdge->weight;
            }
        }

    }

    return distance[dest];
}

/* finds the shortest path between two nodes using dijkstra algorithm */
char shortsPath_cmd(pnode head) {
    // we receive two input numbers : a source node, and a destination node
    char c = getc(stdin);
    int firstNum = 0;
    int secondNum = 0;
    scanf("%d %d",&firstNum, &secondNum);

    int dist = dijkstra(head, firstNum, secondNum);
    if (dist != INT_MAX) {
        printf("Dijsktra shortest path: %d \n", dist);
    } else {
        printf("-1");
    }
    c = getc(stdin);
    if(c == ' ')
    {
        c = getc(stdin);
    }
    return c;
}

/*In this function we need to find the shortest path between k nodes
  we will do all the possible permutations on the given nodes and return the 
  permutation that gives us the shortest path.*/
char TSP_cmd(pnode head) {
    // The size of the array "isIn" is the size of the biggest id number of the nodes in the graph.
    // First, all the indexes in the array "isIn" are 0.
    // Afterwards, we update the value at the index number of the given id to be 1.
    // The array "nodeIDS" holds the id numbers we receive.

    int isIn[findMaxID(head) + 1];
    for (int i = 0; i < findMaxID(head) + 1; i++) {
        isIn[i] = 0;
    }
    char c = getc(stdin);
    int numTSP = 1;
    scanf("%d",&numTSP);
    int nodeIDS[numTSP];
    for(int i =0; i < numTSP;i++)
    {
        nodeIDS[i] = 0;
    }
    int counter = 0;
    for (int i = 0; i < numTSP; i++) {
        int curr = 0;
        scanf("%d",&curr);
        isIn[curr] = 1;
    }

    // here we save all the nodes we need to run the TSP on
    for (int i = 0; i < findMaxID(head) + 1; i++) {
        if (isIn[i] == 1) {
            nodeIDS[counter] = i;
            counter++;
        }
        if (counter == numTSP) {
            break;
        }
    }
    getAllPermutations(head, nodeIDS, numTSP);
    c = getc(stdin);
    if(c == ' ')
    {
        c = getc(stdin);
    }
    return c;
}

// returns array with the shortest paths between twp adjancent nodes in the nodes array
int ShortestArray(pnode head, int *arr, int len) {
    int dist = 0;
    int curr = 0;
    for (int i = 0; i < len - 1; i++) {
        curr = dijkstra(head, arr[i], arr[i + 1]);
        if (curr == INT_MAX) {
            return -1;
        }
        dist += curr;
    }
    return dist;
}

void deleteNode(pnode head, int id) {
    int node_to_del = id;
    pnode temp = head;
    pnode toDelete = getNode(head, node_to_del);

    // STEPS:
    // First, we need to check if there are edges that goes to the node to delete.
    // note: we need to free space of every edge we delete.
    // Second, we need to delete the edges from the node itself.
    // Third, we need to delete the node itself. free the space of the node.
    while (temp != NULL) {
        if (temp->next != NULL && temp->next->node_num == node_to_del) {
            temp->next = temp->next->next;
        }
        removeEdge(temp, node_to_del);
        temp = temp->next;
    }
    while (toDelete->edges != NULL) {
        pedge currEdge = toDelete->edges;
        toDelete->edges = currEdge->next;
        free(currEdge);

    }
    free(toDelete);
}

void deleteGraph_cmd(pnode *head) {

    pnode temp = *head;
    if (*head == NULL) {
        return;
    }
    while (temp->next != NULL) {
        deleteNode(temp, temp->next->node_num);
    }
    while(temp->edges != NULL){
        pedge next = temp->edges->next;
        removeEdge(temp,temp->edges->endpoint->node_num);
        temp->edges = next;
    }
    *head = NULL;
    free(temp);
    free(head);
}
