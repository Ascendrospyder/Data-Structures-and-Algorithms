#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Item; 

typedef HeapRep {
    Item *items; // since heaps utilise an array we need this 
    int num_items;  // with any kind of array in c we need to keep track of num_items
    int num_slots; // max size of the array 
} HeapRep; 

typedef HeapRep *Heap; 

Heap newHeap(int slots)
{
    Heap new = malloc(sizeof(HeapRep)); 
    Int *a = malloc((N + 1) * sizeof(Item)); 
    assert(new != NULL && a != NULL);

    new->items = a; 
    new->num_items = 0; 
    new->num_slots = slots;  
    return new; 
}
/**
 * @brief - This function will swap two items in an array 
 * 
 * @param a 
 * @param i 
 * @param j 
 */
void swap (int *a, int i, int j)
{
    Item temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
/**
 * @brief - This function will take and array and item, and place it in the
 * correct position in the heap by performing swaps 
 * 
 * @param a - Item array 
 * @param i - int 
 */
void fixup(Item *a, int i)
{
    while (i > 1 && a[i/2] < a[i])
    {
        swap(a, i, i/2); 
        i = i/2;
    }
}

void fixDown(Item *a, int i, int N)
{
    while (2 * i <= N)
    {
        int j = 2 * i; 

        if (j < N && a[j] < a[j + 1])
        {
            j++; 
        }

        if (a[j] > a[j + 1])
        {
            break; 
        }
        swap(a, i, j); 
        i = j; 
    }
}
/**
 * @brief - This function will insert an item into the heap and rearrange it
 * to the correct position in the heap.
 * 
 * @param h - Heap 
 * @param it - Item  
 */
void HeapInsert(Heap h, Item it) 
{
    assert(h->num_items < h->num_slots);
    // increase the number of items in the array if we call this function
    h->num_items++; 
    // add this item to the end of this array 
    h->items[h->num_items] = it;
    // move new item to the right position in the heap 
    fixup(h->items, h->num_items); 
}

void HeapDelete(Heap h)
{
    Item top = h->items[1]; // first element of the array (root node)

    //overwrite the root with with the last element of the array
    h->items[1] = h->items[h->num_items]; 
    h->num_items--;
    // adjust the heap correctly by fixing down the root 
    fixDown(h->items, 1, h->num_items); 

    return top; 
}

