// Weighted Graph ADT
// Adjacency Matrix Representation ... COMP2521 
// the following code was adapted from the lecture slide code 
#include "graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



typedef struct GraphRep 
{
   int **edges;  // adjacency matrix storing positive weights
		 // 0 if nodes not adjacent
   int nV;       // #vertices
   int nE;       // #edges
} GraphRep;

Graph newGraph(int V) 
{
   assert(V >= 0);
   int i;

   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = V;
   g->nE = 0;

   // allocate memory for each row
   g->edges = malloc(V * sizeof(int *));
   assert(g->edges != NULL);
   // allocate memory for each column and initialise with 0
   for (i = 0; i < V; i++) {
      g->edges[i] = calloc(V, sizeof(int));
      assert(g->edges[i] != NULL);
   }
   
   return g;
}

// check if vertex is valid in a graph
int validV(Graph g, Vertex v) {
   return (g != NULL && v >= 0 && v < g->nV);
}

void insertEdge(Graph g, Vertex v, Vertex w, int weight) {
   assert(g != NULL && validV(g,v) && validV(g,w));

   if (g->edges[v][w] == 0) {   // edge e not in graph
      g->edges[v][w] = weight; 
      g->nE++;
   }
}

void removeEdge(Graph g, Vertex v, Vertex w) {
   assert(g != NULL && validV(g, v) && validV(g, w));

   if (g->edges[v][w] != 0) 
   {   
      g->edges[v][w] = 0;
      g->nE--;
   }
}

void showGraph(Graph g) {
    assert(g != NULL);
    int i, j;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++)
       for (j = i+1; j < g->nV; j++)
	  if (g->edges[i][j] != 0)
	     printf("Edge %d - %d: %d\n", i, j, g->edges[i][j]);
}

void freeGraph(Graph g) {
   assert(g != NULL);

   int i;
   for (i = 0; i < g->nV; i++)
      free(g->edges[i]);
   free(g->edges);
   free(g);
}

bool GraphCheckAdjacent(Graph g, Vertex v, Vertex w)
{
	if (g->edges[v][w]) {
		return true; 
	} else {
		return false; 
	}
}