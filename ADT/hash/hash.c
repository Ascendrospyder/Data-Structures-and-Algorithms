#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hash.h"

typedef struct HashTabRep {
    Item **items; // array of Item *
    int size; //size of the array (MAX elements )
    int num_items; 
} HashTabRep;

int hash(Key k, int size)
{
    int h = 0, a = 31415, b = 21783; 
    char *c; 

    for (c = key; *c != '\0'; c++)
    {
        a = a * b % (size - 1); 
        h = (a * h + *c) % size; 
    }
    return h; 
}
 
/**
 * @brief - This function will create a new hashtable 
 * 
 * @param size_array - size of the given array 
 * @return HashTable - new HashTable
 */
HashTable newHashTable(int size_array)
{
    HashTable new = malloc(sizeof(HashTabRep)); // create a new hashtable and malloc some memory 

    // fill in the information for the struct
    new->items = malloc(size_array * sizeof(Item *)); // for the array, malloc space for size * size(Item *)
    new->size = size_array; 
    new->num_items = 0; 

    // loop through the whole items array and initialise everything to NULL
    for (int i = 0; i < size_array; i++)
    {
        new->items[i] = NULL;
    }
    return new; // return the new HashTable 
}

/**
 * @brief - This function will insert an item into the HashTable
 * 
 * @param h - hashtable of interest 
 * @param it - item to insert
 */
void HashInsert(HashTable h, Item it)
{
    int hash = hash(key(it), h->size); // converts the string into a numerical index

    h->items[hash] = it; // assigning a copy of the item into that index 
    h->num_items++; // increasing the size of the hashTable by 1 
}

/**
 * @brief - Given a hashtable and its key find the index and assign the value to that index into a new Item *pointer 
 * 
 * @param h - hashtable
 * @param k - key 
 * @return Item* 
 */
Item *HashGet(HashTable h, Key k)
{
    int hash = hash(k, h->size); // find the index in which item is located 

    Item *item_pointer = h->items[hash]; // then we get the value of the item in that index

    if (item_pointer != NULL && (key(*item_pointer) == k)) // if the item pointer isn't empty and is same as the key then return it ez 
    {
        return item_pointer;
    } else {
        return NULL; 
    }
}
/**
 * @brief - This function will remove a key from a hashtable by first finding its index and then freeing the value and resetting the position to NULL 
 * 
 * @param h - hashTable 
 * @param k - key 
 */
void HashDelete(HashTable h, Key k)
{
    int hash = hash(k, h->size); // find the index of they key we wish to delete 
    Item *item_pointer = h->items[hash]; // get that particular value in that index 

    if (item_pointer != NULL && (key(*item_pointer) == k)) // 
    {
        free(item_pointer); // free the value 
        h->items[hash] = NULL; // set the index as NULL
        h->num_items--; // decrease size of num_items
    }
}
/**
 * @brief - This function will free the hashtable
 * 
 * @param h - hash table
 */
void dropHashTable(HashTable h)
{
    for (int i = 0; i < h->size; i++) // loop through every element in the items array and free it
    {
        if (h->items[i] != NULL) free(h->items[i]);
    }
    free(h); // then free the hashtable itself 
}
