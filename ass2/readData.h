// readData ADT interface 

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"

Graph GetGraph(void); 
void GetCollection(FILE *, char *, char **);
int CheckNumberUrls(); 
bool CheckIsLink(char *, char **); 
int CheckLinkPosition(int, char *, char **); 
void FreeUrlsArray(char **, int); 
