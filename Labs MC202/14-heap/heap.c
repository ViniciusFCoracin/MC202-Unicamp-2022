#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "heap.h"

int parent(int index){
    return (index - 1)/ 2;
}

int left(int index){
    return index * 2 + 1;
}

int right(int index){
    return (index + 1) * 2;
}

void heapify_up(element** heap, int* array, int index){
    if (index == 0) return;

    int dad = parent(index);
    if (heap[dad] -> value > heap[index] -> value ||
    (heap[dad] -> value == heap[index] -> value && heap[dad] -> key > heap[index] -> key)){
        array[heap[dad] -> key] = index;
        array[heap[index] -> key] = dad;
        
        element* aux = heap[dad];
        heap[dad] = heap[index];
        heap[index] = aux;
    }

    heapify_up(heap, array, dad);

}

void heapify_down(element** heap, int heap_size, int* array, int index){
    int rson = right(index);
    int lson = left(index);
    int smallest = index;

    if (rson < heap_size && (heap[rson] -> value <= heap[index] -> value ||
    (heap[rson] -> value == heap[index] -> value && heap[rson] -> key < heap[index] -> key))){
        smallest = rson;
    }
    if (lson < heap_size && (heap[lson] -> value <= heap[smallest] -> value ||
    (heap[lson] -> value == heap[smallest] -> value && heap[lson] -> key < heap[smallest] -> key))){
        smallest = lson;
    }

    if (smallest != index){
        array[heap[index] -> key] = smallest;
        array[heap[smallest] -> key] = index;

        element* aux = heap[smallest];
        heap[smallest] = heap[index];
        heap[index] = aux;
        heapify_down(heap, heap_size, array, smallest);
    }
}

void insert(element** heap, int* heap_size, int* array, int key, int value){
    if (array[key]!= INT_MAX) return;

    element* new_element = (element*) malloc(sizeof(element));
    if (new_element){
        new_element -> key = key;
        new_element -> value = value;
        array[key] = ++(*heap_size);
        heap[*heap_size] = new_element;
        heapify_up(heap, array, *heap_size);
    } 
}

void pop(element** heap, int* heap_size, int* array){
    if (*heap_size == -1){
        printf("heap vazio\n");
        return;
    }

    printf("minimo {%d,%d}\n", heap[0] -> key, heap[0] -> value);
    element* aux = heap[0];
    heap[0] = heap[*heap_size];
    heap[*heap_size] = aux;

    heapify_down(heap, *heap_size, array, 0);
    array[heap[*heap_size] -> key] = INT_MAX;
    (*heap_size)--;
}

void alter_value(element** heap, int* array, int key, int value){
    if (array[key] == INT_MAX) return;

    heap[array[key]] -> value = value;
    heapify_up(heap, array, array[key]);
}

void free_heap(element** heap, int heap_size){
    for (int i = 0; i <= heap_size; i++){
        free(heap[i]);
    }
    free(heap);
}

element** create_heap(int heap_size){
    element** heap = (element**) malloc(sizeof(element*) * (unsigned) heap_size);
    return heap;
}

int* create_array(int array_size){
    int* array = (int*) malloc((unsigned) array_size * sizeof(int));
    for (int i = 0; i < array_size; i++){
        array[i] = INT_MAX;
    }
    return array;
}

void free_array(int* array){
    free(array);
}
