#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "dequef.h"

int resize(dequef* D, int r);


/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/
dequef* df_alloc(long capacity, double factor) {
   dequef* D;
   D = (dequef*) malloc(sizeof(dequef));

   if (D == NULL){
      return NULL;
   }
   else{
      float* data_array = (float*) malloc((unsigned) capacity * sizeof(float));

      D -> data = data_array;
      D -> first = 0l;
      D -> size = 0l;
      D -> cap = capacity;
      D -> mincap = capacity;
      D -> factor = factor;
   }

   return D;
}



/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
   free(D -> data);
   free(D);
}



/**
   The size of the deque.
**/
long df_size(dequef* D) {
   return D -> size;
}



/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
   if (D -> size == 0){  // if the array is empty
      D -> data[0] = x;
      D -> size = 1;
      D -> first = 0;
      return 1;
   }
   else if (D -> size == D -> cap){  // if the array is full
      int ans = resize(D, 1);
      if (ans == 0) return 0;
   }
   
   long next = (D -> size + D -> first) % D -> cap; // index of the new element
   D -> data[next] = x;  // add the new element to the array
   D -> size++;
   return 1;
}



/**
   Remove a float from the end of D.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_pop(dequef* D) {
   if (D -> size == 0){  // if the array is empty
      return 0.0;
   }

   long last = D -> first + D -> size - 1;  // pops the last element
   if (last >= D -> size){
      last %= D -> size;
   }
   D -> size--;

   long min_size = (long) (D -> cap / (D -> factor * D -> factor));  // resizes the array
   if (D -> size <= min_size && min_size >= D -> mincap){
      resize(D, -1);
   }

   return D -> data[last];
}



/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
   if (D -> size == 0){  // if the array is empty
      D -> data[0] = x;
      D -> size = 1;
      D -> first = 0;
      return 1;
   }
   else if (D -> size == D -> cap){  // if the array is full
      int ans = resize(D, 1);
      if (ans == 0) return 0;
   }

   long index = D -> first - 1;  //gets the index of the new element
   if (index < 0){
      index = D -> cap - 1;
   }

   D -> data[index] = x;  // places the new element
   D -> size++;
   D -> first = index;

   return 1;
}



/**
   Remove a float from the beginning of D.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_eject(dequef* D) {
   if (D -> size == 0){  // if the array is empty
      return 0.0;
   }

   float element = D -> data[D -> first];  // gets the first element
   
   D -> size--;  // ejects it
   D -> first++;
   if (D -> first >= D -> cap){
      D -> first = 0;
   }

   long min_size = (long) (D -> cap / (D -> factor * D -> factor));  // resizes the array
   if (D -> size <= min_size && min_size >= D -> mincap){
      resize(D, -1);
   }   

   return element;
}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] then D remains unchanged.
**/
void df_set(dequef* D, long i, float x) {
   if (i < D -> size){
      long index = D -> first + i;
      if (index >= D -> cap){
         index %= D -> cap;
      }
      D -> data[index] = x;
   }
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] it returns 0.0.
**/
float df_get(dequef* D, long i) {
   if (i >= D -> size){
      return 0.0;
   }
   else{
      long index = D -> first + i;
      if (index >= D -> cap){
         index %= D -> cap;
      }
      return D -> data[index];
   }
}



/**
   Print the elements of D in a line.
**/
void df_print(dequef* D) {
   printf("deque (%ld): ", D -> size);
   for (long i = 0; i < D -> size; i++){
      long index = D -> first + i;
      if (index >= D -> size){
         index %= D -> cap;
      }
      printf("%.1f ", D -> data[index]);
   }
   printf("\n");
}



/*
   Resize the data array.
   if the int r is higher than 0, than the array will increase it´s size.
   if it´s less than 0, than the array will shrinks it´s size.

   If the resizing was successful, it returns 1. Else, it returns 0.
*/
int resize(dequef* D, int r){
   float* new_data;

   if (r > 0){
      // Expands the array
      new_data = (float*) malloc(((unsigned long) (D -> cap * D -> factor) + 1) * sizeof(float));
      if (new_data == NULL){
         return 0;
      }
   }
   else{
      // Shrinks the array
      new_data = (float*) malloc(((unsigned long) (D -> cap / D -> factor) + 1) * sizeof(float));
      if (new_data == NULL){
         return 0;
      }
   }

   // Copy the elements to the new array.
   for (long i = 0; i < D -> size; i++){
      long index = D -> first + i;
      if (index >= D -> size){
         index = index % D -> cap;
      }
      new_data[i] = D -> data[index];
   }

   free(D -> data);
   D -> data = new_data;
   D -> first = 0;
   D -> cap = (long) ((r > 0)? D -> cap * D -> factor : D -> cap / D -> factor);

   return 1;
} 
