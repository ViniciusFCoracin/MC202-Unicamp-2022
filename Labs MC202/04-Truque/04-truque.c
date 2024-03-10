#include <stdio.h>
#include <math.h>

int sum(int v[], int r[], int len_R, int low_V, int high_V);

void atualize(int v[], int r[], int len_R, int index, int value);

int main(void){
    // Define o array V
    int num_elem_v;
    scanf("%d", &num_elem_v);
    int input_array[num_elem_v];

    //  Inicializa o array V
    int i = 0;
    while (i < num_elem_v && (scanf("%d", input_array + i++)) == 1);

    // Define o array R
    int len_array_r = (int) ceil(sqrt(num_elem_v));
    int array_r[len_array_r];

    // Inicializa o array R
    int index = 0;
    for (i = 0; i < num_elem_v; i += len_array_r){
        int soma = 0;
        for (int j = 0; j < len_array_r && i + j < num_elem_v; j++){
            soma += input_array[i + j];
        }
        array_r[index++] = soma;
    }

    // Lê as operações a serem realizadas e printa as saídas
    char operation;
    int first_arg, sec_arg;
    while (scanf("%c %d %d", &operation, &first_arg, &sec_arg) != EOF){
        if (operation == 's'){
            int ans = sum(input_array, array_r, len_array_r, first_arg, sec_arg);
            printf("%d\n", ans);
        }
        else if (operation == 'a'){
            atualize(input_array, array_r, len_array_r, first_arg, sec_arg);
        }
    }

    return 0;
}


int sum(int v[], int r[], int len_R, int low_V, int high_V){
    // Função que soma os elementos de V a partir do índice low_V
    // até o índice high_V, incluindo os extremos.

    int low_R = (int) low_V / len_R;   // Indica em que posição de r low_v está contido na soma
    int high_R = (int) high_V / len_R;   // Indica em que posição de r high_v está contido na soma
    int soma = 0;

    if (low_R < high_R){
        // Soma os elementos de R correspondentes aos elementos de V totalmente contidos em [i, j]
        for (int i = low_R + 1; i < high_R; i++){
        soma += r[i];
        }

        // Soma os elementos de V que restaram à esquerda
        for (int i = low_R * len_R + (low_V % len_R); i < (low_R + 1)* len_R; i++){
            soma += v[i];
        }

        // Soma os elementos de v que restaram à direita
        for (int i = high_R * len_R; i <= high_R * len_R + (high_V % len_R); i++){
            soma += v[i];
        }
    }

    // Se low_R == high_r, é mais simples somar diretamente em V
    else if (low_R == high_R){
        for (int i = low_V; i <= high_V; i++){
            soma += v[i];
        }
    }
    

    return soma;
}


void atualize(int v[], int r[], int len_R, int index, int value){
    // Função que atualiza ambos os arrays

    int index_r = (int) index / len_R;
    r[index_r] = r[index_r] - v[index] + value;
    v[index] = value;
}
