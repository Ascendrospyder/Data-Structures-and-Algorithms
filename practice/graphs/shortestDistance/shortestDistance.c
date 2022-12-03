
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

#define MAX 1000

int shortestDistance(Graph g, int src, int dest) {
	// TODO
	int pred[MAX];  	
	for (int i = 0; i < GraphNumVertices(g); i++)
	{
		pred[i] = -1; 
	}
	
	if (pred == NULL)
	{
		fprintf(stderr, "Failed to malloc memory!\n"); 
		exit(EXIT_FAILURE); 
	}

	pred[src] = src; 
	bool found = false; 

	Queue q = QueueNew(); 
	QueueEnqueue(q, src); 
	
	while (found == false && !QueueIsEmpty(q))
	{
		Vertex v = QueueDequeue(q);
		for (Vertex w = 0; w < GraphNumVertices(g); w++)
		{
			if (GraphIsAdjacent(g, v, w) && pred[w] == -1)
			{
				pred[w] = v; 
				if (w == dest)
				{
					found = true;
				} 
				QueueEnqueue(q, w);  
			}
		}
	}

	QueueFree(q); 
	
	// if we haven't reached the destination, mark it as not pred 
	if (pred[dest] == -1)
	{
		return -1; 
	}

	int distance = 0;
	Vertex curr = dest;
	while (curr != src) {
		printf("distance = %d\tcurrent = %d\n", distance, curr); 
		distance++;
		curr = pred[curr];
	}
	return distance; 
}

