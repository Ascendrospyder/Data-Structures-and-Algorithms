#include <stdio.h>
#include <stdbool.h>
#include "graph.h"
#include "list.h"

#define MAX_NODES 1000

int visited[MAX_NODES];  // array to store visiting order
                         // indexed by vertex 0..nV-1

int countReachableR(Graph g, int nV, Vertex v)
{
	visited[v] = 1;
	int total = 1; 

	for (Vertex w = 0; w < nV; w++)
	{
		if (GraphAdjacent(g, v, w) && visited[v] == -1)
        {
            int count = countReachableR(g, nV, w); 
            total += count; 
        }
	}
    return total; 
}

bool dfsPathCheck(Graph g, int nV, Vertex v, Vertex dest) 
{
	for (Vertex w = 0; w < nV; w++)
	{
		if (GraphAdjacent(g, v, w) && visited[w] == -1) 
		{
			visited[w] = v;
			if (w == dest)
			{
				return true;
			} else if (dfsPathCheck(g, nV, w, dest)) { // recursive call here introduces the concept of backtracking 
				return true;
			}
		}
	}
   return false;
}

bool findPathDFS(Graph g, int nV, Vertex src, Vertex dest) 
{
	for (Vertex v = 0; v < nV; v++)
	{
		visited[v] = -1;
	}
	visited[src] = src;
	return dfsPathCheck(g, nV, src, dest);
}

int main(void) 
{
	int V = 6;
	Graph g = GraphNew(V);	
	Edge e;
	e.v = 0; e.w = 1; GraphEdgeInsert(g, e);
	e.v = 0; e.w = 4; GraphEdgeInsert(g, e);
	e.v = 0; e.w = 5; GraphEdgeInsert(g, e);
	e.v = 5; e.w = 4; GraphEdgeInsert(g, e);
	e.v = 4; e.w = 2; GraphEdgeInsert(g, e);
	e.v = 4; e.w = 3; GraphEdgeInsert(g, e);
	e.v = 5; e.w = 3; GraphEdgeInsert(g, e);
	e.v = 1; e.w = 2; GraphEdgeInsert(g, e);
	e.v = 3; e.w = 2; GraphEdgeInsert(g, e);	
	int src = 0, dest = 5;
	if (findPathDFS(g, V, src, dest)) 
	{
		Vertex v = dest;
		while (v != src) 
		{
			printf("%d - ", v);
			v = visited[v];
		}
		printf("%d\n", src);	
	}
	return 0;
}
