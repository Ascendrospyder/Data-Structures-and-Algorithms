#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h"


typedef struct GraphRep {
  Edge *edges; // array of edges 
  int nV; // number of vertices 
  int nE; // number of edges 
  int n; // size of edge array 
} GraphRep;  


Graph newGraph(Vertex V)
{
  assert(V >= 0); // return an error if the Vertex isnt greater than or equal to 0  
  Graph g = malloc(sizeof(GraphRep)); // allocate some memory for the graph

  g->nV = V; // fill in the values for the graph 
  g->nE = 0;             
  // Looping through the whole array and callocing every element to 0
  /*for (int i = 0; i < V; i++)
  {
    g->edges[i] = calloc(g->n, sizeof(Edge)); 
  }*/ 
  g->edges = malloc(g->n * sizeof(Edge)); // allocate (size of edge array) * sizeof(Edge struct); 
  return g; 
}

/**
* Checks if two edges are equal 
*/
bool checkEqual(Edge e1, Edge e2)
{
  return ( e1.v == e2.v && e1.w == e2.w) || (e1.v == e2.w && e1.w == e2.v); 
}

void insertEdge(Graph g, Edge e) // Edge e = (v, w); 
{
  assert(g != NULL && g->nE < g->n); // if condtions not met produce an error 

  int i = 0; 
  while (i < g->nE && !checkEqual(e, g->edges[i])) // loop if i < number of edges and if two edges are not equal 
  {
    i++; 
  }

  if (i == g->nE)
  {
    g->edges[g->nE++] = e; 
  }
}

void removeEdge(Graph g, Edge e)
{
  assert(g != NULL); // if g is empty then produce an error 

  int i = 0; 
  while (i < g->nE && !checkEqual(e, g->edges[i]))
  {
    g->edges[i] = g->edges[--g->nE]; 
  }
}
