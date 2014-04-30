#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"

typedef struct set {
	struct node *node;
	struct set *parent;
	int rank;
} TSet;

typedef struct edge_tuple {
	TSet *node1;
	TSet *node2;
	int cost;
	struct edge_tuple *next;
} TEdgeTuple;

TSet * find_set(TSet *set);

void union_set(TSet *x, TSet *y);

TSet * make_set(TNode *value);

TEdgeTuple * new_edge_tuple(TSet *n1, TSet *n2, int cost, TEdgeTuple *next);

void free_edge_tuple_list(TEdgeTuple *tuple_list);

TEdgeTuple * insert_edge_tuple(TEdgeTuple *list, TSet *n1, TSet *n2, int cost);

TNode * kruskal(TNode * graph);

#endif