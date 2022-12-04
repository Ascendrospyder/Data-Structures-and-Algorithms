
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"


static bool doHasCycle(Graph g, int v, int prev, bool *visited); 
// Worst case time complexity of this solution: O(...)
/*
    steps: 
    1. 
*/ 
void nodesNotInCycle(Graph g, int notInCycle[]) 
{
    bool *visited = calloc(GraphNumVertices(g), sizeof(bool)); 

    // for each vertice of the graph if it does form a cycle then mark that vertice in the array as visited   
    for (int i = 0; i < GraphNumVertices(g); i++)
    {
        if (doHasCycle(g, i, i, visited))   
        {
            notInCycle[i] = 0;  
        } else {
            notInCycle[i] = 1; 
        }
    }
    free(visited); 
}

static bool doHasCycle(Graph g, int v, int prev, bool *visited) {
	visited[v] = true; 
	for (int w = 0; w < GraphNumVertices(g); w++) 
    {  
		if (GraphIsAdjacent(g, v, w)) 
        {                     
			if (visited[w]) // if the vertex has been visited and it isnt the previous node mark it as true 
            {
				if (w != prev)  
                {
					return true;
				}
			} else {
				if (doHasCycle(g, w, v, visited)) {
					return true;
				}
			}
		}
	}
	return false;
}



