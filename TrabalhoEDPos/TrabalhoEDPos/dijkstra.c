#include "dijkstra.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "graph.h"

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
		p->helper = -1;
		p = find_least_cost(nodes);
	}

	int size = 0;
	TNode *aux = p;
	while (aux){
		aux = aux->father;
		size++;
	}
	int * ret = (int*)malloc(sizeof(int)*size);
	int i = size - 1;
	while (p){
		ret[i--] = p->number;
		p = p->father;
		
	}
	for (i = 0; i < size; i++){
		printf("%d ", ret[i]);
	}
	return ret;
	
}