// COMP2521 Assignment 2

// Written by: Arindam Mukherjee 
// Date: 4 / 11 / 2022 

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readData.h"
#include "graph.h"

#define MAX 1000

///////////////////////////////// function declarations ///////////////////////
double findWeightedInlinks(Graph g, Vertex v, Vertex w); 
double numLinksToPage(Graph g, Vertex v); 
double numLinksToReference(Graph g, Vertex w); 
double findWeightedOutlinks(Graph g, Vertex v, Vertex w); 
double numOutlinksToPage(Graph g, Vertex v); 
double numOutlinksToReference(Graph g, Vertex w); 
void sortDescendingPrint(double *pageRank, int *outDegree, int len, 
                        char **urlList); 
void initialisePageRankArray(double *pageRank, double *previousPageRank, 
                            int numUrls, double numUrlsFloat); 
void updatePreviousPageRankArray(double *pageRank, double *previousPageRank, int numUrls); 
double calculatePreviousPageRank(Graph url, double *previousPRArray, int i, int numUrls); 
double calculateSumOfDiff(double *pageRank, double *previousPageRank, int numUrls); 
void populateOutdegree(Graph urlGraph, int *outDegree, int numUrls); 
///////////////////////////////// function declarations ///////////////////////

int main(int argc, char *argv[]) 
{
    // argc is the number of command-line arguments, which includes the
    // program name
    // argv is the array of command-line arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s dampingFactor diffPR maxIterations\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    // Read pages from the collection in file collection.txt and build a graph structure 
    // using a graph representation of your choice
    FILE *collectionFile = fopen("collection.txt", "r"); 
    char *urlList[MAX]; 
    char tempStringOne[MAX];    

    GetCollection(collectionFile, tempStringOne, urlList); 

    Graph urlGraph = GetGraph(); 
    int numUrls = checkNumberUrls(); 
    double numUrlsFloat = (double)numUrls; 
    double pageRank[numUrls]; 
    double previousPageRank[numUrls]; 
    double sumOfDiff = 0.0; 

    // set the pagerank arrays' to 1/n
    initialisePageRankArray(pageRank, previousPageRank, numUrls, numUrlsFloat); 

    int iteration = 0; 
    double diff = diffPR; 
    while (iteration < maxIterations && diff >= diffPR)
    {
        sumOfDiff = 0.0; 
        updatePreviousPageRankArray(pageRank, previousPageRank, numUrls); 
        
        for (int i = 0; i < numUrls; i++)  
        {
            double previousWeightedPageRank = calculatePreviousPageRank(urlGraph, previousPageRank, i, numUrls); 
            pageRank[i] = ((1.0 - d) / (numUrlsFloat)) + (d * previousWeightedPageRank);    
        }
        
        sumOfDiff = calculateSumOfDiff(pageRank, previousPageRank, numUrls); 
        diff = sumOfDiff; 
        iteration++; 
    } 

    int outDegree[numUrls]; 
    populateOutdegree(urlGraph, outDegree, numUrls); 

    sortDescendingPrint(pageRank, outDegree, numUrls, urlList); 
    
    freeUrlsArray(urlList, numUrls); 
    freeGraph(urlGraph); 
}

/**
 * @brief - W_in(u, v) = num links in page u / num all links in reference page v
 * 
 * @param g 
 * @param v 
 * @param w 
 * @return double 
 */
double findWeightedInlinks(Graph g, Vertex v, Vertex w)
{
    
    return numLinksToPage(g, w) / numLinksToReference(g, v); 
}

double numLinksToPage(Graph g, Vertex v)
{
    double total = 0; 
    int numUrls = checkNumberUrls(); 
    for (int i = 0; i < numUrls; i++)
    {
        if (i != v && GraphCheckAdjacent(g, i, v))
        {
            total++; 
        }
    } 
    return total; 
}

double numLinksToReference(Graph g, Vertex w)
{
    double total = 0; 
    int numUrls = checkNumberUrls(); 

    for (int i = 0; i < numUrls; i++)
    {
        if (i != w && GraphCheckAdjacent(g, w, i))
        {
            total += numLinksToPage(g, i); 
        }
    }
    return total; 
}

double findWeightedOutlinks(Graph g, Vertex v, Vertex w)
{
    return numOutlinksToPage(g, w) / numOutlinksToReference(g, v); 
}

double numOutlinksToPage(Graph g, Vertex v)
{
    double total = 0; 
    int numUrls = checkNumberUrls(); 

    for (int i = 0; i < numUrls; i++)
    {
        if (i != v && GraphCheckAdjacent(g, v, i))
        {
            total++; 
        }
    }

    if (total == 0) total = 0.5; 
    return total; 
}

double numOutlinksToReference(Graph g, Vertex w)
{
    double total = 0; 
    int numUrls = checkNumberUrls(); 

    for (int i = 0; i < numUrls; i++)
    {
        if (i != w && GraphCheckAdjacent(g, w, i))
        {
            total += numOutlinksToPage(g, i); 
        }
    }
    return total; 
}

void swapElementsInArray(double tempPr, double *pageRank, int tempOutdegree, int *outDegree, char *tempUrlList, char **urlList, int i, int j)
{
    tempPr = pageRank[i]; 
    pageRank[i] = pageRank[j]; 
    pageRank[j] = tempPr; 

    tempOutdegree = outDegree[i]; 
    outDegree[i] = outDegree[j]; 
    outDegree[j] = tempOutdegree; 

    tempUrlList = urlList[i];
    urlList[i] = urlList[j]; 
    urlList[j] = tempUrlList;
}

void sortPageRank(double *pageRank, int *outDegree, int len, char **urlList, double tempPr, int tempOutdegree, char *tempUrlList/*, int i*/)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (pageRank[i] < pageRank[j])
            {
                swapElementsInArray(tempPr, pageRank, tempOutdegree, outDegree, tempUrlList, urlList, i, j); 
            }
        }
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (pageRank[i] == pageRank[j])
            {
                if (strcmp(urlList[i], urlList[j]) > 0)
                {
                    swapElementsInArray(tempPr, pageRank, tempOutdegree, outDegree, tempUrlList, urlList, i, j);
                }
            }
        }
    }
}

void sortDescendingPrint(double *pageRank, int *outDegree, int len, char **urlList)
{
    double pageRankTemp = 0.0; 
    int outDegreeTemp = 0;
    char *urlListTemp = 0;  

    sortPageRank(pageRank, outDegree, len, urlList, pageRankTemp, outDegreeTemp, urlListTemp/*, i*/);
    
    for (int k = 0; k < len; k++)
    {
        printf("%s %d %.7f\n", urlList[k], outDegree[k], pageRank[k]);
    }  
}

void initialisePageRankArray(double *pageRank, double *previousPageRank, int numUrls, double numUrlsFloat)
{
    for (int i = 0; i < numUrls; i++)
    {
        pageRank[i] = (1.0 / numUrlsFloat);  
        previousPageRank[i] = (1.0 / numUrlsFloat); 
    }
}

void updatePreviousPageRankArray(double *pageRank, double *previousPageRank, int numUrls)
{
    for (int j = 0; j < numUrls; j++)
    {
        previousPageRank[j] = pageRank[j]; 
    }
}

double calculatePreviousPageRank(Graph url, double *previousPRArray, int i, int numUrls)
{
    double previousPR = 0.0; 
    for (int j = 0; j < numUrls; j++)
    {
        if (i != j && GraphCheckAdjacent(url, j, i))
        { 
            previousPR = previousPR + (previousPRArray[j] * findWeightedInlinks(url, j, i) * findWeightedOutlinks(url, j, i));
        }
    }
    return previousPR; 
}

double calculateSumOfDiff(double *pageRank, double *previousPageRank, int numUrls)
{
    double sumOfDiff = 0.0; 
    for (int k = 0; k < numUrls; k++)
    {
        sumOfDiff = sumOfDiff + fabs(pageRank[k] - previousPageRank[k]); 
    }
    return sumOfDiff; 
}

void populateOutdegree(Graph urlGraph, int *outDegree, int numUrls)
{
    for (int i = 0; i < numUrls; i++)
    {
        outDegree[i] = (int)numOutlinksToPage(urlGraph, i);  
    } 
}


 
