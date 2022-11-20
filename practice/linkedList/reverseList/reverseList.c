
#include "list.h"

/*
	steps:
	1. iterate through the list until the tail, make the tail the head
	2. 
*/
void listReverse(List l) 
{
	// TODO
	// need to setup 3 pointers, current, previous and next 
	Node current = l->head; 
	Node previous = NULL; 
	Node next = NULL; 

	while (current != NULL)
	{
		next = current->next; 
		current->next = previous; 
		previous = current; 
		current = next; 
	}
	l->head = previous; 
}

