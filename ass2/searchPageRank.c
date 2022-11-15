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

// struct urlsInformation {
//     int numMatchingTerms; 
// }; 



///////////////////////////////////// delete later /////////////////////////////////////////////////////
void printPageRanks(double *pageRanks, char **urls, int numUrls); 
///////////////////////////////////// delete later /////////////////////////////////////////////////////

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
    // if the urls are the same go an appened it to our pageRankArray
    if (strcmp(urls[i], tempUrlBuffer) == 0)
    {
        while (fscanf(pagerankFile, "%s%[ \n]", tempUrlBuffer, newLineBuffer) != EOF)
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

void sortPageRank(double *pageRank, int *numMatching, char **urls, double tempPR, int temp, char *tempUrls, int len, int i)
{
    for (int j = 0; j < len - i - 1; j++)
    {   
        if (numMatching[j] < numMatching[j + 1])
        {
            // swap pageRank --> urls 
            temp = numMatching[j]; 
            numMatching[j] = numMatching[j + 1]; 
            numMatching[j + 1] = temp; 

            tempPR = pageRank[j]; 
            pageRank[j] = pageRank[j + 1]; 
            pageRank[j + 1] = tempPR; 

            tempUrls = urls[j]; 
            urls[j] = urls[j + 1]; 
            urls[j + 1] = tempUrls; 
        }
    } 
}

double *findPageRanks(char **urls, int len)
{
    double *pageRanks = malloc(sizeof(double) * len); 
    char tempUrlBuffer[MAX]; 
    char newlineBuffer[MAX]; 
    FILE *pagerankFile = fopen("pageRankList.txt", "r"); 
 
    int j = 0; 
    while (fscanf(pagerankFile, "%s", tempUrlBuffer) != EOF && j < len)
    {
        for (int i = 0; i < len; i++)
        {   
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
        fprintf(stderr, "Please enter one or more inputs!\n"); 
        exit(EXIT_FAILURE); 
    }

    char **words = NULL; 
    char **urls = NULL; 
    char tempWordBuffer[MAX];  
    char newLineBuffer[MAX];  
    int numWords = 0; 
    int numUrls = 0; 
    int numNewLines = 0; 
    int j = 0; 
    FILE *wordFile = fopen("invertedIndex.txt", "r");

    // fixed a bug where it was printing the ./ command 
    // the following code 
    for (int i = 1; i < argc; i++)
    {
        words = realloc(words, (numWords + 1) * sizeof(char *)); 
        words[numWords] = malloc(strlen(argv[i]) + 1); 
        strcpy(words[numWords++], argv[i]); 
        printf("num words = %d\n", numWords); 
    }

    for (int i = 0; i < numWords; i++)
    {
        printf("words scanned in from command line: %s\n", words[i]);
    }
     

    while (fscanf(wordFile, "%s", tempWordBuffer) != EOF && j < numWords)
    {
        for (int k = 0; k < numWords; k++)
        {
            if (strcmp(words[k], tempWordBuffer) == 0)
            {
                while (fscanf(wordFile, "%s%[ \n]", tempWordBuffer, newLineBuffer) != EOF)
                {
                    // printf("temp word buffer: %c\n", tempWordBuffer[j]);
                    // printf("tempword buffer: %s\n", tempWordBuffer); 
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

    // printf("%d\n", numMatching); 
     
    printf("new lines: %d\n", numNewLines); 
    fclose(wordFile); 

    double tempPR = 0.0; 
    char *tempUrls = NULL; 
    int temp = 0; 
    double *pagerankOfInterest = findPageRanks(urls, numUrls);

    // the following code will get the numMatching terms for each url 
    int numMatching[MAX]; 
    int *holdMatching = malloc(sizeof(int) * numUrls); 
    int count; 
    int counter = 0; 

    for (int i = 0; i < numUrls; i++)
    {
        numMatching[i] = -1; 
    }

    for (int i = 0; i < numUrls; i++)
    {
        count = 1; 
        for (int j = i + 1; j < numUrls; j++)
        {
            if (strcmp(urls[i], urls[j]) == 0)
            {
                printf("I am here!\n"); 
                count++; 
                numMatching[j] = 0; 
            }
        }

        if (numMatching[i] != 0)
        {
            numMatching[i] = count; 
        }
    }

    for (int i = 0; i < numUrls; i++)
    {
        if (numMatching[i] != 0)
        {
            holdMatching[counter++] = numMatching[i]; 
        }
    }


    for (int i = 0; i < numUrls; i++)
    {
        printf("urls = %s\tnumMatching = %d\n", urls[i], numMatching[i]); 
    }


    // int numMatchingTerms = findNumMatchingTerms(urls, words, numUrls, numWords);
    // printf("num Macthing terms: %d\n", numMatchingTerms);  
    // int *numMatchingTerms[numUrls]; 
    // for (int i = 0; i < )

    for (int i = 0; i < numUrls; i++)
    {   
        sortPageRank(pagerankOfInterest, holdMatching, urls, tempPR, temp, tempUrls, numUrls, i); 
    }
    printPageRanks(pagerankOfInterest, urls, numUrls); 
    

    if (numUrls < 30)
    {
        for (int j = 0; j < numUrls && j < 30; j++)
        {
            printf("%s\n", urls[j]); 
        }
    }

    free(pagerankOfInterest);
    freeUrls(urls, numUrls); 
    freeUrls(words, numWords); 
}

//////////////////////////////// debugging function //////////////////////////////
void printPageRanks(double *pageRanks, char **urls, int numUrls)
{
    for (int i = 0; i < numUrls; i++)
    {
        printf("url = %s\tpageRank: %.7f\n", urls[i], pageRanks[i]); 
    }
}
//////////////////////////////// debugging function //////////////////////////////