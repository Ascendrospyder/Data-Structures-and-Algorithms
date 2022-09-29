#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef int Vertex; 

typedef struct Node {
  Vertex v; 
  struct Node *next; 
} Node;

typedef struct GraphRep {
  Node **edges; // 2d array of edges 
  int nV; // number of vertices 
  int nE; // number of edges 
} GraphRep;  

typedef struct GraphRep *Graph; // we are typedefing the struct similar to BST one

typedef struct Edge {
  Vertex v; 
  Vertex w; 
} Edge; 


Graph GraphNew(int); 
void GraphEdgeInsert(Graph, Edge); 
void GraphEdgeRemove(Graph, Edge); 
bool GraphAdjacent(Graph, Vertex, Vertex); 
void GraphShow(Graph); 
void GraphDestroy(Graph); 
// void findPathBFS(Graph, Vertex, Vertex); 