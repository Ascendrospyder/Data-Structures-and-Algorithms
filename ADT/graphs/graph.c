#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h"

typedef struct GraphRep {
  Edge *edges; // array of edges we have
  int nV; // number of vertices 
  int nE; // number of edges 
  int n; // size of edge array 
} GraphRep;  

/**
 * @brief - creates a new graph 
 * 
 * @param V - takes in a vertex v 
 * @return Graph 
 */
Graph GraphNew(Vertex V)
{
  assert(V >= 0); // return an error if the Vertex isnt greater than or equal to 0  
  Graph g = malloc(sizeof(GraphRep)); // allocate some memory for the graph

  g->nV = V; // fill in the values for the graph 
  g->nE = 0;             
  g->edges = malloc(g->n * sizeof(Edge)); // allocate (size of edge array) * sizeof(Edge struct); 
  return g; 
}


bool checkEqual(Edge e1, Edge e2)
{
  return ( e1.v == e2.v && e1.w == e2.w) || (e1.v == e2.w && e1.w == e2.v); // the reason we have (e1.v == e2.w && e1.w == e2.v) because we also need to check if the nodes are the same when reversed 
  /* same as 
  if (( e1.v == e2.v && e1.w == e2.w) || (e1.v == e2.w && e1.w == e2.v))
  {
    return true; 
  } 
  return false 
  */ 
}

/**
 * @brief - This function inserts an edge into a graph 
 * 
 * @param g - takes in a graph 
 * @param e - takes in an edge 
 */
void GraphEdgeInsert(Graph g, Edge e) // Edge e = (v, w); 
{
  assert(g != NULL && g->nE < g->n); // if condtions not met produce an error 

  int i = 0; 
  while (i < g->nE && !checkEqual(e, g->edges[i])) // loop if i < number of edges and if two edges are not equal 
  {
    i++; // amount of elements 
  }

  if (i == g->nE) // if the index value is the same as the number of edges then go ahead and insert the edge into the array 
  {
    g->edges[g->nE++] = e; // insert edge e into the edges array of graph g
  } 
}

/**
 * @brief - Removes an edge from a graph
 * 
 * @param g - takes in a graph 
 * @param e - takes in an edge to remove 
 */
void GraphEdgeRemove(Graph g, Edge e)
{
  assert(g != NULL); // if g is empty then produce an error 

  int i = 0; 
  while (i < g->nE && !checkEqual(e, g->edges[i])) // loop as long as we reach the g->ne amount of elements provided they are not equal
  {
    g->edges[i] = g->edges[--g->nE]; // at the point of index go ahead and remove 
  }
}

/**
 * @brief - checks if a graph is adjacent or not 
 * 
 * @param g - takes in a graph 
 * @param x - takes in a vertex x 
 * @param y - takes in a vertex y
 * @return true - if adjacent 
 * @return false - else 
 */
bool GraphAdjacent(Graph g, Vertex x, Vertex y)
{
  assert(g != NULL); // if the condition isnt satisfied then reproduce an error 

  Edge e; // create a new edge and populate it with the vertices 
  e.v = x; 
  e.w = y;

  int i = 0; 
  while (i < g->nE) // loop through the number of edges and check if e == g->edges[i]
  {
    if (checkEqual(e, g->edges[i]))
    {
      return true; 
    }
    i++; 
  } 
  return false; 
}

/**
 * @brief - print the graph out
 * 
 * @param g - graph g 
 */
void GraphShow (Graph g)
{
  assert(g != NULL); // if the graph doesn't exist, then show an error in the terminal 

  printf("Number of Vertices: %d\n", g->nV); 
  printf("Number of Edges: %d\n", g->nE); 

  for (int i = 0; i < g->nE; i++)
  {
    printf("Edge %d - %d\n", g->edges[i].v, g->edges[i].w); 
  }
}
/**
 * @brief - frees the graph 
 * 
 * @param g - graph g 
 */
void GraphDestroy(Graph g)
{
  assert(g != NULL); 

  free(g->edges); 
  free(g); 
}
