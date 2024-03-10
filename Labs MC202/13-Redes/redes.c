#include <stdio.h>
#include <stdlib.h>

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
    graph[v1][v2] = graph[v2][v1] = 1;
}


int is_critical(int** graph, int num_vert, int v){
    // Cria e inicializa array com os vértices visitados
    int visited[num_vert];
    for (int i = 0; i < num_vert; i++) visited[i] = 0;
    int visits = 1;

    // Cria uma fila para percorrer o grafo em largura
    int queue[num_vert];
    int front, rear;
    front = rear = 0;
    /* Torna o vértice 0 ou o vértice 1 o início da busca
    e "remove" o vértice v, marcando-o como visitado */
   if (v == 0){
        queue[rear++] = 1;
        visited[v] = visited[1] = 1;
    }
    else{
        queue[rear++] = 0;
        visited[v] = visited[0] = 1;
    }

    // Percorre em largura
    int curr_vert;
    while (front != rear){
        curr_vert = queue[front++];
        for (int i = 0; i < num_vert; i++) {
            if (graph[curr_vert][i] == 1 && !visited[i]){
                visited[i] = 1;
                queue[rear++] = i;
                visits += 1;
                if (visits == num_vert - 1) return 0;
            }
        }
    }

    return 1;
}


int how_many_criticals(int** graph, int num_vert){
    // Se houverem apenas 2 vértices, nenhum é crítico
    if (num_vert == 2) return 0;

    int count = 0;
    // "Remove" cada um dos vértices e testa se o grafo resultante ainda é conexo.
    for (int i = 0; i < num_vert; i++){
        if (is_critical(graph, num_vert, i)) count++;
    }

    return count;
}
