#include "graph.h"


void add_edge(node *this, node *other, int weight);
pedge getEdge(pnode src, int dest);
pnode getNode(pnode head, int id);
void removeEdge(pnode src, int dest);
int findMaxID(pnode head);
int getAllPermutations(pnode head, const int *nodes, int len);