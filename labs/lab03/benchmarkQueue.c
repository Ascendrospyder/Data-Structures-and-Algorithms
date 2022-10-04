
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

int main(void) {
	Queue q = QueueNew();

	// TODO
	// Write a benchmark test to demonstrate the difference in
	// efficiency between ArrayQueue and CircularArrayQueue
	for (int i = 1; i <= 150000; i++)
	{
		QueueEnqueue(q, i);
	}

	for (int i = 150001, j = 1; i <= 250000; i++, j++)
	{
		QueueEnqueue(q, i);
		QueueDequeue(q); 
	}
	QueueFree(q);
}

/*
Paste the results of the time commands here:



*/

