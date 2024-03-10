#include <stdio.h>
#include "redes.h"

int main(void){
    int** graph = NULL;
    int input, num_vertices;
    scanf("%d", &input);

    while (1){
        if (input == 0 && !graph){
            break;
        }
        else if (input == 0){
            int ans = how_many_criticals(graph, num_vertices);
            printf("%d\n", ans);
            free_graph(graph, num_vertices);
            graph = NULL;
        }
        else if (!graph){
            num_vertices = input;
            graph = create_graph(num_vertices);
        }
        else{
            int vertex;
            while (1){

                scanf("%d", &vertex);
                add_edge(graph, input - 1, vertex - 1);
                if (getchar() == '\n') break;
            }
        }
        scanf("%d", &input);
    }
}
