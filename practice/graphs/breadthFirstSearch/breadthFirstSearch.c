
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	// TODO
	int *visited = calloc(GraphNumVertices(g), sizeof(int));
	if (visited == NULL)
	{
		fprintf(stderr, "Failed to malloc!\n"); 
		exit(EXIT_FAILURE); 
	}

	visited[src] = src; 
	Queue q = QueueNew(); 
	
	QueueEnqueue(q, src); 
	printf("%d ", src); 
	while (!QueueIsEmpty(q))
	{
		Vertex v = QueueDequeue(q);
		visited[v] = 1; 
		for (Vertex w = 0; w < GraphNumVertices(g); w++)
		{
			if (GraphIsAdjacent(g, v, w) && visited[w] == 0)
			{
				visited[w] = 1; 
				printf("%d ", w); 
				QueueEnqueue(q, w); 
			}
		}
	}

	QueueFree(q); 
	free(visited); 
}

