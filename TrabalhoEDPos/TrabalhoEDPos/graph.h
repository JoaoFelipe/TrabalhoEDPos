#ifndef GRAPH_H
#define GRAPH_H

struct edge;

typedef struct node {
	int number;
	struct node *next;
	struct edge *edges;
} TNode;

typedef struct edge {
	struct node *node;
	struct edge *next;
} TEdge;


TNode * new_node(int number, TNode *next);

TEdge * new_edge(TNode *node, TEdge *next);

void free_edges(TEdge *edge);

void free_nodes(TNode *node);


void print_graph(TNode *graph);

TNode * insert_node(TNode *nodes, int val);

TNode * remove_node(TNode *node, int number);

TNode * remove_edge_from_node(TNode *node, int number);

TNode * find_node(TNode *node, int number);

TNode * remove_edge(TNode *node, int number1, int number2);

int count_edge_sequence(TEdge *edge);

void count_nodes_and_edges(TNode *node, int * nodes, int * edges);

void save(TNode *node, char* name);

#endif
