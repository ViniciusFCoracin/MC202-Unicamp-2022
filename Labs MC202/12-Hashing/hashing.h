/*      hashing.h 

        Defines a hash table. It's elements are (key, value) pairs, both
    strings lesser than 250 characters. They also include timestamps
    that indicates when they were added to the table.

        The hash table uses double hashing and are resized when is 70% filled.

        If an position is empty, it can have the key "NONE" or "DELETED", depending
    if it had a deleted element or not. In that case, no memory is alocated for the 
    value field. If it's not empty, then the key and the value fields points to the
    same string, alocating memory only once.
*/

#ifndef HASH_TABLE
#define HASH_TABLE

// The elements of the hash table
typedef struct element{
    char* key;
    char* data;
    unsigned int timestamp;
} element;

// The hashtable itself
typedef struct hashtable{
    element* array;
    unsigned maxsize;
    unsigned num_elem;
} hashtable;

// First hashing function.
unsigned long hash1(char* str);

// Second hashing function.
unsigned long hash2(char* str);

// Inserts the element in the hash table. If it's already in the table,
// does nothing and returns zero. Else, returns 1.
int insert(hashtable* HT, char* data, unsigned int timestamp);

// Removes the element from the hashing table. If it's not in the table,
// does nothing and returns 0. Else, returns 1.
int delete_element(hashtable* HT, char* data);

// Searches the element. If it's not in the hashing table, returns -1.
// Else, returns it's index.
int search(hashtable* HT, char* data);

// Resizes the hashing table, doubling it's size.
hashtable* resize(hashtable* HT);

// Creates a hash table with "maxsize" size and returns a pointer to it.
hashtable* create_ht(unsigned maxsize);

// Free the memory used for the hashing table.
void free_ht(hashtable* HT);

#endif
