// readData ADT
// Name: Arindam Mukherjee 
// zId: z5421641
// date : 4/11/2022
/*
    Description: The following file acts as a helper file to help create a ]
    graph and get the collection for pageRank.c to use
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "readData.h"
#include "graph.h"

#define MAX 1000 


/**
 * @brief - This function acts as a helper function, to return the 
 * number of url links there are in collection.txt 
 * 
 * @return -int, number of urlLinks present
**/ 
int CheckNumberUrls(void)
{
    char tempString[MAX]; 
    FILE *collectionFile = fopen("collection.txt", "r"); 
    int numUrls = 0; 
    while (fscanf(collectionFile, "%s", tempString) != EOF)
    {
        numUrls++; 
    } 
    return numUrls; 
}

/**
 * @brief - The following function acts as a helper function, to check if
 * there exists a link between a given temporary file string and file array 
 * 
 * @param fileString - Is a temporary file string 
 * @param fileArray - Is a temporary file Array 
 * @return true - if there exists a link 
 * @return false - if there isn't a link 
 * 
**/
bool CheckIsLink(char *fileString, char **fileArray)
{
    for (int i = 0; i < CheckNumberUrls(); i++)
    {
        if (strcmp(fileString, fileArray[i]) == 0) return true; 
    }
    return false; 
}

/**
 * @brief - The following finds where the string is located in the 
 * given array, utilising the strcmp function 
 * 
 * @param numLinks - The number of links that exists 
 * @param fileString - The string being passed on to verify the position
 * @param fileArray - The array being passed to verify where the string
 * is located 
 * @return int - the position in the file array that the string exists in 
**/
int CheckLinkPosition(int numLinks, char *fileString, char **fileArray)
{
    int position = 0; 
    while (position < numLinks)
    {
        if (strcmp(fileString, fileArray[position]) == 0) return position; 
        position++; 
    }
    return position; 
}

/**
 * @brief - The following function will free the url Array. 
 * 
 * @param arrayOfUrls - The array which holds all the urls to be freed
 * @param len - length of the array 
**/ 
void FreeUrlsArray(char **arrayOfUrls, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(arrayOfUrls[i]); 
    }
}

/**
 * @brief - The following function will go through the urlList and
 * concatenate the string with .txt which will be used to open the url 
 * file. 
 * 
 * @param arrayOfUrls - An array holding all the urls
 * @param i - the particular index in the loop 
 * 
 * @returns - the new file name
**/ 
static char *getFileName(char **arrayOfUrls, int i)
{
    char *fileName; 

    fileName = malloc(strlen(arrayOfUrls[i]) + 1); 
    strcpy(fileName, arrayOfUrls[i]); 
    fileName = realloc(fileName, strlen(arrayOfUrls[i]) + strlen(".txt") + 1);
    strcat(fileName, ".txt");

    return fileName; 
}

/**
 * @brief - The following helper function will insert the link into the
 * urlGraph, if it there exists a link with the provided url.
 * 
 * @param tempBufferString - A string that holds the contents of the url file
 * @param arrayOfUrls - The array holding all the urls
 * @param url - The graph we want to insert the link into
 * @param i - the particular index we want to insert into
**/ 
static void insertLink(char *tempBufferString, char **arrayOfUrls, Graph url, 
                       int i)
{
    if (CheckIsLink(tempBufferString, arrayOfUrls))
    {
        int pos = CheckLinkPosition(CheckNumberUrls(), 
                                    tempBufferString, arrayOfUrls);
        insertEdge(url, i, pos, 1);  
    }
}

/**
 * @brief - The following function will open the collection file and copy 
 * the urls into a urlArray. 
 * 
 * @param collectionFile - File holding collection.txt
 * @param tempBufferString - a temporary buffer which we will use to scan in 
 * @param urlArr - store the urls 
 */
void GetCollection(FILE *collectionFile, char *tempBufferString, char **urlArr)
{
    for (int i = 0; fscanf(collectionFile, "%s", tempBufferString) != EOF; i++)
    { 
        urlArr[i] = malloc(strlen(tempBufferString) + 1); 
        strcpy(urlArr[i], tempBufferString); 
    }

    fclose(collectionFile); 
}

/**
 * @brief - The following function will create a new graph by adding
 * relevant urls and outgoing links. 
 * 
 * @return - A new urlGraph
**/ 
Graph GetGraph(void)
{
    FILE *collectionFile = fopen("collection.txt", "r"); 
    char *arrayOfUrls[MAX]; 
    char tempBufferString1[MAX]; 

    // the following code will read through collection and place the urls's
    // into the new arrayOfUrls array 
    for (int i = 0; fscanf(collectionFile, "%s", tempBufferString1) != EOF; i++)
    { 
        arrayOfUrls[i] = malloc(strlen(tempBufferString1) + 1); 
        strcpy(arrayOfUrls[i], tempBufferString1); 
    }
    fclose(collectionFile); 
    

    int numLinks = CheckNumberUrls(); 
    Graph urlGraph = newGraph(numLinks); 
    char tempBufferString2[MAX]; 

    // the following code will open each of the urls and add
    // the relevant urls and outgoing links 
    for (int i = 0; i < numLinks; i++)
    {
        char *fileName = getFileName(arrayOfUrls, i);

        FILE *fileOfInterest = fopen(fileName, "r"); 
        while (fscanf(fileOfInterest, "%s", tempBufferString2) != EOF)
        {
            insertLink(tempBufferString2, arrayOfUrls, urlGraph, i); 
        } 
        fclose(fileOfInterest); 
        free(fileName); 
    }
    FreeUrlsArray(arrayOfUrls, numLinks); 
    return urlGraph; 
}