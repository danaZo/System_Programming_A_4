/* CLASS NODE: */

#include "graph.h"
#include "nodes.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


void add_edge(node *this, node *other, int weight)
{
    pedge head = this->edges; // save the edges so we don't lose it

    // go over all the edge and get to the last one
    while(this->edges != NULL && this->edges->next != NULL)
    {
        this->edges = this->edges->next;
    }
    // create new edge and allocate memory to it's pointer
    pedge pe = malloc(sizeof(edge));
    if(!pe) // check if the allocation was successful
    {
        printf("malloc failed\n");
        exit(1);
    }
    // change the pointer to the address of the edge
    pe->next = NULL;
    pe->weight = weight;
    pe->endpoint = other;
    if(this->edges == NULL)// if the list is empty, the head will be the new pointer
    {
        this->edges = pe;
        return;
    }
    //else, set the pointer as the next one, and return the head
    this->edges->next = pe;
    this->edges = head;
}

pedge getEdge(pnode src, int dest){
    pedge edges = src->edges;
    while(edges != NULL)
    {
        if(edges->endpoint->node_num == dest)
        {
            return edges;
        }
        edges = edges->next;
    }
    return NULL;
}

pnode getNode(pnode head, int id)
{
    pnode temp = head;
    while(temp != NULL)
    {
        if(temp->node_num == id)
        {
            return  temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void removeEdge(pnode src, int dest)
{
    pedge toRemove = getEdge(src,dest);
    if(toRemove != NULL)
    {
        pedge edges = src->edges;
        if(src->edges->endpoint->node_num == dest)
        {
            src->edges = toRemove->next;
            free(toRemove);
            return;
        }
        while(edges->next->endpoint->node_num != dest)
        {
            edges = edges->next;
        }
        edges->next = toRemove->next;
        free(toRemove);
    }
}

int findMaxID(pnode head)
{
    int id = -1;
    pnode temp = head;
    while(temp != NULL)
    {
        if(temp->node_num > id)
        {
            id = temp->node_num;
        }
        temp = temp->next;
    }
    return  id;
}

int factorial(int num)
{
    if(num == 1 || num == 0)
    {
        return 1;
    }
    return num*factorial(num-1);
}

// doing all the possible permutations 
int getAllPermutations(pnode head, int nodes[], int len, int start)
{
    int permutation[len];
    int best = INT_MAX;
    int results[factorial(len)];
    for(int i =0; i < factorial(len);i++)
    {
        results[i] = INT_MAX;
    }
    switch(len){
        case 2:
            for(int i =0; i < len;i++)
            {
                permutation[i] = nodes[i];
                for(int j = 0; j < len; j++)
                {
                    if(j != i)
                    {
                        permutation[j] = nodes[j];
                        int result = ShortestArray(head, permutation,len);
                        if(result < best)
                        {
                            best = result;
                        }
                    }
                }
            }
            break;
        case 3:
            for(int i =0; i < len;i++)
            {
                permutation[i] = nodes[i];
                for(int j = 0; j < len; j++)
                {
                    if(j != i)
                    {
                        permutation[j] = nodes[j];
                        for(int k =0; k < len;k++)
                        {
                            if(k != i && k != j)
                            {
                                permutation[k] = nodes[k];
                                int result = ShortestArray(head, permutation, len);
                                if(result < best)
                                {
                                    best = result;
                                }
                            }
                        }

                    }
                }
            }
            break;
        case 4:
            for(int i =0; i < len;i++)
            {
                permutation[i] = nodes[i];
                for(int j = 0; j < len; j++)
                {
                    if(j != i)
                    {
                        permutation[j] = nodes[j];
                        for(int k =0; k < len;k++)
                        {
                            if(k != i && k != j)
                            {
                                permutation[k] = nodes[k];
                                for(int o =0; o < len;o++)
                                {
                                    if (o != i && o != j && o != k)
                                    {
                                        permutation[o] = nodes[o];
                                        int result = ShortestArray(head, permutation, len);
                                        if(result < best)
                                        {
                                            best = result;
                                        }
                                    }
                                } 
                            }
                        }
                    }
                }
            }
            break;
        case 5:
            for(int i =0; i < len;i++)
            {
                permutation[i] = nodes[i];
                for(int j = 0; j < len; j++)
                {
                    if(j != i)
                    {
                        permutation[j] = nodes[j];
                        for(int k =0; k < len;k++)
                        {
                            if(k != i && k != j)
                            {
                                permutation[k] = nodes[k];
                                for(int o =0; o < len;o++)
                                {
                                    if (o != i && o != j && o != k)
                                    {
                                        permutation[o] = nodes[o];
                                        for (int p = 0; p < len; p++)
                                        {
                                            if (p != i && p != j && p != k && p != o)
                                            {
                                                permutation[p] = nodes[p];
                                                int result = ShortestArray(head, permutation, len);
                                                if(result < best)
                                                {
                                                    best = result;
                                                }
                                            }
                                        }
                                    }
                                } 
                            }
                        }
                    }
                }
            }
            break;
        case 6:
             for(int i =0; i < len;i++)
            {
                permutation[i] = nodes[i];
                for(int j = 0; j < len; j++)
                {
                    if(j != i)
                    {
                        permutation[j] = nodes[j];
                        for(int k =0; k < len;k++)
                        {
                            if(k != i && k != j)
                            {
                                permutation[k] = nodes[k];
                                for(int o =0; o < len;o++)
                                {
                                    if (o != i && o != j && o != k)
                                    {
                                        permutation[o] = nodes[o];
                                        for (int p = 0; p < len; p++)
                                        {
                                            if (p != i && p != j && p != k && p != o)
                                            {
                                                permutation[p] = nodes[p];
                                                for (int h = 0; h < len; h++)
                                                {
                                                    if (h != i && h != j && h != k && h != o && h != p)
                                                    {
                                                        permutation[h] = nodes[h];
                                                        int result = ShortestArray(head, permutation, len);
                                                        if(result < best)
                                                        {
                                                            best = result;
                                                        }
                                                    } 
                                                }
                                            }
                                        }
                                    }
                                } 
                            }
                        }
                    }
                }
            }
            break;   
        default:
            return -1;
    }
}