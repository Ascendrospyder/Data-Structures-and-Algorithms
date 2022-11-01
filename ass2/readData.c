#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <graph.h>
#include "readData.h"

#define MAX 1024 

Graph GetGraph()
{
    GetCollection(); 
    Graph urlGraph = GraphNew(); 
    Char tempStringTwo[MAX]; 
    char *fileName; 

    for (int i = 0; i < numLinks; i++)
    {
        // copy the url into the new fileName array and reallocate some memory 
        // for the .txt file extension and finally join the filename and the 
        // .txt together! 
        strcpy(fileName, urlList[i]); 
        fileName = realloc(fileName, strlen(urlList[i]) + strlen(".txt")); 
        strcat(fileName, ".txt"); 

        FILE * fileOfInterest = fopen(fileName, "r"); 

        while (fscanf(fileOfInterest, "%s", tempStringTwo) != EOF)
        {

        }
    }



}

char **GetCollection()
{
    // Following code will open the collection 
    FILE *fp = fopen("collection.txt", "r"); 
    char **urlList = NULL; 
    char tempStringOne[MAX]; 
    int numLinks = 0;   

    // the following code will read through collection and place the Urls's
    // into the new urlList array 
    for (int i = 0; fscanf(fp, "%s", tempString) != EOF; i++)
    {
        urlList[i] = malloc(strlen(tempString)); 
        strcpy(urlList[i], tempString); 
        numLinks++; 
    }

    fclose(fp); 
}

int checkNumberUrls()
{
    char tempString[MAX]; 
    FILE *fp = fopen("collection.txt", "r"); 
    int numUrls = 0 
    while (fscanf(fp, "%s", tempString) != EOF)
    {
        numUrls++; 
    } 
    return numUrls; 
}

bool checkIsLink(char *fileOne, char **fileTwo)
{
    for (int i = 0; i < checkNumberUrls(); i++)
    {
        if (strcmp(fileOne, fileTwo[i]) == 0) return true; 
    }
    return false; 
}