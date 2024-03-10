#include <stdio.h>
#include <stdlib.h>
#include "generica.h"
#define STR_MAXLEN 40

int main(void){
    List* L = NULL;
    char input;
    scanf(" %c", &input);

    while (input != 'f'){
        if (input == 'c'){
            if (L) free_list(L);
            L = create_list();
        }
        else if (input == 'i'){
            char type;
            Data data;
            scanf(" %c", &type);
            if (type == 'c'){
                scanf(" %c", &data.c);
                push(L, CHAR, data);
            }
            else if (type == 's'){
                char* string = (char*) malloc(STR_MAXLEN * sizeof(char));
                scanf(" %[^\n]", string);
                data.s = string;
                push(L, STR, data);
            }
            else if (type == 'd'){
                scanf("%d", &data.i);
                push(L, INT, data);
            }
            else if (type == 'f'){
                scanf("%f", &data.f);
                push(L, FLOAT, data);
            }
        }
        else if (input == 'p'){
            print_list(L);
        }
        else if (input == 'r'){
            int i, j;
            scanf(" %d %d", &i, &j);
            reverse(L, i, j);
        }
        else if (input == 't'){
            int i, j, k;
            scanf(" %d %d %d", &i, &j, &k);
            transpose(L, i, j, k);
        }
        else {
            printf("Invalid input.\n");
            exit(1);
        }

        scanf(" %c", &input);
    }

    if (L) free_list(L);
    return 0;
}
