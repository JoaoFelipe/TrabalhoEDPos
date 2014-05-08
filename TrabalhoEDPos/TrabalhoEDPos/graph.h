#ifndef GRAPH_H
#define GRAPH_H

struct edge;

typedef struct node {
	int number;
	struct node *next;
	struct edge *edges;
	int helper;
	struct node *father;
} TNode;

typedef struct edge {
	struct node *node;
	struct edge *next;
	int cost;
} TEdge;


TNode * new_node(int number, TNode *next);

TEdge * new_edge(TNode *node, TEdge *next, int cost);

void free_edges(TEdge *edge);

void free_nodes(TNode *node);

void print_graph(TNode *graph);

TNode * insert_node(TNode *nodes, int val);

void insert_edge(TNode *graph, int origin, int dest, int cost);

void insert_edge_in_node(TNode *origin, TNode *dest, int cost);

TNode * remove_node(TNode *node, int number);

TNode * remove_edge_from_node(TNode *node, int number);

TNode * find_node(TNode *node, int number);

void remove_edge(TNode *node, int number1, int number2);

int is_connected(TNode *nodes);

void mark_neighbours(TNode *nodes);

int count_nodes(TNode* nodes);

int count_edge_sequence(TEdge *edge);

void count_nodes_and_edges(TNode *node, int * nodes, int * edges);

void save_file(TNode *node, char* name);

TNode * read_file(char* name);

#endif
