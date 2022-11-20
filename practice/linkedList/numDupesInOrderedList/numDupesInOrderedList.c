
#include "list.h"



int numDupesInOrderedList(List l) 
{
	// TODO
	Node current = l->head; 
	if (current == NULL) return 0; 
	int counter = 0; 

	while (current->next != NULL)
	{
		if (current->value == current->next->value)
		{
			counter++; 
		}
		current = current->next; 
	}

	return counter; 
}

