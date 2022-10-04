// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	// TODO
	// We add elements of a Queue in the back, when there are 
	// more elements that then array's size, we circle back to the first index 
	// and elements to the queue creating a cyclical structure 
	assert(q != NULL); 
	int index = q->frontIndex + q->size; // calculate the index 

	if (index % q->capacity == q->frontIndex) // if the remainder of the index and the Queue's capacity is the front index, then go ahead
	{
		q->items = realloc(q->items, 2 * q->capacity * sizeof(int)); // increase the capacity of the queue 

		int i = q->capacity; 
		int j = 0; 
	
		while (i < (q->frontIndex + q->capacity))
		{
			q->items[i] = q->items[j]; 
			i++; 
			j++; 
		} 
		q->items[index] = it; 
		q->size++; 
		q->capacity = 2 * q->capacity; 	
	} else {
		q->items[(index) % q->capacity] = it; 
		q->size++; 
	}
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	// TODO
	Item current = q->items[q->frontIndex]; 
	q->frontIndex = (q->frontIndex + 1) % q->capacity; 
	q->size--; 

	return current; 
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the items in the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {

}

