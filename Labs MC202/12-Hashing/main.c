#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashing.h"
#define STR_MAX_LEN 251

int main(void){
    hashtable* hashing_table = NULL;
    unsigned int timestamp = 0;
    
    char input;
    scanf(" %c", &input);
    getchar();

    while (input != 'f'){
        if (input == 'c'){
            if (hashing_table != NULL){
                free_ht(hashing_table);
                timestamp = 0;
            }

            unsigned maxsize;
            scanf("%u", &maxsize);
            hashing_table = create_ht(maxsize);
        }
        else if (input == 'i'){
            char* data = (char*) malloc(STR_MAX_LEN * sizeof(char));
            getchar();
            scanf("%[^\n]", data);
            int ans = insert(hashing_table, data, timestamp);
            if (ans == 1){
                timestamp++;
                if (hashing_table -> num_elem >= 0.7 * hashing_table -> maxsize){
                    hashing_table = resize(hashing_table);
                }
            }
        }
        else if (input == 'r'){
            char str[STR_MAX_LEN];
            getchar();
            scanf("%[^\n]", str);
            delete_element(hashing_table, str);
        }
        else if (input == 'b'){
            char str[STR_MAX_LEN];
            getchar();
            scanf("%[^\n]", str);
            int ans = search(hashing_table, str);
            if (ans == -1){
                printf("[%s] nao esta na tabela\n", str);
            }
            else{
                printf("[%s] esta na tabela, timestamp %u\n", str, hashing_table -> array[ans].timestamp);
            }            
        }

        scanf(" %c", &input);
    }
    free_ht(hashing_table);

    return 0;
}
