// Weighted Graph ADT interface ... COMP2521 
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdbool.h>

typedef struct GraphRep *Graph;

// vertices are ints
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
   Vertex v;
   Vertex w;
   int weight; // TODO new change here 
} Edge;

Graph newGraph(int);
void insertEdge(Graph, Vertex, Vertex, int); 
void removeEdge(Graph, Vertex, Vertex);
int  adjacent(Graph, Vertex, Vertex);  // returns weight, or 0 if not adjacent
void  showGraph(Graph);
void  freeGraph(Graph);
bool GraphCheckAdjacent(Graph, Vertex, Vertex); 

#endif