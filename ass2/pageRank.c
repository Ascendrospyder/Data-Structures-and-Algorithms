// COMP2521 Assignment 2
// The following file was indented by clang format

// Written by: Arindam Mukherjee
// zId : z5421641
// Date: 4 / 11 / 2022
/*
    Description: The following program calculates Weighted PageRanks for 
    a collection of pages.
*/ 

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "readData.h"

#define MAX 1000

///////////////////////////////// function declarations ///////////////////////
static double findWeightedInlinks(Graph g, Vertex v, Vertex w);
static double numLinksToPage(Graph g, Vertex v);
static double numLinksToReference(Graph g, Vertex w);
static double findWeightedOutlinks(Graph g, Vertex v, Vertex w);
static double numOutlinksFromPage(Graph g, Vertex v);
static double numOutLinksFromReference(Graph g, Vertex w);
static void sortDescendingPrint(double *pageRank, int *outDegree, int len,
                                char **urlList);
static void initialisePageRankArray(double *pageRank, double *previousPageRank,
                                    int numUrls, double numUrlsFloat);
static void updatePreviousPageRankArray(double *pageRank, 
                                        double *previousPageRank,
                                        int numUrls);
static double calculatePreviousPageRank(Graph url, double *previousPRArray, 
                                        int i, int numUrls);
static double calculateSumOfDiff(double *pageRank, double *previousPageRank,
                                 int numUrls);
static void populateOutdegree(Graph urlGraph, int *outDegree, int numUrls);
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

    // Read pages from the collection in file collection.txt and build a 
    // graph structure using a graph representation
    FILE *collectionFile = fopen("collection.txt", "r");
    char *urlList[MAX];
    char tempBufferString[MAX];

    GetCollection(collectionFile, tempBufferString, urlList);
    Graph urlGraph = GetGraph();

    int numUrls = CheckNumberUrls();
    double numUrlsFloat = (double)numUrls;
    double pageRank[numUrls];
    double previousPageRank[numUrls];
    double sumOfDiff = 0.0;

    // set the pagerank arrays' to 1/n
    initialisePageRankArray(pageRank, previousPageRank, numUrls, numUrlsFloat);

    // Here, we will calculate the pageRanks and pass them into the pageRank 
    // array at a particular index
    int iteration = 0;
    double diff = diffPR;
    while (iteration < maxIterations && diff >= diffPR) 
    {
        sumOfDiff = 0.0;
        updatePreviousPageRankArray(pageRank, previousPageRank, numUrls);

        for (int i = 0; i < numUrls; i++) 
        {
            double previousWeightedPageRank = calculatePreviousPageRank(
                urlGraph, previousPageRank, i, numUrls);
            pageRank[i] =
                ((1.0 - d) / (numUrlsFloat)) + (d * previousWeightedPageRank);
        }

        sumOfDiff = calculateSumOfDiff(pageRank, previousPageRank, numUrls);
        diff = sumOfDiff;
        iteration++;
    }

    int outDegree[numUrls];
    populateOutdegree(urlGraph, outDegree, numUrls);

    // print the urls, outdegrees and pageRanks 
    sortDescendingPrint(pageRank, outDegree, numUrls, urlList);

    // finally free the urls and graph 
    FreeUrlsArray(urlList, numUrls);
    freeGraph(urlGraph);
}

/**
 * @brief - The following function finds the weighted inLinks to the given
 * graph as given by the formula in:
 * https://cgi.cse.unsw.edu.au/~cs2521/22T3/ass/ass2/resources/Weighted-PageRank-Algorithm.pdf
 * 
 * ^ the url above is more than 80 lines to make it easier for the marker to 
 * access
 * 
 * @param g - Graph of interest 
 * @param v - Vertex of interest 
 * @param w - Vertex of interest
 * @return double - number of weighted inlinks 
 */
static double findWeightedInlinks(Graph g, Vertex v, Vertex w) 
{
    return numLinksToPage(g, w) / numLinksToReference(g, v);
}

/**
 * @brief - The following function finds the number links a page has 
 * 
 * @param g - Graph of interest 
 * @param v - Vertex of interest 
 * @return double - total links 
 */
static double numLinksToPage(Graph g, Vertex v) {
    double total = 0;
    int numUrls = CheckNumberUrls();
    for (int i = 0; i < numUrls; i++) 
    {
        if (i != v && GraphCheckAdjacent(g, i, v)) 
        {
            total++;
        }
    }
    return total;
}

/**
 * @brief - The number of links to the reference page 
 * 
 * @param g - Graph of interest 
 * @param w - Vertex of interest 
 * @return double 
 */
/**
 * 
*/
static double numLinksToReference(Graph g, Vertex w) 
{
    double total = 0;
    int numUrls = CheckNumberUrls();

    for (int i = 0; i < numUrls; i++) 
    {
        if (i != w && GraphCheckAdjacent(g, w, i)) 
        {
            total += numLinksToPage(g, i);
        }
    }
    return total;
}

/**
 * @brief - The following function finds the weighted Outlinks of the given
 * graph as given by the formula in:
 * https://cgi.cse.unsw.edu.au/~cs2521/22T3/ass/ass2/resources/Weighted-PageRank-Algorithm.pdf
 * 
 * ^ the url above is more than 80 lines to make it easier for the marker to 
 * access
 * 
 * @param g - Graph of interest 
 * @param v - Vertex of interest
 * @param w - Vertex of interest 
 * @return double - weighted outlink 
 */
static double findWeightedOutlinks(Graph g, Vertex v, Vertex w) 
{
    return numOutlinksFromPage(g, w) / numOutLinksFromReference(g, v);
}

/**
 * @brief - Finds the number of outlinks from a given page 
 * 
 * @param g - Graph of interest 
 * @param v - Vertex of interest 
 * @return double - number of outlinks from a page 
 */
static double numOutlinksFromPage(Graph g, Vertex v) 
{
    double total = 0;
    int numUrls = CheckNumberUrls();

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

/**
 * @brief - Finds the number of outlinks from a given reference 
 * 
 * @param g - Graph of interest
 * @param w - Vertex of interest 
 * @return double - number of outlinks from the reference 
 */
static double numOutLinksFromReference(Graph g, Vertex w) 
{
    double total = 0;
    int numUrls = CheckNumberUrls();

    for (int i = 0; i < numUrls; i++) 
    {
        if (i != w && GraphCheckAdjacent(g, w, i)) 
        {
            total += numOutlinksFromPage(g, i);
        }
    }
    return total;
}

/**
 * @brief - The following function will swap the pageRank, then the OutDegree 
 * and finally the given Url
 * 
 * @param tempPr - tempPr to make the swap
 * @param pageRank - pageRank to be swapped 
 * @param tempOutdegree - tempOutdegree to make the swap 
 * @param outDegree - outDegree to be swapped 
 * @param tempUrlList - tempUrlList to make the swap
 * @param urlList - Url that is being swapped 
 * @param i - i'th index 
 * @param j - j'th index 
 */
static void swapElementsInArray(double tempPr, double *pageRank, 
                                int tempOutdegree, int *outDegree, 
                                char *tempUrlList, char **urlList,
                                int i, int j) 
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

/**
 * @brief - The following function will sort in descending order by Weighted 
 * PageRank. Pages with the same Weighted PageRank are sorted in increasing 
 * alphabetical order by URL
 * 
 * @param pageRank - PageRank array
 * @param outDegree - OutDegree array 
 * @param len - length of urls 
 * @param urlList - Url array 
 * @param tempPr - tempPr to swap pageRanks
 * @param tempOutdegree - tempOutdegree to swap outdegrees 
 * @param tempUrl - tempUrlList to swap the given urls 
 */
static void sortPageRank(double *pageRank, int *outDegree, int len, char **url,
                         double tempPr, int tempOutdegree,
                         char *tempUrl) 
{
    // the following code will sort in descending order by Weighted PageRank
    for (int i = 0; i < len; i++) 
    {
        for (int j = i + 1; j < len; j++) 
        {
            if (pageRank[i] < pageRank[j]) 
            {
                swapElementsInArray(tempPr, pageRank, tempOutdegree, outDegree,
                                    tempUrl, url, i, j);
            }
        }
    }

    // the following code will sort pages with the same Weighted PageRank in 
    //increasing alphabetical order by URL
    for (int i = 0; i < len; i++) 
    {
        for (int j = i + 1; j < len; j++) 
        {
            if (pageRank[i] == pageRank[j]) 
            {
                if (strcmp(url[i], url[j]) > 0) 
                {
                    swapElementsInArray(tempPr, pageRank, tempOutdegree,
                                        outDegree, tempUrl, url, i, j);
                }
            }
        }
    }
}

/**
 * @brief - The following code will print out url, outdegree and pagerank in 
 * the correct order as determined by the sortPageRank function.
 * 
 * @param pageRank - PageRank array 
 * @param outDegree - OutDegree array
 * @param len - length of urls 
 * @param urlList - url array 
 */
static void sortDescendingPrint(double *pageRank, int *outDegree, int len,
                                char **urlList) 
{
    double pageRankTemp = 0.0;
    int outDegreeTemp = 0;
    char *urlListTemp = 0;

    sortPageRank(pageRank, outDegree, len, urlList, pageRankTemp, 
                 outDegreeTemp,
                 urlListTemp);

    for (int k = 0; k < len; k++) 
    {
        printf("%s %d %.7f\n", urlList[k], outDegree[k], pageRank[k]);
    }
}

/**
 * @brief - The following function will initialise everything in the pageRank
 * and previousPageRank array as 1 / n
 * 
 * @param pageRank - pageRank Array
 * @param previousPageRank - array that holds the previous pageranks
 * @param numUrls - number of urls 
 * @param numUrlsFloat - number of urls as a double value 
 */
static void initialisePageRankArray(double *pageRank, double *previousPageRank,
                                    int numUrls, double numUrlsFloat) 
{
    for (int i = 0; i < numUrls; i++) 
    {
        pageRank[i] = (1.0 / numUrlsFloat);
        previousPageRank[i] = (1.0 / numUrlsFloat);
    }
}

/**
 * @brief - The following function will update the previousPageRank array with 
 * the values of the current pageRank 
 * 
 * @param pageRank - pageRank array 
 * @param previousPageRank - previous pageRank array
 * @param numUrls - number of urls 
 */
static void updatePreviousPageRankArray(double *pageRank, 
                                        double *previousPageRank, int numUrls) 
{
    for (int j = 0; j < numUrls; j++) 
    {
        previousPageRank[j] = pageRank[j];
    }
}

/**
 * @brief - Calculate the previous pageRank as given by the formula in: 
 * https://cgi.cse.unsw.edu.au/~cs2521/22T3/ass/ass2/resources/Weighted-PageRank-Algorithm.pdf
 * 
 * ^ the url above is more than 80 lines to make it easier for the marker to 
 * access
 * 
 * @param url - graph holding the url 
 * @param previousPRArray - previous pageRank array 
 * @param i - i'th index 
 * @param numUrls - number of urls 
 * @return double - returns the previousPageRank 
 */
static double calculatePreviousPageRank(Graph url, double *previousPRArray, 
                                        int i, int numUrls) 
{
    double previousPR = 0.0;
    for (int j = 0; j < numUrls; j++) 
    {
        if (i != j && GraphCheckAdjacent(url, j, i)) 
        {
            previousPR = previousPR + (previousPRArray[j] * 
                                       findWeightedInlinks(url, j, i) *
                                       findWeightedOutlinks(url, j, i));
        }
    }
    return previousPR;
}

/**
 * @brief - The following function will calculate the sum of diff as given in 
 * the assignment 2 spec here:
 * https://cgi.cse.unsw.edu.au/~cs2521/22T3/assignments/ass2
 * 
 * @param pageRank - Pagerank array
 * @param previousPageRank - previousPageRank array 
 * @param numUrls - number of urls 
 * @return double - returns the new diff value after applying the formula 
 */
static double calculateSumOfDiff(double *pageRank, double *previousPageRank,
                                 int numUrls) 
{
    double sumOfDiff = 0.0;
    for (int k = 0; k < numUrls; k++) 
    {
        sumOfDiff = sumOfDiff + fabs(pageRank[k] - previousPageRank[k]);
    }
    return sumOfDiff;
}

/**
 * @brief - The following function populates the outDegree array with 
 * appropriate values
 * 
 * @param urlGraph - the graph we need to insert into
 * @param outDegree - outDegree array 
 * @param numUrls - number of urls 
 */
static void populateOutdegree(Graph urlGraph, int *outDegree, int numUrls) 
{
    for (int i = 0; i < numUrls; i++) 
    {
        outDegree[i] = (int)numOutlinksFromPage(urlGraph, i);
    }
}