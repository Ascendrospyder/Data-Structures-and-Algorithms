#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 

int main(void)
{
  Graph g = GraphNew(10);

  Edge e1; 
  e1.w = 2; 
  e1.v = 3; 

  Edge e2; 
  e2.w = 7; 
  e2.v = 2; 

  GraphEdgeInsert(g, e1);
  GraphEdgeInsert(g, e2); 
  GraphShow(g);  
}