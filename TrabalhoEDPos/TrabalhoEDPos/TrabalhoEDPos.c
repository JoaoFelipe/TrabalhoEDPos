// TrabalhoEDPos.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define _CRT_SECURE_NO_DEPRECATE

int main(void)
{
	TNode* graph = NULL;
	//print_graph(graph);
	graph = insert_node(graph, 3);
	//print_graph(graph);

	graph = insert_node(graph, 2);
	//print_graph(graph);
	graph = insert_node(graph, 7);
	//print_graph(graph);
	graph = insert_node(graph, 5);
	//print_graph(graph);
	graph = insert_node(graph, 5);
	//print_graph(graph);
	graph = insert_node(graph, 2);
	//print_graph(graph);
	graph = insert_node(graph, 1);
	//print_graph(graph);
	graph = insert_node(graph, 1);
	//print_graph(graph);
	graph = insert_node(graph, 1);
	//print_graph(graph);
	graph = insert_node(graph, 1);
	//print_graph(graph);
	graph = insert_node(graph, 7);
	print_graph(graph);
	scanf("%d");
	return 0;
}

