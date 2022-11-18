
#include "list.h"

int countNumNodes(List l)
{
	int numNodes = 0; 
	List current = l->head; 

	while (current != NULL)
	{
		numNodes++; 
		current = current->next; 
	}
	return numNodes; 
}

bool listIsOrdered(List l) {
	// TODO
	// steps:
	// 1. loop through the list and check if the value of the next element 
	// is bigger than the previous one 
	List current = l->head;
	int counter = 0; 

	while (current != NULL)
	{
		if (current->value > current->next->value)
		{
			counter++; 
		}
		current = current->next; 
	}

	if (counter == countNumNodes(l))
	{
		return true; 
	}
	return false;
}

