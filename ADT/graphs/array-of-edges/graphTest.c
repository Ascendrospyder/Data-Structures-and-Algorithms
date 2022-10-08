#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h"

int main (int argc, char **argv)
{
  Graph g = GraphNew(3); 
  // Edge e; 
  // e.v = 2; 
  // e.w = 3; 

  /*Edge e2; 
  e2.v = 7; 
  e2.w = 9; */ 

  Edge e3; 
  e3.v = 1; 
  e3.w = 2; 
  // GraphEdgeInsert(g, e); 
  // GraphEdgeInsert(g, e2); 
  GraphEdgeInsert(g, e3); 
  GraphShow(g); 
}