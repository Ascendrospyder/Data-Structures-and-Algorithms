#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "WGraph.h"

#define MAX_NODES 1000

bool visited[MAX_NODES];


/**
 * @brief - The following function will perform a dfs to check for potential cycles 
 * 
 * @param g - Graph 
 * @param nV - number of vertices 
 * @param v - First vertex 
 * @param u - Second vertex 
 * @return true - if there is a cycle 
 * @return false - if there isn't a cycle 
 */
bool dfsCycleCheck(Graph g, int nV, Vertex v, Vertex u) 
{
    visited[v] = true; // 
    for (Vertex w = 0; w < nV; w++) 
    {
        if (adjacent(g, v, w)) 
        {
           if (!visited[w])
           {
                return dfsCycleCheck(g, nV, w, v);
           } else if (w != u) {
                return true;
           }
        }
    } 
    return false;
}

/**
 * @brief - Kruskals algo follows simple rules: 
 * 1. sort the weights in order 
 * 2. add edges in that order and each time check for cycles 
 * 
 * 
 * @param g - Graph g
 * @param sortedEdges - sorted array of edge weights 
 * @param nV - number of vertices 
 * @param nE - number of edges 
 * @return Graph - new mst 
 */
Graph kruskal(Graph g, Edge sortedEdges[], int nV, int nE) 
{
    Graph mst = newGraph(nV); // create an empty graph for our mst 

    int n = 0; 
    for (int i = 0; i < nE && n < nV - 1; i++)
    {
        Edge e = sortedEdges[i]; // assume edges are already sorted? 
        insertEdge(mst, e); 
        n++; 

        // initialise everything in the visited array as false 
        for (Vertex v = 0; v < nV; v++) 
        {
            visited[v] = false; 
        }

        // if a cycle forms then remove the edge from the mst 
        if (dfsCycleCheck(mst, nV, e.v, e.v))
        {
            removeEdge(mst, e); 
            n--; 
        }
    }
    return mst; // return the mst at the end  
}

int main(void) {
   int nV = 5;
   Graph g = newGraph(nV);

   Edge edges[8];
   edges[0].v = 2; edges[0].w = 3; edges[0].weight = 1;
   edges[1].v = 0; edges[1].w = 2; edges[1].weight = 2;
   edges[2].v = 0; edges[2].w = 1; edges[2].weight = 3;
   edges[3].v = 1; edges[3].w = 2; edges[3].weight = 4;
   edges[4].v = 2; edges[4].w = 4; edges[4].weight = 5;
   edges[5].v = 1; edges[5].w = 4; edges[5].weight = 6;
   edges[6].v = 3; edges[6].w = 4; edges[6].weight = 7;
   edges[7].v = 0; edges[7].w = 3; edges[7].weight = 8;

   int i, nE = 8;
   for (i = 0; i < nE; i++) {
      insertEdge(g, edges[i]);
   }
   showGraph(g);
   
   Graph mst = kruskal(g, edges, nV, nE);
   showGraph(mst);
   freeGraph(mst);
   freeGraph(g);

   return 0;
}
