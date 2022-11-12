// COMP2521 Assignment 2

// Written by: Arindam Mukherjee 
// Date: 06/11/2022

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

#define MAX 1000 

void freeUrls(char **urls, int len)
{
    for (int i = 0; i < len; i++)
    {
        free(urls[i]); 
    }
    free(urls); 
}

bool checkFileInUrls(char **urls, char *buffer, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (strcmp(buffer, urls[i]) == 0)
        {
            return true; 
        }
    }
    return false;
}

void populatePageRankArray(FILE *pagerankFile, double *pageRanks, char **urls, char *tempUrlBuffer, char *newLineBuffer, int j, int i)
{
    if (strcmp(urls[i], tempUrlBuffer) == 0)
    {
        while (fscanf(pagerankFile, "%s%[ \t\n]", tempUrlBuffer, newLineBuffer) == 2)
        {
            if (strchr(newLineBuffer, '\n'))
            {
                pageRanks[i] = atof(tempUrlBuffer); 
                break; 
            }
        }
        j++; 
    }
}

void sortPageRank(double *pageRank, char **urls, double tempPR, char *tempUrls, int len, int i)
{
    for (int j = 0; j < len - i - 1; j++)
    {   
        if (pageRank[j] < pageRank[j + 1])
        {
            // swap pageRank --> urls 
            tempPR = pageRank[j]; 
            pageRank[j] = pageRank[j + 1]; 
            pageRank[j + 1] = tempPR; 

            tempUrls = urls[j]; 
            urls[j] = urls[j + 1]; 
            urls[j + 1] = tempUrls; 
        }
    }
}

double *searchPageRanks(char **urls, int len)
{
    double *pageRanks = malloc(sizeof(double) * len); 
    char tempUrlBuffer[MAX]; 
    char newlineBuffer[MAX]; 
    FILE *pagerankFile = fopen("pageRankList.txt", "r"); 
 
    int i = 0; 
    while (fscanf(pagerankFile, "%s", tempUrlBuffer) != EOF && i < len)
    {
        for (int j = 0; j < len; j++)
        {
            /*if (strcmp(urls[i], tempUrlBuffer) == 0)
            {
                while (fscanf(pagerankFile, "%s%[ \t\n]", tempUrlBuffer, newlineBuffer) == 2)
                {
                    if (strchr(newlineBuffer, '\n'))
                    {
                        pageRanks[i] = atof(tempUrlBuffer); 
                        break; 
                    }
                }
                j++; 
            }*/ 
            populatePageRankArray(pagerankFile, pageRanks, urls, tempUrlBuffer, newlineBuffer, j, i); 
        }
    }
    fclose(pagerankFile); 
    return pageRanks; 
}



int main(int argc, char *argv[]) 
{
    if (argc < 2)
    {
        fprintf(stderr, "Please enter one or more inputs!"); 
        exit(EXIT_FAILURE); 
    }

    char **words = NULL; 
    char **urls = NULL; 
    char tempWordBuffer[MAX];  
    char newLineBuffer[MAX];  
    int numWords = 0; 
    int numUrls = 0; 
    int j = 0; 
    FILE *wordFile = fopen("invertedIndex.txt", "r");

    for (int i = 0; i < argc - 1; i++)
    {
        words = realloc(words, (numWords + 1) * sizeof(char *)); 
        words[numWords] = malloc(strlen(argv[i]) + 1); 
        strcpy(words[numWords++], argv[i]); 
    }

    while (fscanf(wordFile, "%s", tempWordBuffer) != EOF && j < numWords)
    {
        for (int k = 0; k < numWords; k++)
        {
            if (strcmp(words[k], tempWordBuffer) == 0)
            {
                while (fscanf(wordFile, "%s%[ \t\n]", tempWordBuffer, newLineBuffer) == 2)
                {
                    if (!checkFileInUrls(urls, tempWordBuffer, numUrls))
                    {
                        urls = realloc(urls, (numUrls + 1) * sizeof(char *)); 
                        urls[numUrls] = malloc(strlen(tempWordBuffer) + 1); 
                        strcpy(urls[numUrls++], tempWordBuffer); 
                        if (strchr(newLineBuffer, '\n'))
                        {
                            break; 
                        }
                    }
                    j++; 
                }
            }
        }
    }
    fclose(wordFile); 

    double tempPR = 0.0; 
    char *tempUrls = NULL; 
    double *pagerankOfInterest = malloc(numUrls * sizeof(double)); 
    pagerankOfInterest = searchPageRanks(urls, numUrls);

    for (int i = 0; i < numUrls; i++)
    {
        sortPageRank(pagerankOfInterest, urls, tempPR, tempUrls, numUrls, i); 
    }

    if (numUrls < 30)
    {
        for (int j = 0; j < numUrls && j < 30; j++)
        {
            printf("%s\n", urls[j]); 
        }
    }

    freeUrls(urls, numUrls); 
    freeUrls(words, numWords); 
}

