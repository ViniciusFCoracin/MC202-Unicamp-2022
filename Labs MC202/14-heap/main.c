#include <stdio.h>
#include "heap.h"

int main(void){
    element** heap = NULL;
    int* array = NULL;
    int heap_size = -1;
    
    char input;
    scanf(" %c", &input);

    while (input != 't'){
        if (input == 'c'){
            if (heap != NULL){
                free_heap(heap, heap_size);
                free_array(array);
                heap_size = 0;
            }

            int heap_maxlen;
            scanf("%d", &heap_maxlen);
            heap = create_heap(heap_maxlen);
            array = create_array(heap_maxlen);
        }
        else if (input == 'i'){
            int key, value;
            scanf("%d %d", &key, &value);
            insert(heap, &heap_size, array, key, value);     
        }
        else if (input == 'm'){
            pop(heap, &heap_size, array);
        }
        else if (input == 'd'){
            int key, value;
            scanf("%d %d", &key, &value);
            alter_value(heap, array, key, value);
        }

        scanf(" %c", &input);
    }
    free_heap(heap, heap_size);

    return 0;
}
