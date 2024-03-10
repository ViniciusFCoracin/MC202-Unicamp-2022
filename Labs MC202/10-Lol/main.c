#include <stdio.h>
#include <stdlib.h>
#include "lol.h"

int main(void){
    matrix* M = NULL;

    char input;
    scanf(" %c", &input);

    while (input != 't'){
        if (input == 'c'){
        M = create_matrix(M);
        }
        else if (input == 'a'){
            int i, j, x;
            scanf(" [%d,%d] %d", &i, &j, &x);
            if (x == 0) set_zero(M, i, j);
            else set(M, x, i, j);
        }
        else if (input == 'r'){
            int i, j, ans;
            scanf(" [%d,%d]", &i, &j);
            ans = get(M, i, j);
            printf("M[%d][%d] == %d\n", i, j, ans);
        }
        else if (input == 'p'){
            print_matrix(M);
        }
        else {
            printf("Invalid input.\n");
            exit(1);
        }

        scanf(" %c", &input);
    }

    return 0;
}
