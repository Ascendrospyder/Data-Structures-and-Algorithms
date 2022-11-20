
#include "list.h"

int countNumNodes(List l)
{
	int numNodes = 0; 
	Node current = l->head; 

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
	
	Node currentAscending = l->head;
	Node currentDescending = l->head; 
	if (currentAscending == NULL || currentDescending == NULL) return true; 
	int counterAscending = 0; 
	int counterDescending = 0; 
	int numNodes = countNumNodes(l); 
	// printf("num nodes = %d\n", numNodes); 

	
	while (currentAscending->next != NULL)
	{
		if (currentAscending->value <= currentAscending->next->value)
		{
			counterAscending++; 
		}
		// printf("currentAscending = %d\tcurrentAscending next = %d\tcounterAscending = %d\n", currentAscending->value, currentAscending->next->value, counterAscending);
		currentAscending = currentAscending->next; 
	}

	while (currentDescending->next != NULL)
	{
		if (currentDescending->value > currentDescending->next->value)
		{
			counterDescending++; 
		}
		// printf("currentDescending = %d\tcurrentDescending next = %d\tcounterAscending = %d\n", currentDescending->value, currentDescending->next->value, counterDescending);
		currentDescending = currentDescending->next; 
	}
	

	if (counterAscending == numNodes - 1 || counterDescending == numNodes - 1)
	{
		return true; 
	} 
	return false; 
}

