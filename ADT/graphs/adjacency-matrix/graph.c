#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 

typedef struct GraphRep {
  Edge **edges; // 2d array of edges 
  int nV; // number of vertices 
  int nE; // number of edges 
} GraphRep;  

