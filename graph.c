/* CLASS GRAPH:
   In this class we create a graph, using linked list that holds the nodes of the graph.
   Each node holds the information about the edges that goes from the node and the next node.*/

#include "graph.h"
#include "nodes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0

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
char insert_node_cmd(pnode *head) 
{
    int id = 0;
    char *idString = (char *) malloc(10); // string
    int isExist = 0;


    /* At the next code block we get the id of the source node
       as a string and turn it into a number. */

    char c = getc(stdin); // receiving the id as a char
    int counter = 0;
    
    // if we don't have head in the list, it means we don't have source node yet.
    // so we receive the id of the source node.
    if (*head == NULL)
    {
        c = getc(stdin);
    }

    // while we didn't receive empty char (space or enter) we add the char (or chars) 
    // that we receive from the keyboard
    while (c != ' ' && c != '\n')
    {
        idString[counter] = c;
        counter++;
        c = getc(stdin);
    }

    idString[counter] = '\0'; // end of the string

    // running on the string we created from the input chars
    // we take the char values from the string and changing it to int values
    // using the ascii value of a char, and add it to the id that is the integer form 
    // of the input char
    for (int i = 0; i < strlen(idString); i++) 
    {
        id *= 10;
        id += idString[i] - 48; // 48 is the ascii value of the char '0'
    }
    free(idString); // we finished using this string so we need to free the memory it used


    /* At this code block we check if the node with the id we got
       already exists in the nodes list of this graph.
       If not -> we create one with this id and insert it to the list. */

    pnode new_node_p;
    if (*head == NULL) // there is no head -> list is empty
    {
        new_node_p = malloc(sizeof(node)); // new nodes list
        if (new_node_p == NULL) 
        {
            exit(1);
        }

        new_node_p->next = NULL; 
        new_node_p->edges = NULL;
        new_node_p->node_num = id;

        // allocating memory to the pointer of head pointer that points at the head node
        *head = malloc(sizeof(pnode)); 
        if (*head == NULL) 
        {
            exit(1);
        }

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
            if ((*head)->node_num == id) 
            {
                isExist = True; // check if the node already exists 
            }
            (*head) = (*head)->next;
        }
        if ((*head)->node_num == id) // checking the last node
        {
            isExist = True;
        }
        if (!isExist) // not exist
        {
            // creating new node
            new_node_p = malloc(sizeof(node)); 
            if (new_node_p == NULL) 
            {
                exit(1);
            }

            new_node_p->next = NULL;
            new_node_p->edges = NULL;
            new_node_p->node_num = id;
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
        if(toCheck == NULL)
        {
            exit(1);
        }
        int result;

        // This is the only place where we may get a char and not a number.
        // We check it, so if we get a char we will go back to the previous functions.
        char current = getc(stdin);
        counter = 0;

        //  while we didn't receive empty char (space or enter)
        while (current != ' ' && current != '\n') 
        {
            toCheck[counter] = current;
            current = getc(stdin);
            counter++;
        }

        toCheck[counter] = '\0'; // end of string
        result = checkInput(toCheck); // checking if it's a char or a number
        if (result == True) // number
        {
            int num = 0;
            for (int i = 0; i < strlen(toCheck); i++) 
            {
                num *= 10;
                num += toCheck[i] - 48; // 48 is the ascii value of the char '0'
            }

            free(toCheck); // we done with this string so we free the memory it used
            destNode = num; // destination node
        }
        else // go back if char
        { 
            current = toCheck[0];
            free(toCheck);
            return current;
        }

        // Go over the current list we have, if the node doesn't exist there,
        // we will create a new one and will add it.
        pnode holder = *head;
        while ((*head)->next != NULL) 
        {
            if ((*head)->node_num == destNode) 
            {
                isExist = True;
            }
            (*head) = (*head)->next;
        }
        if ((*head)->node_num == destNode) 
        {
            isExist = True;
        }
        if (!isExist) // we don't have this node, so we create new node 
        {
            new_node_p = malloc(sizeof(node));
            if (new_node_p == NULL) 
            {
                exit(1);
            }
            new_node_p->next = NULL;
            new_node_p->edges = NULL;
            new_node_p->node_num = destNode;
            (*head)->next = new_node_p;
        }
        *head = holder;

        // At this block we will get the weight of the edge, find the 2 nodes of the edge and create the edge.
        counter = 0;
        current = getc(stdin);
        char *weightString = (char *) malloc(10);

        // while we didn't receive empty char (space or enter)
        while (current != ' ' && current != '\n') 
        {
            weightString[counter] = current;
            counter++;
            current = getc(stdin);
        }
        weightString[counter] = '\0'; // end of string
        for (int i = 0; i < strlen(weightString); i++) 
        {
            weight *= 10;
            weight += weightString[i] - 48; // 48 is the ascii value of the char '0'
        }
        pnode src;
        pnode dest;
        pnode temp = *head;

        // running over the nodes of the graph and checking if it's the source node
        // of the edge or the destination node.
        while ((*head) != NULL) // while it's not the end of the list
        {
            if ((*head)->node_num == id) 
            {
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
char build_graph_cmd(pnode *head) 
{
    int numOfNodes = 0; // will hold the number of the nodes in the graph

    /* getting  the number of nodes */
    char c;
    c = getc(stdin);
    c = 'a';
    char *numString = (char *) malloc(10);
    if (numString == NULL) 
    {
        exit(1);
    } 

    int counter = 0;
    c = getc(stdin);

    // while we didn't receive empty char (space or enter)
    while (c != ' ' && c != '\n') 
    {
        numString[counter] = c;
        counter++;
        c = getc(stdin);
    }
    numString[counter] = '\0'; // end of string
    for (int i = 0; i < strlen(numString); i++) 
    {
        numOfNodes *= 10;
        numOfNodes += numString[i] - 48; // 48 is the ascii value of the char '0'
    }

    // Here we go over the input and create what is needed until we get nothing.
    int n_counter = 0; // counts the number of the char 'n' we received
    counter = 0;
    c = getc(stdin);
    // if the number of 'n' is the same as the number of the nodes, it means we finished 
    // working on all the source nodes.
    while (n_counter != numOfNodes) 
    {
        if (c == 'n') 
        {
            n_counter++;
            c = insert_node_cmd(head);
        } 
        else 
        {
            return c;
        }
    }
    return c;
}

/* At this function we delete a node and all the edges that connected to it */
void delete_node_cmd(pnode* head)
{
   int node_to_del = (*head)->node_num;
   int isExist;
   char *idString = (char *) malloc(10); // string

   char c = getc(stdin); // receiving the id as a char
   int counter = 0;
    
    if (*head == NULL)
    {
        c = getc(stdin);
    }

    // while we didn't receive empty char (space or enter) we add the char (or chars) 
    // that we receive from the keyboard
    while (c != ' ' && c != '\n')
    {
        idString[counter] = c;
        counter++;
        c = getc(stdin);
    }

    idString[counter] = '\0'; // end of the string

    for (int i = 0; i < strlen(idString); i++) 
    {
        node_to_del *= 10;
        node_to_del += idString[i] - 48; // 48 is the ascii value of the char '0'
    }
    free(idString); // we finished using this string so we need to free the memory it used


    if (*head == NULL) // there is no head -> list is empty
    {
        return;
    }

    else // list isn't empty
    {
        // temporary pointer, saves the head node value while we promote head
        // and going over all the nodes in the list using it
        pnode holder = *head; 
        while ((*head)->next != NULL) // while it's not the end of the list
        {
            if ((*head)->node_num == node_to_del) 
            {
                isExist = True; // check if the node already exists 
            }
            (*head) = (*head)->next;
        }
        if ((*head)->node_num == node_to_del) // checking the last node
        {
            isExist = True;
        }
        if (isExist) // exist
        {
            // deleting the node
            
        }
        *head = holder; // turning the head value to be the value we stored in holder
    }

}

