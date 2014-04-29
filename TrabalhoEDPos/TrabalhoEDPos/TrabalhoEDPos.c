// TrabalhoEDPos.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


int main(void)
{
	TNode* graph = read_file("temp.txt");
	print_graph(graph);
	graph = remove_node(graph,7);
	save_file(graph, "temp2.txt");
	print_graph(graph);
	scanf_s("%d");
	return 0;
}

