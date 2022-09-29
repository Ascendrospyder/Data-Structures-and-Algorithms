#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 
#include "list.h"
#include "queue.h"

#define FALSE 0 
#define TRUE 1 
#define MAX_NODES 1000 

int visited[MAX_NODES];

bool findPathBFS(Graph g, Vertex src, Vertex dest); 

int main (int argc, char *argv[])
{
    int V = 6;
    Graph g = GraphNew(V);

    Edge e;
    e.v = 0; e.w = 1; GraphEdgeInsert(g, e);
    e.v = 0; e.w = 2; GraphEdgeInsert(g, e);
    e.v = 0; e.w = 5; GraphEdgeInsert(g, e);
    e.v = 1; e.w = 5; GraphEdgeInsert(g, e);
    e.v = 2; e.w = 3; GraphEdgeInsert(g, e);
    e.v = 3; e.w = 4; GraphEdgeInsert(g, e);
    e.v = 3; e.w = 5; GraphEdgeInsert(g, e);
    e.v = 3; e.w = 8; GraphEdgeInsert(g, e);
    e.v = 4; e.w = 5; GraphEdgeInsert(g, e);
    e.v = 4; e.w = 7; GraphEdgeInsert(g, e);
    e.v = 4; e.w = 8; GraphEdgeInsert(g, e);
    e.v = 5; e.w = 6; GraphEdgeInsert(g, e);
    e.v = 7; e.w = 8; GraphEdgeInsert(g, e);
    e.v = 7; e.w = 9; GraphEdgeInsert(g, e);
    e.v = 8; e.w = 9; GraphEdgeInsert(g, e);

    int src = 0, dest = 6;
   if (findPathBFS(g, src, dest)) {
      Vertex v = dest;
      while (v != src) {
	 printf("%d - ", v);
	 v = visited[v];
      }
      printf("%d\n", src);
   }
   return 0;
}

bool findPathBFS(Graph g, Vertex src, Vertex dest)
{
  Vertex v;//   Vertex *visited = malloc(sizeof(Vertex*)); // create a visited array 
  for (v = 0; v < g->nV; v++)
  {
    visited[v] = -1; // initialise everything to -1 
  }
  visited[src] = src; // fill the starting nodes value with itself 
  
  Queue q = QueueNew(); // create a new queue 
  QueueEnqueue(q, src);  // add src (root node) to the queue 
  while (!QueueIsEmpty(q)) // as we go through the queue, make sure its not empty found != 0 
  { 
    v = QueueDequeue(q); // take something of the queue 
    Vertex w; 
    for (w = 0; w < g->nV; w++) // loop through all the neighbours  of the graph 
    {
      if (GraphAdjacent(g, v, w) && visited[w] == -1) // check if nodes are adjacent and havent been visited yet
      {
        visited[w] = v; 
        if (w == dest) // if w is what we are looking for mark it as found 
        {
          return true; 
        } else {
          QueueEnqueue(q, w); // if not found add w to the queue
        }
    }  
    }
  }
  return false; 
}

