// TrabalhoEDPos.cpp : Defines the entry point for the console application.
//


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "kruskal.h"
#include "dijkstra.h"

void help() {
	printf("O que deseja fazer?\n");
	printf("0- Ajuda\n");
	printf("1- Imprimir grafo\n");
	printf("2- Inserir no\n");
	printf("3- Inserir aresta\n");
	printf("4- Remover no\n");
	printf("5- Remover aresta\n");
	printf("6- Arvore geradora minima\n");
	printf("7- Caminho minimo\n");
	printf("8- Salvar\n");
	printf("9- Sair\n");
}

int interface(TNode *graph) {
	int opt, v1, v2, c;
	printf("Grafo:\n");
	print_graph(graph);
	help();
	while (1) {
		printf("> ");
		scanf(" %d", &opt);
		switch (opt) {
			case 0:
				help();
				break;
			case 1:
				printf("Grafo:\n");
				print_graph(graph);
				break;
			case 2:
				printf("Inserir No. Digite um identificador para o no: \n>> ");
				scanf(" %d", &v1);
				graph = insert_node(graph, v1);
				break;
			case 3:
				printf("Inserir Aresta. Digite os identificadores dos nos e o custo: \n>> ");
				scanf(" %d %d %d", &v1, &v2, &c);
				insert_edge(graph, v1, v2, c);
				break;
			case 4:
				printf("Remover No. Digite um identificador para o no: \n>> ");
				scanf(" %d", &v1);
				graph = remove_node(graph, v1);
				break;
			case 5:
				printf("Remover Aresta. Digite os identificadores dos nos: \n>> ");
				scanf(" %d %d", &v1, &v2);
				remove_edge(graph, v1, v2);
				break;
			case 6:
				printf("Arvore geradora minima\n");
				if (is_connected(graph)) {
					TNode *k = kruskal(graph);
					save_file(k, "avm.txt");
					printf("Resultado salvo em avm.txt\n");
					free_nodes(k);
				} else {
					printf("Grafo desconexo\n");
				}
				break;
			case 7:				
				if (is_connected(graph)) {
					printf("Caminho Minimo. Digite o identificador do no: \n>> ");
					scanf(" %d", &v1);
					int ret = dijkstra(graph, v1);
					if (ret)
						printf("Resultado salvo em cmc.txt\n");
					else
						printf("No nao existe!\n");
				} else {
					printf("Grafo desconexo\n");
				}
				break;
			case 8:
				printf("Salvando arquivo saida.txt\n");
				save_file(graph, "saida.txt");
				break;
			case 9:
				free_nodes(graph);
				return 0;
		}
	}
}

int main(int argc, char **argv)
{
	TNode* graph;
	if (argc == 1) {
		graph = read_file(".txt");
	} else {
		graph = read_file(argv[1]);
	}
	return interface(graph);
}

