#include "graph.h"
#include <stdlib.h>

TNode * new_node(int number, TNode *next) {
	TNode *result = (TNode *)malloc(sizeof(TNode));
	result->number = number;
	result->next = next;
	result->edges = NULL;
	return result;
}

TEdge * new_edge(TNode *node, TEdge *next) {
	TEdge *result = (TEdge *)malloc(sizeof(TEdge));
	result->node = node;
	result->next = next;
	return result;
}

void free_edges(TEdge *edge) {
	TEdge *temp;
	while (edge) {
		temp = edge->next;
		free(edge);
		edge = temp;
	}
}

void free_nodes(TNode *node) {
	TNode *temp;
	while (node) {
		temp = node->next;
		free_edges(node->edges);
		free(node);
		node = temp;
	}
}
void printGraph(TNode* graph){
	TNode* p = graph;
	while (p){
		printf("%d : ", p->number);
		TEdge * q = p->edges;
		while (q){
			printf("%d ", q->node->number);
			q = q->next;
		}
		printf("\n");
		p = p->next;
	}
	printf("\n");
}
TNode* insertNode(TNode* nodes,int val){
	if (!nodes){
		TNode* newNode = new_node(val, NULL);
		return newNode;
	}
	if (val < nodes->number){
		TNode* newNode = new_node(val, nodes);
		return newNode;
	}
	TNode *p = nodes;
	TNode *ant = NULL;
	while (p && p->number < val){
		ant = p;
		p = p->next;
	}
	if (!p){
		TNode* newNode = new_node(val, NULL);
		ant->next = newNode;
	}
	else if ( p->number != val){
		TNode* newNode = new_node(val, p);
		ant->next = newNode;
	}
	return nodes;
	
}

