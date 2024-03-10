/*  
    tarefas.h
    Implementa grafos direcionados, utilizando matriz de adjacências
*/

// Cria um grafo com num_v vértices
int** create_graph(int num_v);

// Libera a memória utilizada pelo grafo
void free_graph(int** graph, int num_v);

// Adiciona a aresta (v1, v2)
void add_edge(int** graph, int v1, int v2);
