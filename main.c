/* MAIN:
   In this class we receive the inputs
   -CASE A: create a graph-
           Input format: source node, than pairs of destination node and weight.
           This represents the edges from the source node, to destination nodes, with a given weight.
           End of this source node and a start of new source node represented by the char 'n'.
           We save the nodes of the graph at
           The edges from every node we save at */

#include "graph.h"
#include "nodes.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getNumber(char* str)
{
    return 0;
}

int main()
{
    char* line = (char*)malloc(sizeof(char) * 10000); // line = the input string, allocating memory for it
    if(line == NULL) // check if the allocation was successful
    {
        printf("malloc failed");
        exit(1);
    }

    pnode nodes_list = NULL; //list of nodes
    int* nodes; // array of graph's nodes 
    int node_counter = 0;
    char response = 'Z'; // holds the input char
    char newNode; // if the input will be 'n' -> we work on new node
    int numOfNodes; // will hold the number of the nodes in the graph
    int srcNode, destNode, weight;
    int index = 2; // index of string of specific node input
    
    
    printf("choose action:\n"); /*DELETE LATER*/
    while(response != 'E'){ // while the input char is valid
        scanf("%c",&response); // we receive the char response that will hold which case is it.
        switch (response) { 
            /* case A: Create a new graph */
            case 'A': 
                // getting  the number of nodes;
                scanf("%d", &numOfNodes);
                printf("%d\n", numOfNodes); /*DELETE LATER*/

                // working on nodes:
                printf("write n + src node + dest nodes and weights, when finish this src node press n \n"); /*DELETE LATER*/
                scanf("%s", line); // current src node
                
                while(line[index] != 'n' || index != strlen(line))
                {
                    nodes[node_counter] += (int)line[1]; //source nodes
                    destNode = (int)line[index];
                    weight = (int)line[index+1];
                    index += 2;
                }
                
                
                break;
                // scanf("%s",line); 
                // int firstN = 0;
                // int numOfNodes = 0;
                // char* currString = (char*)malloc(strlen(line));
                // int counter = 0;
                // for(int i = 1; i < strlen(line);i++)
                // {
                //     char curr = *(line+i);
                //     if(firstN == 0)
                //     {
                //         if(curr == 'n')
                //         {
                //             firstN = 1;
                //         }
                //         else
                //         {
                //             numOfNodes *= 10;
                //             numOfNodes += (int) *(line+i)-48;
                //         }
                //     }
                //     else
                //     {
                //         if(curr != 'n')
                //         {
                //             *(currString+counter) = curr;
                //             counter++;
                //         }
                //         else
                //         {
                //             counter = 0;
                //             int srcNode = -1;
                //             int destNode = -1;
                //             int weight = -1;
                //             for(int j =0; j < strlen(currString);j++){
                //                 if(*(currString+j) != ' ')
                //                 {
                //                     if(srcNode == -1)
                //                     {
                //                         srcNode *= 10;
                //                         srcNode += (int)*(currString+j)-48;
                //                     }
                //                     else if(destNode == -1){
                //                         destNode *= 10;
                //                         destNode += (int)*(currString+j)-48;
                //                     }
                //                     else{
                //                         weight *= 10;
                //                         weight += (int)*(currString+j)-48;
                //                     }
                //                 }
                //                 else
                //                 {
                //                     if(destNode == -1)
                //                     {

                //                     }
                //                     else if(destNode != -1 && srcNode != -1 && weight != -1)
                //                     {

                //                     }
                //                     else
                //                     {
                //                         destNode = -1;
                //                     }
                //                 }
                //             }
                //         }
                //     }
                // }

        }
    }
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
