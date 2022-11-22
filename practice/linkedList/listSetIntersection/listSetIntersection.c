
#include "list.h"

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

void prepend(List l, int value)
{
	Node new = newNode(value); 

	new->next = l->head; 
	l->head = new; 
}

List listSetIntersection(List s1, List s2) {
	// TODO
	List new = newList(); // create a new list 
	
	for (Node current = s1->head; current != NULL; current = current->next)
	{
		if (checkInList(s2, current->value))
		{
			prepend(new, current->value); 
		}
	}
	
	return new;
}

