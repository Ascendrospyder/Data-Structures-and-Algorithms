#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 
#include "list.h"

int main (int argc, char *argv[])
{
    int V = 10;
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