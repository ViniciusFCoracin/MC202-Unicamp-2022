#include <stdio.h>
#include "tarefas.h"

int main(void){
    int tarefas, precedencias;
    scanf("%d", &tarefas);
    scanf("%d", &precedencias);
    int** graph = create_graph(tarefas);

    for (int i = 0; i < precedencias; i++){
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        add_edge(graph, v1, v2);
    }
    // função final

    return 0;
}
