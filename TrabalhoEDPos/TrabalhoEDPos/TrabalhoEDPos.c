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
	//graph = remove_node(graph,7);
	//insert_edge(graph, 1, 3, 10);
	//insert_edge(graph, 3, 2, 10);
	//graph = remove_node(graph, 1);
	//graph = remove_node(graph, 7);
	//graph = remove_node(graph, 5);
	//save_file(graph, "temp2.txt");
	//print_graph(graph);

	int conexo = is_connected(graph);
	printf("Conexo: %d\n", conexo);
	TNode* k = kruskal(graph);
	print_graph(k);

	free_nodes(graph);
	free_nodes(k);

	int a;
	scanf(" %d", &a);
	return 0;
}

