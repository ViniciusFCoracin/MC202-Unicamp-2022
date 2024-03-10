/*
    lol.h
    Declarations for a sparse matrix, implemented as linked lists
*/

#ifndef LOL_H
#define LOL_H

typedef struct node{
    struct node* next;
    int j;
    int data;
}node;

typedef struct row{
    struct row* next;
    struct node* head;
    int i;
}row;

typedef struct matrix{
    struct row* head;
}matrix;


/* Create a new matrix with sentinel row and sentinel node.
   If there is already a matrix in the memory, it firsts free
   the previous one. */
matrix* create_matrix(matrix* M);

/* Free the matrix. */
void free_matrix(matrix* M);

/* Creates a new row with sentinel node and returns it's pointer. */
row* create_row(matrix* M, int i);

/* Creates a new node and returns it's pointer. */
node* create_node(row* R, int j, int x);

/* Removes the row with index i of the matrix. A row with index i
   must exists. */
void remove_row(matrix* M, int i);

/* Removes the node of index j of the specified row. A node with
   index j must exists. */
void remove_node(row* R, int j);

/* Writes or rewrites the element M[i][j] with the element x. */
void set(matrix* M, int x, int i, int j);

/* Removes the element M[i][j] from the matrix. */
void set_zero(matrix* M, int i, int j);

/* Gets the element M[i][j] from the matrix. If it's not specified,
   then it's zero.*/
int get(matrix* M, int i, int j);

/* Prints the elements of the matrix in index order. */
void print_matrix(matrix* M);

#endif
