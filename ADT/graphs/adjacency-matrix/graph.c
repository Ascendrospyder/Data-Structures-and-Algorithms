#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 

typedef struct GraphRep {
  Edge **edges; // 2d array of edges 
  int nV; // number of vertices 
  int nE; // number of edges 
} GraphRep;  

/**
 * @brief - This function will create a new graph given a vertex
 * 
 * @param V - Vertex V
 * @return Graph - new graph 
 */
Graph GraphNew(Vertex V)
{
  assert(V >= 0); // check if the vertex is greater than or equal to 0 
  Graph g = malloc(sizeof(GraphRep)); // malloc some space for the graph as we havent statically declared memory for it 
  assert(g != NULL); 
  // allocate the info 
  g->nV = V; 
  g->nE = 0; // since its a new graph it has no edges 
  // allocate memory for each row 
  // the reason we don't malloc with two loops is because the malloc following this line 
  // will go ahead and allocate memory to each row an the next loop will go through the cols
  g->edges = malloc(V * sizeof(int *)); 
  // allocate memory for each col and initialise with 0 
  for (int i = 0; i < V; i++)
  {
    g->edges[i] = calloc(V, sizeof(int)); // this will allocate memory and set every element to zero  
  }
  return g;  
}

/**
 * @brief - this function inserts an edge in a graph 
 * 
 * @param g - graph g
 * @param e - edge e 
 */
void GraphEdgeInsert(Graph g, Edge e)
{
  if (!g->edges[e->v][e->w]) // if (g->edges[e->v][e->w] != 0) which means if edge e isn't in graph 
  {
    g->edges[e->v][e->w] = 1; // a slot adj[i][j] = 1 indicates that there is an edge from vertex i to vertex j.
    g->edges[e->w][e->v] = 1; // the reason why we do this twice is because there is an edge from v - w and w - v so we set it as 1 twice 
    g->nE++; // increase the number of edges by 1  
  }
}

/**
 * @brief - this function removes an edge in a graph 
 * 
 * @param g - graph g 
 * @param e - edge e 
 */
void GraphEdgeRemove(Graph g, Edge e)
{
  if (g->edges[e->v][e->w]) // if g->edges[e->v][e->w] == 0) which means if the edge is found 
  {
    g->edges[e->v][e->w] = 0; // a slot adj[i][j] = 0 indicates that there is an edge from vertex i to vertex j and we want to remove it.
    g->edges[e->w][e->v] = 0; // the reason why we do this twice is because there is an edge from v - w and w - v so we set it as 0 twice 
    g->nE--; // decrement the number of edges by 1 
  }
}

/**
 * @brief - this functions prints out a graph 
 * 
 * @param g - graph g 
 */
void GraphShow(Graph g)
{
  for (int i = 0; i < g->nV; i++) // loop through the row
  {
    for (j = i + 1; j < g->nV; j++) // loop through the cols 
    {
      if (g->edges[i][j]) // if (g->edges[i][j] != 0) meaning if edge found then go ahead and print 
      {
        printf("Edge %d - %d\n", i, j);
      }
    }
  }
}

/**
 * @brief - this function free's a graph 
 * 
 * @param g - Graph g
 */
void GraphDestroy(Graph g)
{
  assert(g != NULL); 
  // loop through the edges array of a graph and destroy each element in the row just like that
  // the reason we don't free with two loops is because the free following this line 
  // will go ahead and free memory for each row and the next loop will go through the cols and free
  for (int i = 0; i < g->nV; i++)
  {
    free(g->edges[i]); 
  }
  // this will free everything in the col 
  free(g->edges); // free the edges array 
  free(g); // free the graph 
}