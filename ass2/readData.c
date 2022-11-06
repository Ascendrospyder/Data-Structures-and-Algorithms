#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



#include "readData.h"
#include "graph.h"

#define MAX 1000 

int checkNumberUrls()
{
    char tempString[MAX]; 
    FILE *fp = fopen("collection.txt", "r"); 
    int numUrls = 0; 
    while (fscanf(fp, "%s", tempString) != EOF)
    {
        numUrls++; 
    } 
    return numUrls; 
}

bool checkIsLink(char *fileString, char **fileArray)
{
    for (int i = 0; i < checkNumberUrls(); i++)
    {
        if (strcmp(fileString, fileArray[i]) == 0) return true; 
    }
    return false; 
}

int checkLinkPosition(int numLinks, char *fileString, char **fileArray)
{
    int position = 0; 
    while (position < numLinks)
    {
        if (strcmp(fileString, fileArray[position]) == 0) return position; 
        position++; 
    }
    return position; 
}

Graph GetGraph()
{
    // Following code will open the collection 
    FILE *fp = fopen("collection.txt", "r"); 
    char *urlList[MAX]; 
    char tempStringOne[MAX]; 
    int numLinks = 0;   

    // the following code will read through collection and place the Urls's
    // into the new urlList array 
    for (int i = 0; fscanf(fp, "%s", tempStringOne) != EOF; i++)
    { 
        urlList[i] = malloc(strlen(tempStringOne) + 1); 
        strcpy(urlList[i], tempStringOne); 
        numLinks++; 
    }

    fclose(fp); 
     

    Graph urlGraph = newGraph(numLinks); 
    char tempStringTwo[MAX]; 
    char *fileName; 
    // Edge e; 

    for (int i = 0; i < numLinks; i++)
    {
        // copy the url into the new fileName array and reallocate some memory 
        // for the .txt file extension and finally join the filename and the 
        // .txt together!
        fileName = malloc(strlen(urlList[i]) + 1); 
        strcpy(fileName, urlList[i]); // potential bug 
        // printf("file name : %s\n", fileName); 
        fileName = realloc(fileName, strlen(urlList[i]) + strlen(".txt") + 1); // potential bug 
        strcat(fileName, ".txt"); 

        FILE *fileOfInterest = fopen(fileName, "r"); 
        

        while (fscanf(fileOfInterest, "%s", tempStringTwo) != EOF)
        {
            // printf("files inside : %s\n", tempStringTwo); 
            if (checkIsLink(tempStringTwo, urlList))
            {
                // potential bug 
                // e.v = i; 
                // printf("I am here!\n"); 
                int pos = checkLinkPosition(numLinks, tempStringTwo, urlList);
                insertEdge(urlGraph, i, pos, 1);  
            }
        }
        
        fclose(fileOfInterest); 
    }
    return urlGraph; 
}



// // potential bug 
// char **GetCollection()
// {
//     // Following code will open the collection 
//     FILE *fp = fopen("collection.txt", "r"); 
//     char **urlList = NULL; 
//     char tempStringOne[MAX]; 
//     int numLinks = 0;   

//     // the following code will read through collection and place the Urls's
//     // into the new urlList array 
//     for (int i = 0; fscanf(fp, "%s", tempString) != EOF; i++)
//     {
//         urlList[i] = malloc(strlen(tempString)); 
//         strcpy(urlList[i], tempString); 
//         numLinks++; 
//     }

//     fclose(fp); 
    
//     return urlList; 
// }

