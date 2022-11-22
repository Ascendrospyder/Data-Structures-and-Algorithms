
#include "list.h"

int countNodes(List l)
{
	int counter = 0; 
	for (Node current = l->first; current != NULL; current = current->next)
	{
		counter++; 
	}
	return counter; 
}
/*
	steps:
	1. step through the start to the end of the list and compare the value with 
	the last to first 
*/
bool listIsPalindromic(List l) {
	// TODO
	int counter = 0; 
	Node start = l->first; 
	Node end = l->last; 
	while (start != NULL && end != NULL)
	{
		if (start->value == end->value)
		{
			counter++; 
		}	
		start = start->next; 
		end = end->prev; 
	}


	if (counter == countNodes(l))
	{
		return true; 
	} else {
		return false;
	}

}

