#include "disjoint_set.h"
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

TSetList * new_set_list(TSet *set, TSetList *next) {
	TSetList *result = (TSetList *) malloc(sizeof(TSetList));
	result->set = set;
	result->next = next;
	return result;
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

void free_set_list(TSetList *set_list) {
	TSetList *temp;
	while (set_list) {
		temp = set_list->next;
		free(set_list->set);
		free(set_list);
		set_list = temp;
	}
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

TEdgeTupleList * kruskal(TNode * graph) {
	TEdgeTupleList *result = NULL;
	TSetList *sets = NULL;
	TEdgeTupleList *ordered = NULL;
	TNode *node = graph;
	while (node) {
		TSet *set = make_set(node);
		sets = new_set_list(set, sets);
		TEdge *edge = node->edges;
		while (edge) {
			if (edge->node->number > node->number) {
				TEdgeTuple *tuple = new_edge_tuple(
					(void *) node, (void *) edge->node, edge->cost
				);
				ordered = insert_edge_tuple(ordered, tuple);
			}
			edge = edge->next;
		}
		node = node.next;
	}

	

	free_set_list(sets);

}