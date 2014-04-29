#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"

typedef struct set {
	struct node *node;
	struct set *parent;
	int rank;
} TSet;

typedef struct set_list {
	struct set_list *next;
	struct set *set;
} TSetList;

typedef struct edge_tuple {
	void *node1;
	void *node2;
	int cost;
} TEdgeTuple;

typedef struct edge_tuple_list {
	struct edge_tuple *tuple;
	struct edge_tuple_list *next;
} TEdgeTupleList;

TSet * find_set(TSet *set);

void union_set(TSet *x, TSet *y);

TSet * make_set(TNode *value);

TSetList * new_set_list(TSet *set, TSetList *next);

TEdgeTuple * new_edge_tuple(void *node1, void *node2, int cost);

TEdgeTupleList * new_edge_tuple_list(TEdgeTuple *tuple, TEdgeTupleList *next);

void free_set_list(TSetList *set_list);

void free_edge_tuple_list(TEdgeTupleList *tuple_list);

TEdgeTupleList * insert_edge_tuple(TEdgeTupleList *list, TEdgeTuple *tuple);

TEdgeTupleList * kruskal(TNode * graph);

#endif