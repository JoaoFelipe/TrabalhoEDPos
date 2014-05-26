#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

int dijkstra(TNode* nodes, int start);
void prepare_array(int* val, int size, int num);
int prepare_helpers(TNode *graph);
#endif