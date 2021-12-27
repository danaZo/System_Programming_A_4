#include "graph.h"
#include "nodes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getNumber(char* str)
{

}

int main()
{
    char* line = (char*)malloc(sizeof(char) * 10000);
    if(line == NULL)
    {
        printf("malloc failed");
        exit(1);
    }
    pnode list = NULL;
    char response = 'Z';
    printf("choose action:");
    while(response != 'e'){
        scanf("%c",&response);
        switch (response) {
            case 'A':
                scanf("%s",line);
                int firstN = 0;
                int numOfNodes = 0;
                char* currString = (char*)malloc(strlen(line));
                int counter = 0;
                for(int i = 1; i < strlen(line);i++)
                {
                    char curr = *(line+i);
                    if(firstN == 0)
                    {
                        if(curr == 'n')
                        {
                            firstN = 1;
                        }
                        else
                        {
                            numOfNodes *= 10;
                            numOfNodes += (int) *(line+i)-48;
                        }
                    }
                    else
                    {
                        if(curr != 'n')
                        {
                            *(currString+counter) = curr;
                            counter++;
                        }
                        else
                        {
                            counter = 0;
                            int srcNode = -1;
                            int destNode = -1;
                            int weight = -1;
                            for(int j =0; j < strlen(currString);j++){
                                if(*(currString+j) != ' ')
                                {
                                    if(srcNode == -1)
                                    {
                                        srcNode *= 10;
                                        srcNode += (int)*(currString+j)-48;
                                    }
                                    else if(destNode == -1){
                                        destNode *= 10;
                                        destNode += (int)*(currString+j)-48;
                                    }
                                    else{
                                        weight *= 10;
                                        weight += (int)*(currString+j)-48;
                                    }
                                }
                                else
                                {
                                    if(destNode == -1)
                                    {

                                    }
                                    else if(destNode != -1 && srcNode != -1 && weight != -1)
                                    {

                                    }
                                    else
                                    {
                                        destNode = -1;
                                    }
                                }
                            }
                        }
                    }
                }

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
