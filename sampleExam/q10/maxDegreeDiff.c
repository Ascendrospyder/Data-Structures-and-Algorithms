
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int maxDegreeDiff(Graph g) 
{
    // TODO
    if (g == NULL)
    {
        return 0; 
    }
    int numV = GraphNumVertices(g); 
    int *deg = calloc(numV, sizeof(int));

    for (Vertex i = 0; i < numV; i++)
    {
        for (AdjList current = g->edges[i]; current != NULL; current = current->next)
        {
            deg[i] = abs(deg[i] - deg[current->v]); 
            printf("ith inlink = %d\tcurrent outlink = %d\n", i, current->v); 
        }
    }

    int maxDeg = 0; 
    for (int i = 0; i < numV; i++)
    {
        if (deg[i] > maxDeg)
        {
            maxDeg = deg[i]; 
        }
    }
    free(deg); 
    return maxDeg; 
}



