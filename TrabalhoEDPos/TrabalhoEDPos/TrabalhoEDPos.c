// TrabalhoEDPos.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(void)
{
	TNode* graph = NULL;
//	printGraph(graph);
	graph = insertNode(graph, 3);
//	printGraph(graph);

	graph = insertNode(graph, 2);
//	printGraph(graph);
	graph = insertNode(graph, 7);
//	printGraph(graph);
	graph = insertNode(graph, 5);
//	printGraph(graph);
	graph = insertNode(graph, 5);
//	printGraph(graph);
	graph = insertNode(graph, 2);
//	printGraph(graph);
	graph = insertNode(graph, 1);
//	printGraph(graph);
	graph = insertNode(graph, 1);
//	printGraph(graph);
	graph = insertNode(graph, 1);
//	printGraph(graph);
	graph = insertNode(graph, 1);
//	printGraph(graph);
	graph = insertNode(graph, 7);

	insert_edge(graph, 2, 5, 3);
	insert_edge(graph, 2, 5, 7);
	insert_edge(graph, 2, 7, 11);
	insert_edge(graph, 2, 108, 0);

	printGraph(graph);
	graph = remove_node(graph,7);


	printGraph(graph);
	scanf_s("%d");
	return 0;
}

