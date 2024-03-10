#include <stdio.h>
#include <stdlib.h>
#include "tarefas.h"

int** create_graph(int num_v){
    int** graph = (int**) malloc((unsigned) num_v * sizeof(int*));
    if (!graph) return NULL;

    for (int i = 0; i < num_v; i++){
        int* graph_row = (int*) malloc((unsigned) num_v * sizeof(int));
        graph[i] = graph_row;
        for (int j = 0; j < num_v; j++) graph_row[j] = 0;
    }

    return graph;
}


void free_graph(int** graph, int num_v){
    for (int i = 0; i < num_v; i++){
        free(graph[i]);
    }
    free(graph);
}

void add_edge(int** graph, int v1, int v2){
    graph[v1][v2] = 1;
}

