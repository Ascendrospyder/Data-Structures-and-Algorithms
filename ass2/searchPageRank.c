// COMP2521 Assignment 2

// Written by: Arindam Mukherjee
// zId: z5421641
// Date: 06/11/2022
/*	
	Description: The program should take search terms as command-line 
	arguments, find pages with one or more matching search terms and 
	output the top 30 pages in descending order of the number of 
	matching search terms to stdout. Pages with the same number of 
	matching search terms should be sorted in descending order by 
	their Weighted PageRank. Pages with the same number of matching 
	search terms and the same Weighted PageRank should be sorted in 
	increasing alphabetical order by URL.
*/ 

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

#define MAX 1000
#define MAX_URLS_PRINT 30

///////////////////////////////////// function prototypes ////////////////////
static void freeUrls(char **urls, int len); 
static void populatePageRankArray(FILE *pagerankFile, double *pageRanks, 
								  char **urls, char *tempUrlBuffer, 
								  char *newLineBuffer, int j, int i); 
static void swapElementsInArray(char *tempUrls, char **urls, int temp, 
								int *countUrls,
                         		double tempPR, double *pageRank, 
								int i, int j); 
static void sortPageRank(double *pageRank, int *countUrls, char **urls, 
						 double tempPR, int temp, char *tempUrls, 
						 int numUrls); 
static double *findPageRanks(char **urls, int length); 
static void printRelevantUrls(char **urls, int numUrls); 
///////////////////////////////////// function prototypes //////////////////

int main(int argc, char *argv[]) 
{
	if (argc < 2) {
		fprintf(stderr, "Please enter one or more inputs!\n");
		exit(EXIT_FAILURE);
	}

	char **words = NULL;
	char **urls = NULL;
	int *countUrls = NULL;
	char tempWordBuffer[MAX];
	char newLineBuffer[MAX];
	int numWords = 0;
	int numUrls = 0;
	FILE *wordFile = fopen("invertedIndex.txt", "r");

	// this will read arguments from the command line and load it into our word
	// array 
	for (int i = 1; i < argc; i++) 
	{
		words = realloc(words, (numWords + 1) * sizeof(char *));
		words[numWords] = malloc(strlen(argv[i]) + 1);
		strcpy(words[numWords++], argv[i]);
	}

	while (fscanf(wordFile, "%s", tempWordBuffer) != EOF) 
    {
		for (int k = 0; k < numWords; k++) 
        {
			if (strcmp(words[k], tempWordBuffer) == 0) 
            {
				// read from our wordFile and store all the contents into 
				// our tempWordBuffer and load every instance of a newline into
				// our newline buffer 
				while (fscanf(wordFile, "%s%[ \n]", tempWordBuffer,
				              newLineBuffer) != EOF) 
                {
					int index = 0;
					// loop through all our urls and if the url already exists 
					// then go ahead and increment that particular index in our 
					// countUrl array 
					for (index = 0; index < numUrls; index++) 
                    {
						if (strcmp(urls[index], tempWordBuffer) == 0) 
						{
							countUrls[index] = countUrls[index] + 1;
							break;
						}
					}

					// if the url to be added is unique go ahead and add it 
					// and mark the numMatching terms as 1 in the countUrls 
					// array 
					if (index == numUrls) 
					{
						urls = realloc(urls, (numUrls + 1) * sizeof(char *));
						countUrls =
						    realloc(countUrls, (numUrls + 1) * sizeof(int));
						urls[index] = malloc(strlen(tempWordBuffer) + 1); 
						strcpy(urls[numUrls], tempWordBuffer);
						countUrls[index] = 1;
						numUrls++;
					}

					// for the first instance of a newline, go ahead and break 
					// out of the loop 
					if (strchr(newLineBuffer, '\n')) 
					{
						break;
					}
				}
			}
		}
	}
	fclose(wordFile);

	double tempPR = 0.0;
	char *tempUrls = NULL;
	int temp = 0;
	double *pagerankOfInterest = findPageRanks(urls, numUrls);

	// the following code will sort the pageRanks to help us in printing 
	sortPageRank(pagerankOfInterest, countUrls, urls, tempPR, temp, tempUrls,
	             numUrls);

	// the following will print out all the urls found 
    printRelevantUrls(urls, numUrls); 

	// finally free everything 
	free(pagerankOfInterest);
	freeUrls(urls, numUrls);
	freeUrls(words, numWords);
	free(countUrls);
}

//////////////////////////////// definitions //////////////////////////////

/**
 * @brief - The following function free's the url array 
 * 
 * @param urls - urls array 
 * @param len - length of urls 
 */
static void freeUrls(char **urls, int len) {
	for (int i = 0; i < len; i++) {
		free(urls[i]);
	}
	free(urls);
}

/**
 * @brief - The following function populate the page rank array with all the 
 * pageRanks. 
 * 
 * @param pagerankFile - pageRank file 
 * @param pageRanks - array holding the pagerank
 * @param urls - array holding the urls 
 * @param tempUrlBuffer - temporary buffer which holds the string of the file
 * @param newLineBuffer - temporary buffer which holds every instance of 
 * lines in the file 
 * @param j - the j'th index 
 * @param i - the i'th index 
 */
static void populatePageRankArray(FILE *pagerankFile, double *pageRanks, 
								  char **urls,
                                  char *tempUrlBuffer, char *newLineBuffer, 
								  int j, int i) 
{
	// if the urls are the same go an appened it to our pageRankArray
	if (strcmp(urls[i], tempUrlBuffer) == 0) 
    {
		// load the file contents into tempUrlBuffer and load every instance of 
		// a newline into the newLineBuffer
		while (fscanf(pagerankFile, "%s%[ \n]", tempUrlBuffer, newLineBuffer) !=
		       EOF) 
        {
			// at the first instance of a newline, go ahead and add the string
			// to the pageRank array and break out of the loop
			if (strchr(newLineBuffer, '\n')) 
			{
				pageRanks[i] = atof(tempUrlBuffer);
				break;
			}
		}
		j++;
	}
}

/**
 * @brief - The following function swaps the url, then the number of matching 
 * terms and finally the pageRanks. 
 * 
 * @param tempUrls - tempUrls which will help make the swap 
 * @param urls - array of urls 
 * @param temp - temp which will help make the swap 
 * @param countUrls - array of numMatching terms 
 * @param tempPR - tempPR which will help make the swap 
 * @param pageRank - array of all the pageRanks 
 * @param i - i'th index
 * @param j - j'th index 
 */
static void swapElementsInArray(char *tempUrls, char **urls, int temp, 
							    int *countUrls,
                                double tempPR, double *pageRank, int i, 
								int j) 
{
	tempUrls = urls[i];
	urls[i] = urls[j];
	urls[j] = tempUrls;

	temp = countUrls[i];
	countUrls[i] = countUrls[j];
	countUrls[j] = temp;

	tempPR = pageRank[i];
	pageRank[i] = pageRank[j];
	pageRank[j] = tempPR;
}

/**
 * @brief - The following code will sort the pages in descending order of the 
 * number of matching search terms to stdout. Then it will sort pages with the 
 * same number of matching search terms in descending order by their 
 * Weighted PageRank. Finally, pages with the same number of matching search 
 * terms and the same Weighted PageRank will be sorted in increasing 
 * alphabetical order by URL
 * 
 * @param pageRank - pageRank array holding the pageRanks 
 * @param countUrls - array holding the number of matching terms for each url 
 * @param urls - array of urls 
 * @param tempPR - tempPR which will help make the swap 
 * @param temp - temp which will help make the swap
 * @param tempUrls - tempUrls which will help make the swap
 * @param numUrls - number of urls
 */
static void sortPageRank(double *pageRank, int *countUrls, char **urls, 
					     double tempPR, int temp, char *tempUrls, 
						 int numUrls) 
{
	// this will sort the pages in descending order of the number of 
	// matching search terms
	for (int i = 0; i < numUrls; i++) 
    {
		for (int j = i + 1; j < numUrls; j++) 
        {
			if (countUrls[i] < countUrls[j]) 
            {
				swapElementsInArray(tempUrls, urls, temp, countUrls, tempPR,
				                    pageRank, i, j);  
			}
		}
	}

	// this will sort pages with the same number of matching search terms 
	// in descending order by their Weighted PageRank
	for (int i = 0; i < numUrls; i++) 
	{
		for (int j = i + 1; j < numUrls; j++) 
		{
			if (countUrls[i] == countUrls[j] && pageRank[i] < pageRank[j]) 
			{
				swapElementsInArray(tempUrls, urls, temp, countUrls, tempPR,
				                    pageRank, i, j);
			}
		}
	}

	// this will sort pages with the same number of matching search terms and 
	// the same Weighted PageRank in increasing alphabetical order by URL.
	for (int i = 0; i < numUrls; i++) 
	{
		for (int j = i + 1; j < numUrls; j++) 
		{
			if (countUrls[i] == countUrls[j] && pageRank[i] == pageRank[j]) 
			{
				if (strcmp(urls[i], urls[j]) > 0) {
					swapElementsInArray(tempUrls, urls, temp, countUrls, tempPR,
					                    pageRank, i, j);
				}
			}
		}
	}
}

/**
 * @brief - The following function will extract the relevant pageranks from
 * pageRankList.txt
 * 
 * @param urls - array holding the urls 
 * @param length - int length
 * @return double* - new array populated by all the pageRanks 
 */
static double *findPageRanks(char **urls, int length) 
{
	double *pageRanks = malloc(sizeof(double) * length);
	char tempUrlBuffer[MAX];
	char newlineBuffer[MAX];
	FILE *pagerankFile = fopen("pageRankList.txt", "r");

	int j = 0;
	while (fscanf(pagerankFile, "%s", tempUrlBuffer) != EOF && j < length) 
	{
		for (int i = 0; i < length; i++) 
		{
			populatePageRankArray(pagerankFile, pageRanks, urls, tempUrlBuffer,
			                      newlineBuffer, j, i);
		}
	}

	fclose(pagerankFile);
	return pageRanks;
}

/**
 * @brief - The following function will print out all the relevant urls 
 * 
 * @param urls - urls array 
 * @param numUrls - number of urls 
 */
static void printRelevantUrls(char **urls, int numUrls)
{
    for (int j = 0; j < numUrls && j < MAX_URLS_PRINT; j++) 
    {
		printf("%s\n", urls[j]);
	}
}
//////////////////////////////// definitions //////////////////////////////