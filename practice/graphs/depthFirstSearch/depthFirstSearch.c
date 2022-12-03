
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void dfsPathCheck(Graph g, int nV, Vertex v, int *visited); 

void depthFirstSearch(Graph g, int src) 
{
	// TODO
	int *visited = calloc(GraphNumVertices(g), sizeof(int)); 
	visited[src] = src;
	printf("%d ", src);
	dfsPathCheck(g, GraphNumVertices(g), src, visited); 
	free(visited); 
}

void dfsPathCheck(Graph g, int nV, Vertex v, int *visited) 
{
	for (Vertex w = 0; w < nV; w++)
	{
		visited[v] = 1;  
		if (GraphIsAdjacent(g, v, w) && visited[w] == 0)
		{
			visited[w] = 1; 
			printf("%d ", w); 
			dfsPathCheck(g, nV, w, visited); 
		}
	}
}

