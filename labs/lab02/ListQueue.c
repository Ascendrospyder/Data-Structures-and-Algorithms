// Implementation of the Queue ADT using a linked list

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

typedef struct node *Node;
struct node {
	Item item;
	Node next;
};

struct queue {
	Node head;
	Node tail;
	int  size;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}

	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	Node curr = q->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(q);
}
static Node new_node(Item it)
{
	Node new = malloc(sizeof(*new)); 

	if (new == NULL)
	{
		fprintf(stderr, "Error, failed to malloc\n"); 
		exit(EXIT_FAILURE); 
	}

	new->item = it; 
	new->next = NULL; 
	return new; 
}
/**
 * Adds an item to the end of the queue
 * steps: 
 */
void QueueEnqueue(Queue q, Item it) {
	// TODO
	assert(q != NULL);
	// make a new node by mallocing some space 
	Node new = new_node(it); 

	// if the queues size is 0 then the head should point to the new node
	if (q->size == 0)
	{
		q->head = new; 
	} else 
	{
		q->tail->next = new; // assign new node to the end of the queue
	}
	// let q's tail now point to our new node
	q->tail = new; 
	q->size++; // increment the size of the queue by one as we added an element 
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	// TODO
	assert(q != NULL && q->size > 0); // throw errors in terminal if any of the conditions fail 
	Node current_head = q->head->next; // our new head should now point to the next element from the head            
	Item it = q->head->item; // access the item we want to remove 

	// remove the head of the original queue
	free(q->head); 

	// make the q->head->next as our new head and decrement the size by 1 each time
	q->head = current_head; 
	q->size--; 
	return it; 
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);

	return q->head->item;
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
	for (Node curr = q->head; curr != NULL; curr = curr->next) {
		fprintf(fp, "%d ", curr->item);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q) {
	Node current = q->head; 

	while (current != NULL)
	{
		printf("%d ", current->item); 
		current = current->next; 
	}
	printf("\n"); 
}

