/* CLASS GRAPH:
   In this class we create a graph, using linked list that holds the nodes of the graph.
   Each node holds the information about the edges that goes from the node.*/

#include "graph.h"
#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>

void insert_node_cmd(pnode *head)
{
   int id;
   printf("enter id of key: ");
   scanf("%d",&id);
   pnode np = create_node(id);
   if(head == NULL){
      *head = np;
   } 
   else{
      pnode* holder = head;
      while(&(*holder)->next != NULL){
         (*holder) = &(*holder)->next;
      }
      
   }
}

void build_graph_cmd(pnode *head)
{
   int numOfNodes;                // will hold the number of the nodes in the graph
   int srcNode, destNode, weight;

   /* getting  the number of nodes */
   scanf("%d", &numOfNodes);
   printf("%d\n", numOfNodes); /*DELETE LATER*/

   int n_counter = 0;
   int counter =0;
   int isFirst =1;


   while(n_counter != numOfNodes)
   {
      int currentNum = 0;
      while(scanf("%d"),&currentNum){
         if(isFirst){
            pnode np = create_node(currentNum);
            isFirst = 0;
            *head = np;
         }
         else{
            if(counter%2 == 0){
               destNode = currentNum;
               counter++;
            }
            else{

            }
         }
      }
   }
}


