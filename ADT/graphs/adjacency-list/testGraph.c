#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "graph.h" 
#include "list.h"

int main (int argc, char *argv[])
{
    Graph new = GraphNew(10);
    Edge new_edge; 
    new_edge.v = 1; 
    new_edge.w = 0; 
    GraphEdgeInsert(new, new_edge); 
    Edge another; 
    another.v = 4; 
    another.w = 2;
    GraphEdgeInsert(new, another);  
    GraphShow(new);  
    return 0; 
}