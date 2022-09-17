#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node *List;

struct Node *makeNode (int); 
List insertLL (List, int); 
List deleteLL(List, int); 
bool inLL (List, int);
void showLL(List); 
void freeLL(List);  
