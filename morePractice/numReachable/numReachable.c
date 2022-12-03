
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int doNumReachable(Graph g, int v, int *visited, int numV)
{
	int count = 1; 
	for (int i = 0; i < numV; i++)
	{
		visited[v] = 1; 
		for (int j = 0; j < numV; j++)
		{
			if (GraphIsAdjacent(g, v, j) && visited[j] == 0)
			{
				visited[j] = 1; 
				count += doNumReachable(g, j, visited, numV); 
			}
		}
	}
	return count; 
}

int numReachable(Graph g, int src) {
	// TODO
	int numV = GraphNumVertices(g); 
	int *visited = calloc(numV, sizeof(int)); 
	int result = doNumReachable(g, src, visited, numV);
	free(visited); 
	return result;
}

