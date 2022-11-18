#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "readData.h"
#include "graph.h"

#define MAX 1000 

// submission command : give cs2521 ass2 pageRank.c searchPageRank.c scaledFootrule.c graph.c graph.h readData.c readData.h

/**
 * @brief - This function acts as a helper function, to return the 
 * number of url links there are in collection.txt 
 * 
 * @return -int, number of urlLinks present
**/ 
int checkNumberUrls()
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
bool checkIsLink(char *fileString, char **fileArray)
{
    for (int i = 0; i < checkNumberUrls(); i++)
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

/**
 * @brief - The following function will free the url Array. 
 * 
 * @param urlList - The array which holds all the urls to be freed
 * @param len - length of the array 
**/ 
void freeUrlsArray(char **urlList, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(urlList[i]); 
    }
}

/**
 * @brief - The following function will go through the urlList and
 * concatenate the string with .txt which will be used to open the url 
 * file. 
 * 
 * @param urlList - An array holding all the urls
 * @param i - the particular index in the loop 
 * 
 * @returns - the new file name
**/ 
char *getFileName(char **urlList, int i)
{
    char *fileName; 

    fileName = malloc(strlen(urlList[i]) + 1); 
    strcpy(fileName, urlList[i]); 
    fileName = realloc(fileName, strlen(urlList[i]) + strlen(".txt") + 1);
    strcat(fileName, ".txt");

    return fileName; 
}

/**
 * @brief - The following helper function will insert the link into the
 * urlGraph, if it there exists a link with the provided url.
 * 
 * @param tempString - A string that holds the contents of the url file
 * @param urlList - The array holding all the urls
 * @param url - The graph we want to insert the link into
 * @param i - the particular index we want to insert into
**/ 
void insertLink(char *tempString, char **urlList, Graph url, int i)
{
    if (checkIsLink(tempString, urlList))
    {
        int pos = checkLinkPosition(checkNumberUrls(), tempString, urlList);
        insertEdge(url, i, pos, 1);  
    }
}

void GetCollection(FILE *collectionFile, char *tempStringOne, char **urlList)
{
    for (int i = 0; fscanf(collectionFile, "%s", tempStringOne) != EOF; i++)
    { 
        urlList[i] = malloc(strlen(tempStringOne) + 1); 
        strcpy(urlList[i], tempStringOne); 
    }

    fclose(collectionFile); 
}

/**
 * @brief - The following function will create a new graph by adding
 * relevant urls and outgoing links. 
 * 
 * @return - A new urlGraph
**/ 
Graph GetGraph()
{
    FILE *collectionFile = fopen("collection.txt", "r"); 
    char *urlList[MAX]; 
    char tempStringOne[MAX]; 

    // the following code will read through collection and place the urls's
    // into the new urlList array 
    for (int i = 0; fscanf(collectionFile, "%s", tempStringOne) != EOF; i++)
    { 
        urlList[i] = malloc(strlen(tempStringOne) + 1); 
        strcpy(urlList[i], tempStringOne); 
    }
    fclose(collectionFile); 
    

    int numLinks = checkNumberUrls(); 
    Graph urlGraph = newGraph(numLinks); 
    char tempStringTwo[MAX]; 

    // the following code will open each of the urls and add
    // the relevant urls and outgoing links 
    for (int i = 0; i < numLinks; i++)
    {
        char *fileName = getFileName(urlList, i);

        FILE *fileOfInterest = fopen(fileName, "r"); 
        while (fscanf(fileOfInterest, "%s", tempStringTwo) != EOF)
        {
            insertLink(tempStringTwo, urlList, urlGraph, i); 
        } 
        fclose(fileOfInterest); 
        free(fileName); 
    }
    freeUrlsArray(urlList, numLinks); 
    return urlGraph; 
}