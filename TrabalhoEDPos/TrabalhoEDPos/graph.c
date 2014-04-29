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

void print_graph(TNode* graph){
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

int count_edge_sequence(TEdge *edge) {
	if (!edge) {
		return 0;
	}
	return 1 + count_edge_sequence(edge->next);
}

void count_nodes_and_edges(TNode *node, int * nodes, int * edges);
	*nodes = 0;
	*edges = 0;
	while (node) {
		*nodes += 1;
		*edges += count_edge_sequence(node->edges);
		node = node->next;
	}
	*edges /= 2;
}

void save(TNode *node, char *name) {
	int nodes, edges;
	count_nodes_and_edges(node, nodes, edges);
	FILE *file;
	file = fopen(name, "w");
	fprintf(file, "%d\n", nodes);
	TNode *temp = node;
	while (temp) {
		fprintf(file, "%d\n", temp->number);
		temp = temp->next;
	}
	fprintf(file, "%d\n", edges);
	TNode *temp = node;
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
