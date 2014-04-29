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

TNode * remove_node(TNode *node, int number) {
	if (!node){ 
		return node;
	}
	TNode *prev = NULL;
	TNode *first = node;
	while (node && (node->number < number)) {
		prev = node;
		node = node->next;
	}
	if (node && (node->number == number)) {
		if (prev) {
			prev->next = node->next;
		} else {
			first = node->next;
		}

		TEdge *edge = node->edges;
		while(edge) {
			remove_edge_from_node(edge->node, node->number);
		}
		free_edges(node->edges);
		free(node);
	}
	return first;
}

TNode * remove_edge_from_node(TNode *node, int number) {
	TNode * result = NULL;
	if (!node || !node->edges){
		return result;
	}
	TEdge *prev = NULL, *first = node->edges, *edge = node->edges;
	while (edge && (edge->node->number < number)) {
		prev = edge;
		edge = edge->next;
	}
	if (edge && (edge->node->number == number)) {
		if (prev) {
			prev->next = edge->next;
		} else {
			node->edges = edge->next;
		}
		result = edge->node;
		free(edge);
	}
	return result;
}

TNode * find_node(TNode *node, int number) {
	while (node && (node->number < number)) {
		node = node->next;
	}
	if (node && (node->number == number)) {
		return node;
	}
	return NULL;
}

TNode * remove_edge(TNode *node, int number1, int number2) {
	TNode *found = find_node(node, number1);
	if (!found) return node;
	found = remove_edge_from_node(found, number2);
	if (!found) return node;
	remove_edge_from_node(found, number1);
	return node;
}
