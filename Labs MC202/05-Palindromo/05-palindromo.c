#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define WORD_MAX_LENGTH 256

int is_2palindrome(char* word);


int main(void){
    char word[WORD_MAX_LENGTH];
    while (scanf("%s", word) != EOF){
        char word_lower[WORD_MAX_LENGTH];

        // Converte os caracteres de word para minúsculo e salva-os em word_lower
        for (unsigned i = 0; i < strlen(word); i++){
            word_lower[i] = (char) tolower(word[i]);
        }
        word_lower[strlen(word)] = '\0';

        // Checa se a palavra é 2-palindromo
        if (is_2palindrome(word_lower)){
            printf("%s\n", word);
        }
    }
    return 0;
}


int is_2palindrome(char* word){
    // Checagem rápida, se o tamanho for menor que 4, não pode ser 2-palindromo.
    if (strlen(word) < 4){
        return 0;
    }

    char first_subpalindrome[WORD_MAX_LENGTH];
    char second_subpalindrome[WORD_MAX_LENGTH];
    int already_found_a_palin = 0;

    /* Vamos fixar um índice final e um inicial e testar se o primeiro caractere
    é igual ao último, o segundo igual ao penúltimo etc. Se for, achamos um subpalíndromo
    e salvamos-o. Se não for, aumentamos o índice final em uma unidade e checamos
    novamente. Quando o índice final for igual ao comprimento da palavra e não tivermos
    encontrado nenhum subpalindromo, aumentamos o índice inicial em uma unidade e
    fazemos toda a checagem novamente.*/
    for (unsigned i = 0; i < strlen(word) - 2; i++){
        int continue_internal_loop = 1;
        for (unsigned j = i + 2; j < strlen(word) && continue_internal_loop; j++){
            unsigned start = i;
            unsigned end = j;
            int is_palin = 1;
            for (; start < end && is_palin; start++, end--){
                if (word[start] != word[end]) is_palin = 0;
            }

            // Encontro do primeiro palíndromo
            if (is_palin && !already_found_a_palin){
                already_found_a_palin = 1;
                start = i;
                end = j;
                for (unsigned index = 0; start <= end; start++, index++){
                    first_subpalindrome[index] = word[start];
                }
                first_subpalindrome[j - i + 1] = '\0';

                continue_internal_loop = 0;
            }

            // Encontro do segundo palíndromo
            else if (is_palin && already_found_a_palin){
                start = i;
                end = j;
                for (unsigned index = 0; start <= end; start++, index++){
                    second_subpalindrome[index] = word[start];
                }
                second_subpalindrome[j - i + 1] = '\0';

                // Se um não está contido no outro, então é 2-palindromo
                if (strstr(first_subpalindrome, second_subpalindrome) == NULL &&
                    strstr(second_subpalindrome, first_subpalindrome) == NULL){
                    return 1;
                }
                
                /* Se um está contido no outro, fico só com o menor subpalindromo e 
                continuo as verificações*/
                else if (strlen(first_subpalindrome) > strlen(second_subpalindrome)){
                    strcpy(first_subpalindrome, second_subpalindrome);
                }
            }
        }
    }
    return 0;
}