
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int visited[1000]; 

static void dfsPathCheck(Graph g, int numV, Vertex v, int *visited); 

void depthFirstSearch(Graph g, int src) {
	// TODO
	int nV = GraphNumVertices(g);
	int *visited = calloc(nV, sizeof(int)); 

	dfsPathCheck(g, nV, src, visited); 

	free(visited); 
}


static void dfsPathCheck(Graph g, int numV, Vertex v, int *visited)
{
	printf("%d ", v); 
	visited[v] = 1; 
	for (Vertex w = 0; w < numV; w++)
	{
		if (GraphIsAdjacent(g, v, w) && !visited[w])
		{
			dfsPathCheck(g, numV, w, visited); 
		}
	}
}


