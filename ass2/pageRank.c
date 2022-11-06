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
void sortDescendingPrint(double *pageRank, int *outDegree, int len, char **urlList); 
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
    FILE *fp = fopen("collection.txt", "r"); 
    char *urlList[MAX]; 
    char tempStringOne[MAX];    

    // the following code will read through collection and place the Urls's
    // into the new urlList array 
    for (int i = 0; fscanf(fp, "%s", tempStringOne) != EOF; i++)
    { 
        urlList[i] = malloc(strlen(tempStringOne) + 1); 
        strcpy(urlList[i], tempStringOne); 
    }
    fclose(fp); 

    // the following code will build the graph
    Graph urlGraph = GetGraph(); 
    
    int numUrls = checkNumberUrls(); 
    double numUrlsFloat = (double)numUrls; 
    double pageRank[numUrls]; 
    double previousPageRank[numUrls]; 

    // the following code will set pagerank to 1/n
    for (int i = 0; i < numUrls; i++)
    {
        pageRank[i] = (1 / numUrlsFloat); 
        previousPageRank[i] = (1 / numUrlsFloat); 
    }

    int iteration = 0; 
    double diff = diffPR; 
    while (iteration < maxIterations && diff >= diffPR)
    {
        for (int i = 0; i < numUrls; i++) // too nested need to fix later 
        {
            double previousWeightedPageRank = 0; 
            for (int j = 0; j < numUrls; j++)
            {
                if (i != j && GraphCheckAdjacent(urlGraph, j, i))
                { 
                    previousWeightedPageRank = previousWeightedPageRank + (previousPageRank[j] * findWeightedInlinks(urlGraph, j, i) * findWeightedOutlinks(urlGraph, j, i));
                }
            }
            pageRank[i] = ((1 - d) / (numUrlsFloat)) + (d * previousWeightedPageRank);    
        }
        

        for (int i = 0; i < numUrls; i++)
        {
            diff = diff + fabs(pageRank[i] - previousPageRank[i]); 
        }

        for (int j = 0; j < numUrls; j++)
        {
            previousPageRank[j] = pageRank[j]; 
        }
        
        iteration++;
    } 

    int outDegree[numUrls]; 
    for (int i = 0; i < numUrls; i++)
    {
        outDegree[i] = (int)numOutlinksToPage(urlGraph, i);  
    } 

    sortDescendingPrint(pageRank, outDegree, numUrls, urlList); 
    return 0; 
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

void sortPageRank(double *pageRank, int *outDegree, int len, char **urlList, double tempPr, int tempOutdegree, char *tempUrlList, int i)
{
    for (int j = 0; j < len - i - 1; j++)
    {   
        if (pageRank[j] < pageRank[j + 1])
        {
            // swap pageRank --> outdegree --> urlList 
            tempPr = pageRank[j]; 
            pageRank[j] = pageRank[j + 1]; 
            pageRank[j + 1] = tempPr; 

            tempOutdegree = outDegree[j]; 
            outDegree[j] = outDegree[j + 1]; 
            outDegree[j + 1] = tempOutdegree; 

            tempUrlList = urlList[j];
            urlList[j] = urlList[j + 1]; 
            urlList[j + 1] = tempUrlList; 
        }
    }
}

void sortDescendingPrint(double *pageRank, int *outDegree, int len, char **urlList)
{
    double pageRankTemp = 0.0; 
    int outDegreeTemp = 0;
    char *urlListTemp = 0;  

    for (int i = 0; i < len; i++)
    {
        sortPageRank(pageRank, outDegree, len, urlList, pageRankTemp, outDegreeTemp, urlListTemp, i);
    }
    
    for (int k = 0; k < len; k++)
    {
        printf("%s %d %.7f\n", urlList[k], outDegree[k], pageRank[k]);
    }  
}


 
