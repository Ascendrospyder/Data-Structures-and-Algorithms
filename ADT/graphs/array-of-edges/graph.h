#include <stdbool.h>

typedef struct GraphRep *Graph; // we are typedefing the struct similar to BST one

typedef int Vertex; 


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