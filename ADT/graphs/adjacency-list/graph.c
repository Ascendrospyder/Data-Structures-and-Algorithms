#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 
#include "list.h"
#include "queue.h"

#define FALSE 0 
#define TRUE 1 
#define MAX_NODES 1000



/**
 * @brief - the following function will create a new graph 
 * 
 * @param v - num of vertices 
 * @return Graph 
 */
Graph GraphNew(Vertex numV)
{
  assert(numV >= 0); 

  Graph g = malloc(sizeof(GraphRep)); // allocate some memory for the graph

  // populate the struct with the values 
  g->nV = numV; 
  g->nE = 0; 

  // allocate memory for the array of list 
  g->edges = malloc(numV * sizeof(Node)); 

  // loops through all edges and sets everything to NULL
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

/*

bool dfsCycleCheck(Graph g, Vertex v, Vertex u); 

void findPathBFS(Graph g, Vertex src, Vertex dest)
{
  Vertex *visited_array = malloc(sizeof(Vertex *)); // create a visited_array array 
  for (int i = 0; i < g->nV; i++)
  {
    visited_array[i] = -1; // initialise everything to -1 
  }
  int found = FALSE; // make a flag variable and assign it as false 
  visited_array[src] = src; // fill the starting nodes value with itself 
  
  Queue q = QueueNew(); // create a new queue 
  QueueEnqueue(q, src);  // add src (root node) to the queue 
  while (!QueueIsEmpty(q) && found == FALSE) // as we go through the queue, make sure its not empty found != 0 
  { 
    Vertex v = QueueDequeue(q); // take something of the queue 
    Vertex w; 
    for (w = 0; w < g->nV; w++) // loop through all the neighbours  of the graph 
    {
      if (GraphAdjacent(g, v, w) && visited_array[w] == -1) // check if nodes are adjacent and havent been visited_array yet
      {
        visited_array[w] = v; 
        if (w == dest) // if w is what we are looking for mark it as found 
        {
          found = TRUE;
        } else {
          QueueEnqueue(q, w); // if not found add w to the queue
        }
      }  
    }
  } 
}

bool dfsCycleCheck(Graph g, Vertex v, Vertex u)
{
  Vertex *visited = malloc(sizeof(Vertex *)); 
  visited[v] = true; 
  for (Vertex w = 0; w < g->nV; w++)
  {
    if (GraphAdjacent(g, v, w))
    {
      if (!visited[w])
      {
        if (dfsCycleCheck(g, w, v))
        {
          return true; 
        } else if (w != u)
        {
          return true; 
        }
      }
    }
  }
  return false; 
}

bool hasCycle(Graph g, Vertex s)
{
  Vertex *visited; 
  bool result = false; 
  visited = calloc(g->nV, sizeof(int)); // this will manually allocate memory and set everything to 0

  for (int v = 0; v < g->nV; v++)
  {
    for (int i = 0; i < g->nV; i++)
    {
      visited[i] = -1; 
    } 
    if (dfsCycleCheck(g, v, v))
    {
      result = true; 
      break; 
    }
  }
  free(visited); 
  return result; 
}
*/ 
/*
bool visited[MAX_NODES];


bool hamiltonR(Graph g, int nV, Vertex v, Vertex dest, int d) 
{
// v = current vertex considered
// dest = destination vertex
// d = distance "remaining" until path found

   Vertex w;
   if (v == dest) 
   {
      return (d == 0);
   } else 
   {
      visited[v] = true;
      for (w = 0; w < nV; w++) 
      {
	      if (GraphAdjacent(g, v, w) && !visited[w]) 
        {
	          if (hamiltonR(g, nV, w, dest, d-1)) 
            {
	            return true;
	          }
	      }
      }
   }
   visited[v] = false;
   return false;
}

bool hasHamiltonianPath(Graph g, int nV, Vertex src, Vertex dest) 
{
  Vertex v;
  for (v = 0; v < nV; v++)
  {
    visited[v] = false;
  }

  return hamiltonR(g, nV, src, dest, nV-1);
}
*/ 