#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashing.h"

int insert(hashtable* HT, char* data, unsigned int timestamp){
    if (search(HT, data) != -1) return 0;
    
    unsigned long key = hash1(data) % HT -> maxsize;
    unsigned long step = hash2(data);
    unsigned int i = 0;

    while (i < HT -> maxsize){
        // If the position is not empty
        if (strcmp(HT -> array[key].key, "NONE") != 0 && strcmp(HT -> array[key].key, "DELETED") != 0){
            // If the element is already in that position
            if (strcmp(HT -> array[key].data, data) == 0) return 0;
            // If it's not
            else{
                key = (key + step) % HT -> maxsize;
                i++;
            }
        }
        // If the position is empty
        else break;
    }

    if (i >= HT -> maxsize) return 0;
    else{
        free(HT -> array[key].key);

        element new_element;
        new_element.data = data;
        new_element.key = data;
        new_element.timestamp = timestamp;

        HT -> array[key] = new_element;
        HT -> num_elem += 1;
        return 1;
    }
}


int delete_element(hashtable* HT, char* data){
    if (search(HT, data) == -1) return 0;

    unsigned long key = hash1(data) % HT -> maxsize;
    unsigned long step = hash2(data);
    unsigned int i = 0;

    // Stops when a None place is found or when the entire table was traversed
    while (strcmp(HT -> array[key].key, "NONE") != 0 && i < HT -> maxsize){
        // If the element is found, it is removed.
        if (strcmp(HT -> array[key].key, "DELETED") != 0 && strcmp(HT -> array[key].data, data) == 0){
            free(HT -> array[key].key);
            HT -> array[key].key = (char*) malloc(8 * sizeof(char));
            char new_key[8] = "DELETED";
            strcpy(HT -> array[key].key, new_key);
            HT -> num_elem -= 1;
            return 1;
        }
        // Else, goes to the next index
        key = (key + step) % HT -> maxsize;
        i++;
    }
    
    return 0;
}


int search(hashtable* HT, char* data){
    unsigned long key = hash1(data) % HT -> maxsize;
    unsigned long step = hash2(data);
    unsigned int i = 0;

    // Stops when a None place is found or when the entire table was traversed
    while (strcmp(HT -> array[key].key, "NONE") != 0 && i < HT -> maxsize){
        // If the position is not empty and the data matches
        if (strcmp(HT -> array[key].key, "DELETED") != 0 && strcmp(HT -> array[key].data, data) == 0){ 
            return (int) key;   
        }
        key = (key + step) % HT -> maxsize;
        i++;
    }
    return -1;
}


hashtable* resize(hashtable* HT){
    unsigned new_size = (HT ->  maxsize) * 2;
    hashtable* new_ht = create_ht(new_size);
    if (!new_ht) return NULL;
    new_ht -> num_elem = HT -> num_elem;

    // Traverse the entire old hash table
    for (unsigned i = 0; i < HT -> maxsize; i++){
        // Rehash the non-null elements
        if (strcmp(HT -> array[i].key, "NONE") != 0 && strcmp(HT -> array[i].key, "DELETED") != 0){
            unsigned long key = hash1(HT -> array[i].data) % new_size;
            unsigned long step = hash2(HT -> array[i].data);
            unsigned int j = 0;
            while (strcmp(new_ht -> array[key].key, "NONE") != 0 && j < new_size){
                key = (key + step) % (new_size);
                j++;
            }
            element new_element;
            char* new_data = (char*) malloc((strlen(HT -> array[i].data) + 1) * sizeof(char));
            strcpy(new_data, HT -> array[i].data);
            new_element.key = new_data;
            new_element.data = new_data;
            new_element.timestamp = HT -> array[i].timestamp;
            new_ht -> array[key] = new_element;
        }
     }
    free_ht(HT);
    return new_ht;
}


hashtable* create_ht(unsigned maxsize){
    element* array = (element*) malloc(maxsize * sizeof(element));
    if (!array) return NULL;
    hashtable* HT = (hashtable*) malloc(sizeof(hashtable));
    if(!HT) return NULL;

    HT -> maxsize = maxsize;
    HT -> num_elem = 0;
    HT -> array = array;

    for (unsigned i = 0; i < maxsize; i++){
        HT -> array[i].key = (char*) malloc(5 * sizeof(char));
        char key[5] = "NONE";
        strcpy(HT -> array[i].key, key); 
    }
    return HT;
}


void free_ht(hashtable* HT){
    for (unsigned i = 0; i < HT -> maxsize; i++){
        free(HT -> array[i].key);
    }
    free(HT -> array);
    free(HT);
}


unsigned long hash1(char *str){
    unsigned long hash = 5381;
    unsigned long c;

    while ((c = (unsigned char) *str++))
    hash = ((hash << 5) + hash) ^ c; // hash * 33 XOR c

    return hash;
}


unsigned long hash2(char* key){
    unsigned long hash = 0;
    unsigned long c;

    while ((c = (unsigned char) *key++)) {
        hash = (hash << 5) + hash + c; // Utiliza a técnica de multiplicação e soma
    }

    return (hash % 7) + 1; // Retorna um valor entre 1 e 7
}
