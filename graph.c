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

int getIntFromStringInput() {
    char current;
    char *numStr = (char *) malloc(sizeof(char) * 10);
    int i = 0;
    current = getc(stdin);
    if (current == ' ' || current == '\n') {
        current = getc(stdin);
    }
    // while we didn't receive empty char (space or enter) we add the char (or chars)
    // that we receive from the keyboard
    while (current != ' ' && current != '\n') {
        numStr[i] = current;
        i++;
        current = getc(stdin);
    }
    numStr[i] = '\0'; // end of string
    int finalNum = 0;

    // running on the string we created from the input chars
    // we take the char values from the string and changing it to int values
    // using the ascii value of a char, and add it to the id that is the integer form
    // of the input char
    for (i = 0; i < strlen(numStr); i++) {
        finalNum *= 10;
        finalNum += numStr[i] - 48; // ascii value of '0' is 48
    }
    free(numStr); // free the memory we used

    return finalNum;
}

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

int checkInput(char *toCheck) {
    /*
     * this function gets a string and checks if it's a number or a char
       True = int
       False = char
     */
    if (strlen(toCheck) > 1) // char will be given at length of 1 so more than 1 will be int
    {
        return True; // int 
    }
    if (toCheck[0] < 58 && toCheck[0] > 47) // chars that represent numbers in ascii table
    {
        return True; // int
    }
    return False; // char
}

/* Function to insret a new node to the graph */
char insert_node_cmd(pnode *head, char from) {
    int id = 0;
    char *idString = (char *) malloc(10); // string
    if(idString == NULL)
    {
        exit(1);
    }
    int isExist = 0;


    /* At the next code block we get the id of the source node
       as a string and turn it into a number. */

    char c = getc(stdin); // receiving the id as a char
    //c = getc(stdin);
    int counter = 0;

    // if we don't have head in the list, it means we don't have source node yet.
    // so we receive the id of the source node.
    if (*head == NULL) {
        c = getc(stdin);
    }


    while (c != ' ' && c != '\n') {
        *(idString+counter) = c;
        counter++;
        c = getc(stdin);
    }

    idString[counter] = '\0';


    for (int i = 0; i < strlen(idString); i++) {
        id *= 10;
        id += idString[i] - 48;
    }
    free(idString);



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
//        *head = malloc(sizeof(pnode));
//        printf("malloc\n");
//        if (*head == NULL) {
//            exit(1);
//        }

        // the pointer to the head receives the value of the pointer to the new node (source node)
        *head = new_node_p;
    } else // list isn't empty
    {
        // temporary pointer, saves the head node value while we promote head
        // and going over all the nodes in the list using it
        pnode holder = *head;
        while ((*head)->next != NULL) // while it's not the end of the list
        {
            if ((*head)->node_num == id) {
                (*head)->edges = NULL;
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
    while (1) {
        isExist = False;
        int destNode = 0;
        int weight = 0;
        char *toCheck = (char *) malloc(10);
        if (toCheck == NULL) {
            exit(1);
        }
        int result;

        // This is the only place where we may get a char and not a number.
        // We check it, so if we get a char we will go back to the previous functions.
        char current = getc(stdin);
        counter = 0;

        //  while we didn't receive empty char (space or enter)
        while (current != ' ' && current != '\n') {
            *(toCheck+counter) = current;
            current = getc(stdin);
            counter++;
        }

        toCheck[counter] = '\0'; // end of string
        result = checkInput(toCheck); // checking if it's a char or a number
        if (result == True) // number
        {
            int num = 0;
            for (int i = 0; i < strlen(toCheck); i++) {
                num *= 10;
                num += toCheck[i] - 48; // 48 is the ascii value of the char '0'
            }
            free(toCheck); // we done with this string so we free the memory it used
            destNode = num; // destination node
        } else // go back if char
        {
            current = toCheck[0];
            free(toCheck);

            return current;
        }

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
            pnode new_node_p = malloc(sizeof(node));
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
        counter = 0;
        current = getc(stdin);
        char *weightString = (char *) malloc(10);
        // while we didn't receive empty char (space or enter)
        while (current != ' ' && current != '\n') {
            *(weightString+counter) = current;
            counter++;
            current = getc(stdin);
        }
        weightString[counter] = '\0'; // end of string
        for (int i = 0; i < strlen(weightString); i++) {
            weight *= 10;
            weight += weightString[i] - 48; // 48 is the ascii value of the char '0'
        }
        free(weightString);
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
}


/* At this function we create the graph */
char build_graph_cmd(pnode *head) {
    /* getting  the number of nodes */
    char c;
    c = getc(stdin);
    c = 'a';
    char *numString = (char *) malloc(10);
    if (numString == NULL) {
        exit(1);
    }

    int counter = 0;
    c = getc(stdin);

    // while we didn't receive empty char (space or enter)
    while (c != ' ' && c != '\n') {
        numString[counter] = c;
        counter++;
        c = getc(stdin);
    }
    numString[counter] = '\0'; // end of string
    for (int i = 0; i < strlen(numString); i++) {
        numOfNodes *= 10;
        numOfNodes += numString[i] - 48; // 48 is the ascii value of the char '0'
    }
    free(numString);
    // Here we go over the input and create what is needed until we get nothing.
    int n_counter = 0; // counts the number of the char 'n' we received
    counter = 0;
    c = getc(stdin);
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
    int node_to_del = getIntFromStringInput();

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



    char next = getc(stdin);
    return next;

}

int min_distance(int distance[], bool shortest_paths[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numOfNodes; v++)
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
        int u = min_distance(distance, shortest_path);
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
    int firstNum = getIntFromStringInput();
    int secondNum = getIntFromStringInput();

    int dist = dijkstra(head, firstNum, secondNum);
    if (dist != INT_MAX) {
        printf("Dijsktra shortest path: %d \n", dist);
    } else {
        printf("-1");
    }
    char next = getc(stdin);
    return next;
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
    int numTSP = getIntFromStringInput();
    int nodeIDS[numTSP];
    int counter = 0;
    for (int i = 0; i < numTSP; i++) {
        int curr = getIntFromStringInput();
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
    char next = getc(stdin);
    return next;
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
