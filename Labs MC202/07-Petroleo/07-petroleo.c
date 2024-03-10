#include <stdio.h>
#include <stdlib.h>

char** malloc_char_matrix(unsigned lines, unsigned rows);

int count_areas(char** cpp, unsigned lines, unsigned rows);

void clear_around(char** cpp, unsigned lines, unsigned rows, unsigned i, unsigned j);

void free_char_matrix(char** ipp, unsigned lines);

int main(void){
    unsigned lines, rows;
    scanf("%u %u", &lines, &rows);
    getchar();  //  Consome o \n do final da linha.

    while (lines){
        char c;
        char** cpp;
        int num_areas;

        cpp = malloc_char_matrix(lines, rows);

        for (unsigned i = 0; i < lines; i++){
            for (unsigned j = 0; j < rows; j++){
                c = (char) getchar();
                cpp[i][j] = c;
            }
            getchar();  // Consome o \n do final da linha.
        }

        num_areas = count_areas(cpp, lines, rows);
        printf("%d\n", num_areas);
        free_char_matrix(cpp, lines);

        scanf("%u %u", &lines, &rows);
        getchar();
    }

    return 0;
}


char** malloc_char_matrix(unsigned lines, unsigned rows){
    char** cpp;
    cpp = malloc(lines * sizeof(char*));

    for (unsigned i = 0; i < lines; i++){
        cpp[i] = malloc(rows * sizeof(char));
    }

    return cpp;
}


void free_char_matrix(char** cpp, unsigned lines){
    for (unsigned i = 0; i < lines; i++){
        free(cpp[i]);
    }
    free(cpp);
}


int count_areas(char** cpp, unsigned lines, unsigned rows){
    int count = 0;

    for (unsigned i = 0; i < lines; i++){
        for (unsigned j = 0; j < rows; j++){
            if (cpp[i][j] == '@'){
                count++;
                clear_around(cpp, lines, rows, i, j);
            }
        }
    }

    return count;
}


void clear_around(char** cpp, unsigned lines, unsigned rows, unsigned i, unsigned j){
    /* Escreve '*' na posição atual, ou seja, cpp[i][j]. Em seguida, olha para todas
    as casas ao redor, procurando por '@' adjacentes. Quando encontra, chama novamente
    essa função recursivamente, até que todos os '@' adjacentes sejam tranformados em '*'.*/
    
    cpp[i][j] = '*';

    if (i > 0 && j > 0 && cpp[i - 1][j - 1] == '@'){
        // Verifica se a casa superior esquerda é @
        clear_around(cpp, lines, rows, i - 1, j - 1);
    }
    if (i > 0 && cpp[i - 1][j] == '@'){
        // Verifica se a casa acima é @
        clear_around(cpp, lines, rows, i - 1, j);
    }
    if (i > 0 && j < rows - 1 && cpp[i - 1][j + 1] == '@'){
        // Verifica se a casa superior direita é @
        clear_around(cpp, lines, rows, i - 1, j + 1);
    }
    if (j > 0 && cpp[i][j - 1] == '@'){
        // Verifica se a casa à esquerda é @
        clear_around(cpp, lines, rows, i, j - 1);
    }
    if (j < rows - 1 && cpp[i][j + 1] == '@'){
        // Verifica se a casa à direita é @
        clear_around(cpp, lines, rows, i, j + 1);
    }
    if (i < lines - 1 && j > 0 && cpp[i + 1][j - 1] == '@'){
        // Verifica se a casa inferior esquerda é @
        clear_around(cpp, lines, rows, i + 1, j - 1);
    }
    if (i < lines - 1 && cpp[i + 1][j] == '@'){
        // Verifica se a casa abaixo é @
        clear_around(cpp, lines, rows, i + 1, j);
    }
    if (i < lines - 1 && j < rows - 1 && cpp[i + 1][j + 1] == '@'){
        // Verifica se a casa inferior direita é @
        clear_around(cpp, lines, rows, i + 1, j + 1);
    }
}