/*  
    redes.h
    Implementa grafos não direcionados, utilizando matriz de adjacências
*/

// Cria um grafo com num_v vértices
int** create_graph(int num_v);

// Libera a memória utilizada pelo grafo
void free_graph(int** graph, int num_v);

// Adiciona a aresta (v1, v2)
void add_edge(int** graph, int v1, int v2);

// Testa se o vértice v é crítico
int is_critical(int** graph, int num_vert, int v);

// Itera sobre o grafo, contando quantos vértices críticos existem
int how_many_criticals(int** graph, int num_vert);
