#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"

Graph GetGraph(); 
void GetCollection(FILE *, char *, char **);
int checkNumberUrls(); 
bool checkIsLink(char *, char **); 
int checkLinkPosition(int, char *, char **); 
void freeUrlsArray(char **, int); 
