#include "kruskal.h"
#include <stdlib.h>

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

TEdgeTuple * new_edge_tuple(void *node1, void *node2, int cost) {
	TEdgeTuple *result = (TEdgeTuple *) malloc(sizeof(TEdgeTuple));
	result->node1 = node1;
	result->node2 = node2;
	result->cost = cost;
	return result;
}

TEdgeTupleList * new_edge_tuple_list(TEdgeTuple *tuple, TEdgeTupleList *next) {
	TEdgeTupleList *result = (TEdgeTupleList *) malloc(sizeof(TEdgeTupleList));
	result->tuple = tuple;
	result->next = next;
	return result;
}

void free_edge_tuple_list(TEdgeTupleList *tuple_list) {
	TEdgeTupleList *temp;
	while (tuple_list) {
		temp = tuple_list->next;
		free(tuple_list);
		tuple_list = temp;
	}
}

TEdgeTupleList * insert_edge_tuple(TEdgeTupleList *list, TEdgeTuple *tuple) {
	TEdgeTupleList* new = new_edge_tuple_list(tuple, NULL);
	if (!list) {
		return new;
	}
	TEdgeTupleList *prev = NULL, *first = list;
	while (list && (list->tuple->cost < tuple->cost)) {
		prev = list;
		list = list->next;
	}
	new->next = list;
	if (!list || (list &&
			!((list->tuple->node1 == tuple->node1) &&
			 (list->tuple->node2 == tuple->node2)))) {
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
	TEdgeTupleList *sorted = NULL, *current_tuple;

	int size = count_nodes(graph), i;
	TSet **sets = (TSet **) malloc(sizeof(TSet *)*size);


	// makesets
	TNode *node = graph;
	i = 0;
	while (node) {
		node->helper = i;
		sets[i++] = make_set(node);
		result = insert_node(result, node->number);
		node = node->next;
	}

	// sorted edges by weight
	node = graph;
	while (node) {
		TEdge *edge = node->edges;
		while (edge) {
			if (edge->node->number > node->number) {
				TEdgeTuple *tuple = new_edge_tuple(
					(void *) sets[node->helper],
					(void *) sets[edge->node->helper],
					edge->cost
				);
				sorted = insert_edge_tuple(sorted, tuple);
			}
			edge = edge->next;
		}
		node = node->next;
	}

	// find minimum spanning tree
	current_tuple = sorted;
	while (current_tuple) {
		TSet *u = (TSet *) current_tuple->tuple->node1;
		TSet *v = (TSet *) current_tuple->tuple->node2;
		TSet *u_root = find_set(u), *v_root = find_set(v);
		if (u_root != v_root) {
			insert_edge(result, u->node->number, v->node->number, current_tuple->tuple->cost);
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