#include "kruskal.h"
#include <stdlib.h>
#include <stdio.h>

TSet * find_set(TSet * set) {
	TSet *temp = NULL, *root = set;
	while (root->parent) {
		root = root->parent;
	}
	while (set->parent) {
		temp = set->parent;
		set->parent = root;
		set = temp;
	}
	return root;
}

void union_set(TSet *x, TSet *y) {
	TSet *x_root = find_set(x);
	TSet *y_root = find_set(y);
	if (x_root == y_root)
		return;

	if (x_root->rank < y_root->rank) {
		x_root->parent = y_root;
	} else if (x_root->rank > y_root->rank) {
		y_root->parent = x_root;
	} else {
		y_root->parent = x_root;
		x_root->rank++;
	}
}

TSet * make_set(TNode *node) {
	TSet *set = (TSet*) malloc(sizeof(TSet));
	set->node = node;
	set->parent = NULL;
	set->rank = 0;
	return set;
}


TEdgeTuple * new_edge_tuple(TSet *n1, TSet *n2, int cost, TEdgeTuple *next) {
	TEdgeTuple *result = (TEdgeTuple *) malloc(sizeof(TEdgeTuple));
	result->node1 = n1;
	result->node2 = n2;
	result->cost = cost;
	result->next = next;
	return result;
}

void free_edge_tuple_list(TEdgeTuple *edge_tuple) {
	if (edge_tuple) {
		free_edge_tuple_list(edge_tuple->next);
		free(edge_tuple);
	}
}

TEdgeTuple * insert_edge_tuple(TEdgeTuple *edge, TSet *n1, TSet *n2, int cost) {
	TEdgeTuple *new = new_edge_tuple(n1, n2, cost, NULL);
	if (!edge) {
		return new;
	}
	TEdgeTuple *prev = NULL, *first = edge;
	while (edge && (edge->cost < cost)) {
		prev = edge;
		edge = edge->next;
	}
	new->next = edge;
	if (!edge || (edge && !((edge->node1 == n1) && (edge->node2 == n2)))) {
		if (!prev) {
			first = new;
		} else  {
			prev->next = new;
		}
	}
	return first;
}


TNode * kruskal(TNode * graph) {
	TNode *result = NULL;
	TEdgeTuple *sorted = NULL, *current_tuple;
	int size = count_nodes(graph), i;
	TSet **sets = (TSet **) malloc(sizeof(TSet *)*size);

	// makesets
	TNode *node = graph;
	i = 0;
	while (node) {
		node->helper = i;
		sets[i] = make_set(node);
		result = insert_node(result, node->number);
		node = node->next;
		i++;
	}

	// sorted edges by weight
	node = graph;
	while (node) {
		TEdge *edge = node->edges;
		while (edge) {
			if (edge->node->number > node->number) {
				TSet *u = sets[node->helper];
				TSet *v = sets[edge->node->helper];
				sorted = insert_edge_tuple(sorted, u, v, edge->cost);
			}
			edge = edge->next;
		}
		node = node->next;
	}

	// find minimum spanning tree
	current_tuple = sorted;
	while (current_tuple) {
		TSet *u = current_tuple->node1;
		TSet *v = current_tuple->node2;
		TSet *u_root = find_set(u), *v_root = find_set(v);
		if (u_root != v_root) {
			insert_edge(result, u->node->number, v->node->number, current_tuple->cost);
			union_set(u_root, v_root);
		}
		current_tuple = current_tuple->next;
	}

	// free sets
	for (i = 0; i < size; i++) {
		free(sets[i]);
	}
	free(sets);
	free_edge_tuple_list(sorted);

	return result;
}