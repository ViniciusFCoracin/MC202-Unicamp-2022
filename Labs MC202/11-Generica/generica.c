#include <stdio.h>
#include <stdlib.h>
#include "generica.h"


List* create_list(void){
    List* new_list = (List*) malloc(sizeof(List));
    Node* guard = (Node*) malloc(sizeof(Node));
    guard -> next = NULL;
    new_list -> head = guard;

    return new_list;
}


void free_list(List* L){
    Node* np = L -> head;
    while (np != NULL){
        Node* aux = np -> next;
        if (np -> type == STR) free(np -> data.s);
        free(np);
        np = aux;
    }
    free(L);
}


int push(List* L, Type type, Data data){
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL){
        return 0;
    }
    new_node -> next = NULL;
    new_node -> type = type;
    if (type == CHAR){
        new_node -> data.c = data.c;
    }
    else if (type == INT){
        new_node -> data.i = data.i;
    }
    else if (type == FLOAT){
        new_node -> data.f = data.f;
    }
    else if (type == STR){
        new_node -> data.s = data.s;
    }

    Node* np = L -> head;
    while (np -> next != NULL){
        np = np -> next;
    }
    np -> next = new_node;
    
    return 1;
}


void print_list(List* L){
    Node* np = L -> head -> next;
    while (np != NULL){
        if (np -> type == CHAR) printf("%c ", np -> data.c);
        else if (np -> type == INT) printf("%d ", np -> data.i);
        else if (np -> type == FLOAT) printf("%.4f ", np -> data.f);
        else if (np -> type == STR) printf("%s ", np -> data.s);
        np = np -> next;
    }
    printf("\n");
}


void reverse(List* L, int i, int j){
    if (i >= j || L -> head -> next == NULL) return;

    Node* np = L -> head;
    Node* before_first;  // The element before the first reverted

    // Stops one before the first
    for (int n = -1; n < i - 1; n++){
        np = np -> next;
    }
    before_first = np;

    for (int n = i - 1; n < j; n++){
        np = np -> next;
    }
    Node* last = np;  // Finds the last element to be reverted
    Node* after_last = np -> next;  // Finds the element after the last

    int last_index = j;
    while (last_index != i){
        np = before_first;
        for (int n = i - 1; n < last_index - 1; n++){
            np = np -> next; 
        }
        np -> next -> next = np;
        last_index--;
    }
    before_first -> next -> next = after_last;
    before_first -> next = last;
}


void transpose(List* L, int i, int j, int k){
    if (i > j || k + 1 == i) return;
    
    // if more than one node will be transposed
    if (i != j){
        Node* np = L -> head;
        Node* index_k, *after_index_k;
        Node* start, *end;
        Node* before_start, *after_end;
        index_k = after_index_k = start = end = before_start = after_end = NULL;

        for (int n = -1; (n <= j && j > k) || (n <= k && k > j); n++, np = np -> next){
            if (n == k){
                index_k = np;  // Saves the node at index k
                after_index_k = np -> next;  // Saves the next node
            } 
            else if (n == i - 1){
                before_start = np;  // Saves the node before the first to be transposed
                start = np -> next;  // Saves the first node to be transposed
            }
            else if (n == j){
                end = np;  // Saves the last node to be transposed
                after_end = np -> next;  // Saves the next node
            }
        }

        index_k -> next = start;
        end -> next = after_index_k;
        before_start -> next = after_end;
    }
    // If just one node will be transposed
    else{
        Node* np = L -> head;
        Node* index_k, *after_index_k;
        Node* element;
        Node* before_start, *after_end;
        index_k = after_index_k = element = before_start = after_end = NULL;

        for (int n = -1; (n <= j && j > k) || (n <= k && k > j); n++, np = np -> next){
            if (n == k){
                index_k = np;  // Saves the node at index k
                after_index_k = np -> next;  // Saves the next one
            } 
            else if (n == i - 1){
                before_start = np;  // Saves the node before the one to be transposed
                element = np -> next;  // Saves the node that will be transposed
                after_end = np -> next -> next;  // Saves the next one
            }
        }

        index_k -> next = element;
        element -> next = after_index_k;
        before_start -> next = after_end;
    }
}
