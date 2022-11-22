
#include "list.h"

void prepend(List l, int value)
{
	Node new = newNode(value); 

	new->next = l->head; 
	l->head = new; 
}

bool checkInList(List l, int value)
{
	for (Node current = l->head; current != NULL; current = current->next)
	{
		if (current->value == value)
		{
			return true; 
		}
	}
	return false; 
}

void listDelete(List l, int value)
{
	Node current = l->head; 
	Node previous = NULL; 

	while (current->value != value)
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
}
/*
	steps: loop through the first list 
*/
List listSetDifference(List l1, List l2) {
	// TODO
	List new = newList(); 

	for (Node current = l1->head; current != NULL; current = current->next)
	{
		prepend(new, current->value); 
	}
	
	for (Node current = l2->head; current != NULL; current = current->next)
	{
		if (checkInList(new, current->value))
		{
			listDelete(new, current->value); 
		}
	}

	return new;
}

