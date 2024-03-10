/*
    heap.h 
    Define a min heap, using an array.
    The heap must be dense and continous.
    The elements are pairs (key, value), both integers.
*/

#ifndef HEAP
#define HEAP

// The elements in the heap
typedef struct element{
    int key;
    int value;
} element;

// Return the parent's index of the element in the "index" position.
int parent(int index);

// Return the left son's index of the element in the "index" position.
int left(int index);

// Return the right son's index of the element in the "index" position.
int right(int index);

// Heapify up the heap. Used to insert elements in the heap.
void heapify_up(element** heap, int* array, int index);

// Heapify down the heap. Used to pop and alter the value of an element.
void heapify_down(element** heap, int heap_size, int* array, int index);

// Insert the element (key, value) in the heap. If the element is 
// already in the heap, does nothing.
void insert(element** heap, int* heap_size, int* array, int key, int value);

// Pop the min element in the heap and prints it. If two elements
// are equal in value, the key is used to decide which is smaller.
// If the heap is empty, prints an "Empty heap" message.
void pop(element** heap, int* heap_size, int* array);

// Alter the value of the element with a given key. If it's not in the 
// array, returns. The new value must be always lesser than the old one.
void alter_value(element** heap, int* array, int key, int value);

// Free the used memory.
void free_heap(element** heap, int heap_size);

// Create a heap and returns a pointer to it.
element** create_heap(int heap_size);

// Create an auxiliary array, which the element in the index i is the position
// of the element with key i in the heap. If the element with key i isn't in the
// heap, so array[i] is equal to INT_MAX. 
int* create_array(int array_size);

// Free the memory used for the auxiliary array.
void free_array(int* array);

#endif
