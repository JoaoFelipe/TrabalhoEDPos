#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

TNode * new_node(int number, TNode *next) {
	TNode *result = (TNode *)malloc(sizeof(TNode));
	result->number = number;
	result->next = next;
	result->edges = NULL;
	return result;
}

TEdge * new_edge(TNode *node, TEdge *next, int cost) {
	TEdge *result = (TEdge *)malloc(sizeof(TEdge));
	result->node = node;
	result->next = next; 
	result->cost = cost;
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
			printf("%d(%d) ", q->node->number, q->cost);
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
void insert_edge(TNode* graph, int origin, int dest, int cost){
	insert_edge_in_node(graph, origin, dest, cost);
	insert_edge_in_node(graph, dest, origin, cost);

}
void insert_edge_in_node(TNode* graph,int origin, int dest, int cost){
	TNode * ori = find_node(graph, origin);
	TNode * destNode = find_node(graph, dest);
	if (!ori || !destNode){
		return;
	}
	TEdge * edges = ori->edges;
	
	if (!edges){		
		TEdge* newEdge = new_edge(destNode, NULL,cost);
		ori->edges = newEdge;
		return;
	}
	if (destNode->number < edges->node->number){
		TEdge* newEdge = new_edge(destNode, edges, cost);
		ori->edges = newEdge;
	}
	TEdge *p = edges;
	TEdge *ant = NULL;
	while (p && p->node->number < destNode->number){
		ant = p;
		p = p->next;
	}
	if (!p){
		TEdge* newEdge = new_edge(destNode, NULL, cost);
		ant->next = newEdge;
	}
	else if (p->node->number != destNode->number){
		TEdge* newEdge = new_edge(destNode, p, cost);
		ant->next = newEdge;
	}


}

TNode * remove_node(TNode *node, int number) {
	if (!node) {
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
			edge = edge->next;
		}
		free_edges(node->edges);
		free(node);
	}
	return first;
}

TNode * remove_edge_from_node(TNode *node, int number) {
	TNode * result = NULL;
	if (!node || !node->edges) {
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
int count_nodes(TNode* nodes){
	int count = 0;
	TNode *p = nodes;
	while (!p){
		count++;
		p = p->next;
	}
	return count;
}
int is_connected(TNode *nodes){



}