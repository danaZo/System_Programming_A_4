/* CLASS GRAPH:
   In this class we create a graph, using linked list that holds the nodes of the graph.
   Each node holds the information about the edges that goes from the node.*/

#include "graph.h"
#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkInput(char *toCheck) {
    /*
     * this function get a string and checks if it is a number or a char
     */
    if (strlen(toCheck) > 1) {
        return 1;
    }
    if (toCheck[0] < 58 && toCheck[0] > 47) {
        return 1;
    }
    return 0;
}

char insert_node_cmd(pnode *head) {
    int id = 0;
    char *idString = (char *) malloc(10);
    int isExist = 0;

    // in the next code block we get our id of the source node
    // as a string and turn it to a number
    char c = getc(stdin);
    int counter = 0;
    if (*head == NULL) {
        c = getc(stdin);
    }
    while (c != ' ' && c != '\n') {
        idString[counter] = c;
        counter++;
        c = getc(stdin);
    }
    idString[counter] = '\0';
    for (int i = 0; i < strlen(idString); i++) {
        id *= 10;
        id += idString[i] - 48;
    }
    free(idString);

    //in this code block we check if the node with the id we got
    //already exists and if not we create one with this id and insert him to the list
    pnode new_node_p;
    if (*head == NULL) {
        new_node_p = malloc(sizeof(node));
        if (new_node_p == NULL) {
            exit(1);
        }
        new_node_p->next = NULL;
        new_node_p->edges = NULL;
        new_node_p->node_num = id;
        *head = malloc(sizeof(pnode));
        if (*head == NULL) {
            exit(1);
        }
        *head = new_node_p;
    } else {
        pnode holder = *head;
        while ((*head)->next != NULL) {
            if ((*head)->node_num == id) {//here we check if the node exists already
                isExist = 1;
            }
            (*head) = (*head)->next;
        }
        if ((*head)->node_num == id) {
            isExist = 1;
        }
        if (!isExist) {
            new_node_p = malloc(sizeof(node));
            if (new_node_p == NULL) {
                exit(1);
            }
            new_node_p->next = NULL;
            new_node_p->edges = NULL;
            new_node_p->node_num = id;
            (*head)->next = new_node_p;
        }
        *head = holder;
    }

    /*
     * in this loop we will run while we get more numbers until a char is hit
     * here we create any new node we need and add edges that we get
     */
    while (1) {
        isExist = 0;
        int destNode = 0;
        int weight = 0;
        char *toCheck = (char *) malloc(10);
        if(toCheck == NULL)
        {
            exit(1);
        }
        int result;

        //this is the only place where we may get a char and not a number
        // we check it so if we get a char we will go back to the previous functions
        char current = getc(stdin);
        counter = 0;
        while (current != ' ' && current != '\n') {
            toCheck[counter] = current;
            current = getc(stdin);
            counter++;
        }
        toCheck[counter] = '\0';
        result = checkInput(toCheck);
        if (result == 1) {
            int num = 0;
            for (int i = 0; i < strlen(toCheck); i++) {
                num *= 10;
                num += toCheck[i] - 48;
            }
            free(toCheck);
            destNode = num;
        }
        else { // go back if char
            current = toCheck[0];
            free(toCheck);
            return current;
        }

        // go over the current list we have, if the node doesn't exist there already
        // we will create a new one and will add him
        pnode holder = *head;
        while ((*head)->next != NULL) {
            if ((*head)->node_num == destNode) {
                isExist = 1;
            }
            (*head) = (*head)->next;
        }
        if ((*head)->node_num == destNode) {
            isExist = 1;
        }
        if (!isExist) {
            new_node_p = malloc(sizeof(node));
            if (new_node_p == NULL) {
                exit(1);
            }
            new_node_p->next = NULL;
            new_node_p->edges = NULL;
            new_node_p->node_num = destNode;
            (*head)->next = new_node_p;
        }
        *head = holder;

        //in this block we will get the weight of the edge, find the 2 nodes and create the edge
        counter = 0;
        current = getc(stdin);
        char *weightString = (char *) malloc(10);
        while (current != ' ' && current != '\n') {
            weightString[counter] = current;
            counter++;
            current = getc(stdin);
        }
        weightString[counter] = '\0';
        for (int i = 0; i < strlen(weightString); i++) {
            weight *= 10;
            weight += weightString[i] - 48;
        }
        pnode src;
        pnode dest;
        pnode temp = *head;
        while ((*head) != NULL) {
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

char build_graph_cmd(pnode *head) {
    int numOfNodes = 0;// will hold the number of the nodes in the graph

    /* getting  the number of nodes */
    char c = 'a';
    c = getc(stdin);
    c = 'a';
    char *numString = (char *) malloc(10);
    if (numString == NULL) {
        exit(1);
    } else {
    }
    int counter = 0;
    c = getc(stdin);
    while (c != ' ' && c != '\n') {
        numString[counter] = c;
        counter++;
        c = getc(stdin);
    }
    numString[counter] = '\0';
    for (int i = 0; i < strlen(numString); i++) {
        numOfNodes *= 10;
        numOfNodes += numString[i] - 48;
    }

    //here we go over the input and create what is needed until we get nothing
    int n_counter = 0;
    counter = 0;
    c = getc(stdin);
    while (n_counter != numOfNodes) {
        if (c == 'n') {
            n_counter++;
            c = insert_node_cmd(head);
        } else {
            return c;
        }
    }
    return c;
}


