
#include "list.h"

int findHighest(List l)
{
	Node current = l->head;
	Node largest = NULL;  
	largest = current; 

	// loop through the list first time and find the largest value 
	while (current != NULL)
	{
		if (current->value > largest->value)
		{
			largest = current; 
		}  
		current = current->next; 
	}

	int result = largest->value; 
	return result; 
}
/*
	steps: 
	1. go through the list 
*/
int listDeleteLargest(List l) 
{
	int highest = findHighest(l); 
	// printf("highest = %d\n", highest->value); 
	Node previous = NULL; 
	Node current = l->head; 

	// the following code keeps sets a previous node until it reaches 
	// the largest value of interest 
	while (current->value != highest)
	{
		previous = current; 
		current = current->next; 
	}

	if (current == l->head)
	{
		l->head = current->next; 
	} else {
		previous->next = current->next; 
	}
	
	free(current);  
	return highest; 
}

