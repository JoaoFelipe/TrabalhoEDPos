#include "graph.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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

void print_graph(TNode* graph){
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

TNode* insert_node(TNode *node, int number){
	TNode* new = new_node(number, NULL);
	if (!node) {
		return new;
	}
	TNode *prev = NULL, *first = node;
	while (node && (node->number < number)) {
		prev = node;
		node = node->next;
	}
	new->next = node;
	if ((node && (node->number != number)) || !node) {
		if (!prev ) {
			first = new;
		} else  {
			prev->next = new;
		}
	}
	return first;
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

	if (!edges) {
		TEdge* newEdge = new_edge(destNode, NULL,cost);
		ori->edges = newEdge;
		return;
	}
	if (destNode->number < edges->node->number){
		TEdge* newEdge = new_edge(destNode, edges, cost);
		ori->edges = newEdge;
		return;
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
	TNode *prev = NULL, *first = node;
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
void reset_helper(TNode *nodes, int val){
	TNode* p = nodes;
	while (p){
		p->helper = val;
		p->father = NULL;
		p = p->next;
		
	}
}

int is_connected(TNode *nodes){
	reset_helper(nodes,0);
	mark_neighbours(nodes);
	TNode *p = nodes;
	while (p){
		if (p->helper == 0)
			return 0;
		p = p->next;
	}
	return 1;
}
TNode* find_least_cost(TNode* nodes){
	TNode*p = nodes->next;
	TNode*ret = nodes;
	while (p){
		if (p->helper != -1){
			if (p->helper < ret->helper || ret->helper == -1)
				ret = p;
		}
		
		p = p->next;
	}
	return ret;
}
int* dijkstra(TNode* nodes, int start, int end){
	reset_helper(nodes, INT_MAX);
	TNode *p = find_node(nodes, start);
	p->helper = 0;
	int size = 0;
	
	while (p->helper != -1){
		if (p->number == end)
			break;
		TEdge* e = p->edges;
		while (e){
			if (e->node->helper != -1){				
				int val = p->helper + e->cost;								
				if (val < e->node->helper){
					e->node->helper = val;
					e->node->father = p;
				}
												
			}	
			e = e->next;
		}
		size++;
		p->helper = -1;
		p = find_least_cost(nodes);
	}
	int * ret = (int*)malloc(sizeof(int)*size);
	int i = size-1;
	while (p){
		ret[i] = p->number;
		i--;
		p = p->father;
	}
	return ret;
	
}
void mark_neighbours(TNode *nodes){

		nodes->helper = -1;
		TEdge *e = nodes->edges;
		while (e){
			if (e->node->helper == 0)
				mark_neighbours(e->node);
			e = e->next;
		}
	
}

int count_edge_sequence(TEdge *edge) {
	if (!edge) {
		return 0;
	}
	return 1 + count_edge_sequence(edge->next);
}

void count_nodes_and_edges(TNode *node, int * nodes, int * edges) {
	*nodes = 0;
	*edges = 0;
	while (node) {
		*nodes += 1;
		*edges += count_edge_sequence(node->edges);
		node = node->next;
	}
	*edges = *edges / 2;
}

void save_file(TNode *node, char *name) {
	int nodes, edges;
	count_nodes_and_edges(node, &nodes, &edges);
	FILE *file;
	file = fopen(name, "w");
	fprintf(file, "%d\n", nodes);
	TNode *temp = node;
	while (temp) {
		fprintf(file, "%d\n", temp->number);
		temp = temp->next;
	}
	fprintf(file, "%d\n", edges);
	temp = node;
	while (temp) {
		TEdge *edge = temp->edges;
		while (edge) {
			if (edge->node->number > temp->number) {
				fprintf(file, "%d %d %d\n",
						temp->number,
						edge->node->number,
						edge->cost);
			}
			edge = edge->next;
		}
		temp = temp->next;
	}
	fclose(file);
}

TNode * read_file(char* name) {
	TNode *result = NULL;
	FILE *file;
	file = fopen(name, "r");
	if (file) {
		int nodes, edges, i;
		fscanf(file, " %d", &nodes);
		for (i = 0; i < nodes; i++) {
			int number;
			fscanf(file, " %d", &number);
			result = insert_node(result, number);
		}
		fscanf(file, " %d", &edges);
		for (i = 0; i < edges; i++) {
			int number1, number2, cost;
			fscanf(file, " %d %d %d", &number1, &number2, &cost);
			insert_edge(result, number1, number2, cost);
		}
		fclose(file);
	}
	return result;
}
