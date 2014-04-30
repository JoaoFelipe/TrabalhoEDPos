// TrabalhoEDPos.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "kruskal.h"



int main(void)
{
	TNode* graph = read_file("temp.txt");
	print_graph(graph);

	dijkstra(graph, 6, 3);
	
	
	int conexo = is_connected(graph);
	printf("\nConexo: %d\n", conexo);
	TNode* k = kruskal(graph);
	print_graph(k);

	free_nodes(graph);
	free_nodes(k);

	int a;
	scanf(" %d", &a);

	return 0;
}

