#include <stdio.h>
#include <stdlib.h>
#include "lol.h"

matrix* create_matrix(matrix* M){
    if (M != NULL){
        free(M);
    }

    matrix* new_matrix;
    row* safe_row;
    new_matrix = (matrix*) malloc(sizeof(matrix));
    safe_row = (row*) malloc(sizeof(row));
    
    new_matrix -> head = safe_row;
    safe_row -> i = -1;
    safe_row -> next = NULL;

    return new_matrix;
}


void free_matrix(matrix* M){
    row* rp = M -> head;
    while(rp != NULL){
        node* np = rp -> head;
        while (np != NULL){
            node* aux = np;
            np = aux -> next;
            free(aux);
        }
        row* aux = rp;
        rp = rp -> next;
        free(aux);
    }
    free(M);
}


row* create_row(matrix* M, int i){
    int smaller_row;
    smaller_row = (M -> head -> next == NULL)? -1 : M -> head -> next -> i;

    row* rp = M -> head;
    if (smaller_row != -1 && i > smaller_row){
        // If the row is not imediately after M -> head
        while (rp != NULL){
            if (rp -> next == NULL || (rp -> i < i && rp -> next -> i > i)){
                break;
            }
            else{
                rp = rp -> next;
            }
        }
    }    

    row* new_row = (row*) malloc(sizeof(row));
    node* safe_node = (node*) malloc(sizeof(node));
    safe_node -> next = NULL;
    safe_node -> j = -1;
    new_row -> i = i;
    new_row -> head = safe_node;

    new_row -> next = rp -> next;
    rp -> next = new_row;

    return new_row;
}


node* create_node(row* R, int j, int x){
    int smaller_node;
    smaller_node = (R -> head -> next == NULL)? -1 : R -> head -> next -> j;

    node* np = R -> head;
    if (smaller_node != -1 && j > smaller_node){
        // If the node is not imediately after rp -> head
        while (np != NULL){
            if (np -> next == NULL || (np -> j < j && np -> next -> j > j)){
                break;
            }
            else{
                np = np -> next;
            }
        }
    }    

    node* new_node = (node*) malloc(sizeof(node));
    new_node -> j = j;
    new_node -> data = x;

    new_node -> next = np -> next;
    np -> next = new_node;

    return new_node;
}


void remove_row(matrix* M, int i){
    row* rp = M -> head;
    while(1){
        // Gets the row before the one with index i
        if (rp -> next -> i == i) break;
        else rp = rp -> next;
    }

    free(rp -> next -> head -> next);
    free(rp -> next -> head);
    row* aux = rp -> next;
    rp -> next = aux -> next;
    free(aux);
}


void remove_node(row* R, int j){
    node* np = R -> head;
    while(1){
        // Gets the element before the one with index j
        if (np -> next -> j == j) break;
        else np = np -> next;
    }

    node* aux = np -> next;
    np -> next = aux -> next;
    free(aux);
}


void set(matrix* M, int x, int i, int j){
    row* rp = M -> head -> next;
    while(rp != NULL){
        // Checks if there is already a row with index i
        if (rp -> i == i) break;
        else rp = rp -> next;
    }
    if (rp == NULL){
        rp = create_row(M, i);
    }
    
    node* np = rp -> head;
    while(np != NULL){
        // Checks if there is already a node with index j
        if (np -> j == j){
            np -> data = x;
            break;
        }
        else np = np -> next;
    }
    if (np == NULL){
        np = create_node(rp, j, x);
    }
}       


void set_zero(matrix* M, int i, int j){
    if (get(M, i, j) == 0){
        // If M[i][j] is null
        return;
    }

    row* rp = M -> head;
     while(1){
        // Gets the row before the one with index i
        if (rp -> next -> i == i || rp -> next -> next == NULL) break;
        else rp = rp -> next;
    }

    if (rp -> next -> head -> next -> next == NULL){
        // If the element is the only one in the row
        remove_row(M, i);
    }
    else{
        rp = rp -> next;
        remove_node(rp, j);
    }
}


int get(matrix* M, int i, int j){    
    row* rp = M -> head;
    while(rp -> i != i){
        if (rp -> i > i || rp -> next == NULL) return 0;
        else rp = rp -> next;
    }

    int elem;
    node* np = rp -> head;
    while(np != NULL){
        if (np -> j == j){
            elem = np -> data;
            return elem;
        }
        else if (np -> j > j) return 0;
        else np = np -> next;
    }
    
    return 0;
}
    

void print_matrix(matrix* M){
    if (M -> head -> next == NULL){
        printf("A matriz e' nula.\n");
    }
    else{
        printf("M: ");
        row* rp = M -> head -> next;
        while(rp != NULL){
            node* np = rp -> head -> next;
            while (np != NULL){
                printf("(%d,%d,%d) ", rp -> i, np -> j, np -> data);
                np = np -> next;
            }
            rp = rp -> next;
        }
        printf("\n");
    }
}
