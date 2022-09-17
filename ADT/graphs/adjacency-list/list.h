#include <stdio.h>

typedef struct Node *List;

Node *makeNode (int); 
List insertLL (List, int); 
List deleteLL(List, int); 
bool inLL (List, int);
void showLL(List); 
void freeLL(List);  
