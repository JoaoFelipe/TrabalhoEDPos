// TrabalhoEDPos.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(void)
{
	TNode* graph = read_file("temp.txt");
	//print_graph(graph);
	//graph = remove_node(graph,7);
	//insert_edge(graph, 1, 3, 10);
	//insert_edge(graph, 3, 2, 10);
	dijkstra(graph, 6, 3);
	//graph = remove_node(graph, 1);
	//graph = remove_node(graph, 7);
	//graph = remove_node(graph, 5);
	save_file(graph, "temp2.txt");
	//print_graph(graph);
//	int conexo = is_connected(graph);
//	printf("%d", conexo);
	scanf("%d");
	return 0;
}

