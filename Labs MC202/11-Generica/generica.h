/*
  generic.h
  Declaration for a linked list with guards in the beggining,
  using one struct for the nodes and another one for the list.
  The content of the nodes can be of types int, float, char or strings.
*/


#ifndef GENERIC
#define GENERIC

typedef enum {
    CHAR,
    INT,
    FLOAT,
    STR
} Type;

typedef union {
        float f;
        char c;
        char* s;
        int i;
} Data;

typedef struct Node{
    Type type; // The type of the data
    Data data;  // The data to be stored
    struct Node* next;   // A pointer to the next element
} Node;

typedef struct{
    Node* head;  // A pointer to the first element of the list
} List;


/* Create an empty list and returns a pointer to it. */
List* create_list(void);

/* Free the memory used for a list and it's nodes. */
void free_list(List* L);

/* Adds an element in the end of the list.
   If it is successful, returns 1, else, returns 0. */
int push(List* L, Type type, Data data);

/* Prints the elements of the list in order. */
void print_list(List* L);

/* Reverses the elements of the list, starting in the
index i and stoping in the index j, including these. */
void reverse(List* L, int i, int j);

/* Transposes the sublist from indexes i to j to the
right of the position of index k. If k == -1, so the 
sublist is transposed to the start of the list L. */
void transpose(List* L, int i, int j, int k);

#endif
