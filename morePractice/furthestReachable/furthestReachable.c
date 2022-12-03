
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

static int doFurthestReachable(Graph g, int v, int *visited, int *pred, int numV)
{
	int count = 1; 
	int maxCount = 0; 
	for (int i = 0; i < numV; i++)
	{
		visited[v] = 1; 
		for (int j = 0; j < numV; j++)
		{
			if (GraphIsAdjacent(g, v, j) && visited[j] == 0)
			{
				visited[j] = 1; 
				pred[j] = v; 
				doFurthestReachable(g, j, visited, pred, numV); 
				count++;
			}
		}

		if (count >= maxCount)
		{
			maxCount = count; 
		}
	}

	return maxCount; 
}

int furthestReachable(Graph g, int src) {
	// TODO
	int *pred = malloc(sizeof(*pred)); 
	int numV = GraphNumVertices(g); 
	int *visited = calloc(numV, sizeof(int)); 

	for (int i = 0; i < numV; i++)
	{
		pred[i] = -1; 
	}
	pred[src] = src; 
	int furthestVertice = doFurthestReachable(g, src, visited, pred, numV); 
	return furthestVertice;
}

