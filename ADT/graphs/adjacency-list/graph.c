#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 

typedef struct GraphRep {
  Node **edges; // 2d array of edges 
  int nV; // number of vertices 
  int nE; // number of edges 
} GraphRep;  


Graph GraphNew(Vertex v)
{
  assert(V >= 0); 

  Graph g = malloc(sizeof(GraphRep)); 

  // populate the struct with the values 
  g->nV = V; 
  g->nE = 0; 

  // allocate memory for the array of list 
  g->edges = malloc(V * sizeof(Node)); 

  for (int i = 0; i < g->nV; i++)
  {
    g->edges[i] = NULL; // setting everything to NULL 
  }
  return g; 
}

bool validV(Graph g, Vertex v)
{
  return (g != NULL && v >= 0 && v < g->nV); 
}

void insertEdge(Graph g, Edge e)
{
  assert(g != NULL && )
}