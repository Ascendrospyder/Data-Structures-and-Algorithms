
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/*
	steps: 
	1. we need to keep track of a counter
	2. what we need to check if that node is adjacent to the src node 
*/
int doNumReachable(Graph g, Vertex v, int *visited, int numV)
{
	visited[v] = 1; 
	int count = 1; 
	for (Vertex w = 0; w < numV; w++)
	{
		if (GraphIsAdjacent(g, v, w) && !visited[w])
		{
			visited[w] = 1; 
			count += doNumReachable(g, w, visited, numV);
		}
	}
	return count; 
}
int numReachable(Graph g, int src) {
	// TODO
	if (g == NULL)
	{
		return 0; 
	}

	int *visited = calloc(GraphNumVertices(g), sizeof(int)); 

	int numV = GraphNumVertices(g); 
	int result = doNumReachable(g, src, visited, numV); 
	free(visited); 
	return result; 
}

