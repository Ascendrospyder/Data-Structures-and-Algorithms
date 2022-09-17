#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 
#include "list.h"

typedef struct GraphRep {
  Node **edges; // 2d array of edges 
  int nV; // number of vertices 
  int nE; // number of edges 
} GraphRep;  

/**
 * @brief - the following function will create a new graph 
 * 
 * @param v - num of vertices 
 * @return Graph 
 */
Graph GraphNew(Vertex V)
{
  assert(V >= 0); 

  Graph g = malloc(sizeof(GraphRep)); // allocate some memory for the graph

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

/**
 * @brief - checks if the Vertex is valid 
 * 
 * @param g - takes in a graph g 
 * @param v - takes in a vertex v 
 * @return true if ((g != NULL && v >= 0 && v < g->nV))
 * @return false - else 
 */
bool validV(Graph g, Vertex v)
{
  return (g != NULL && v >= 0 && v < g->nV); // checks if graph exists, num vertex is not negative, num vertex is less than 
}

/**
 * @brief - inserts an edge in the graph
 * 
 * @param g - graph g 
 * @param e - edge e 
 */
void GraphEdgeInsert(Graph g , Edge e) 
{
  assert(g != NULL && validV(g, e.v) && validV(g, e.w)); // if the following conditions are false then print an error in terminal

  if(!inLL(g->edges[e.v], e.w)) // if the edge is not already in the graph then go ahead and create it 
  {
    g->edges[e.v] = insertLL(g->edges[e.v], e.w); // inserts e->w in the head of the LL 
    g->edges[e.w] = insertLL(g->edges[e.w], e.v); // inserts e->v in the head of the LL
    g->nE++; // increment the num edges by 1 
  }
}

/**
 * @brief - this function removes an edge in the graph
 * 
 * @param g - graph g 
 * @param e - edge e 
 */
void GraphEdgeRemove(Graph g, Edge e)
{
  assert(g != NULL && validV(g, e.v) && validV(g, e.w)); // if the following conditions are false then print an error in terminal

  if (inLL(g->edges[e.v], e.w)) // if the edge is already in the graph 
  {
    g->edges[e.v] = deleteLL(g->edges[e.v], e.w); // deletes the node e->w in LL 
    g->edges[e.w] = deleteLL(g->edges[e.w], e.v); // deletes the node e->v in LL 
    g->nE--; // decrement the number of edges by 1 
  }
}

/**
 * @brief - this function checks if the graph is adjacent 
 * 
 * @param g - graph g 
 * @param v - vertex v
 * @param w - vertex w 
 * @return true 
 * @return false 
 */
bool GraphAdjacent(Graph g, Vertex v, Vertex w)
{
  assert(g != NULL && validV(g, v));

  return inLL(g->edges[v], w);  
} 

/**
 * @brief - The following function prints the graph out 
 * 
 * @param g - graph g 
 */
void GraphShow(Graph g)
{
  assert(g != NULL); 

  printf("Number of vertices : %d\n", g->nV); 
  printf("Number of edges : %d\n", g->nE); 

  for (int i = 0; i < g->nV; i++)
  {
    printf("%d - ", i); 
    showLL(g->edges[i]); 
  }
}

/**
 * @brief - The following function free the graph 
 * 
 * @param g - graph g 
 */
void GraphDestroy(Graph g)
{
  assert(g != NULL); 

  for (int i = 0; i < g->nV; i++)
  {
    freeLL(g->edges[i]); // loop through edges and free the rows 
  }
  free(g); // free the cols 
}