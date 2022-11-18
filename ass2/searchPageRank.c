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
        if (strcmp(buffer, urls[i]) == 0) return true;
    }
    return false;
}

void populatePageRankArray(FILE *pagerankFile, double *pageRanks, char **urls, char *tempUrlBuffer, char *newLineBuffer, int j, int i)
{
    // if the urls are the same go an appened it to our pageRankArray
    if (strcmp(urls[i], tempUrlBuffer) == 0)
    {
        // load the file contents into tempUrlBuffer and load every instance of a 
        // newline into the newLineBuffer 
        while (fscanf(pagerankFile, "%s%[ \n]", tempUrlBuffer, newLineBuffer) != EOF)
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

void swapElementsInArray(char *tempUrls, char **urls, int temp, int *countUrls, double tempPR, double *pageRank, int i, int j)
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

void sortPageRank(double *pageRank, int *countUrls, char **urls, double tempPR, int temp, char *tempUrls, int numUrls)
{
    // tested and works 
    for (int i = 0; i < numUrls; i++)
    {
        for (int j = i + 1; j < numUrls; j++)
        { 
            if (countUrls[i] < countUrls[j])
            {
                printf("FIRST LOOP: url[i] = %s\turl[j] = %s\tcountUrl[i] = %d\tcountUrl[j] = %d\tpageRank[i] = %.7f\tpageRank[j] = %.7f\n", urls[i], urls[j], countUrls[i], countUrls[j], pageRank[i], pageRank[j]);
                swapElementsInArray(tempUrls, urls, temp, countUrls, tempPR, pageRank, i, j); // potential bug 
            }
        }
    }

    //tested and works 
    for (int i = 0; i < numUrls; i++)
    {
        for (int j = i + 1; j < numUrls; j++)
        { 
            
            if (countUrls[i] == countUrls[j] && pageRank[i] < pageRank[j])
            {
                swapElementsInArray(tempUrls, urls, temp, countUrls, tempPR, pageRank, i, j); 
            }
        }
    }

    for (int i = 0; i < numUrls; i++)
    {
        for (int j = i + 1; j < numUrls; j++)
        {
            if (countUrls[i] == countUrls[j] && pageRank[i] == pageRank[j])
            {
                if (strcmp(urls[i], urls[j]) > 0)
                {
                    swapElementsInArray(tempUrls, urls, temp, countUrls, tempPR, pageRank, i, j); 
                }
            }
        }
    }
}


double *findPageRanks(char **urls, int length)
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
    int *countUrls = NULL; 
    char tempWordBuffer[MAX];  
    char newLineBuffer[MAX];  
    int numWords = 0; 
    int numUrls = 0; 
    FILE *wordFile = fopen("invertedIndex.txt", "r");


    for (int i = 1; i < argc; i++)
    {
        words = realloc(words, (numWords + 1) * sizeof(char *)); 
        words[numWords] = malloc(strlen(argv[i]) + 1); 
        strcpy(words[numWords++], argv[i]); 
        // printf("num words = %d\n", numWords); 
    }

    // for (int i = 0; i < numWords; i++)
    // {
    //     printf("words scanned in from command line: %s\n", words[i]);
    // }


    while (fscanf(wordFile, "%s", tempWordBuffer) != EOF)
    {
        for (int k = 0; k < numWords; k++)
        {
            if (strcmp(words[k], tempWordBuffer) == 0)
            {   
                 
                while (fscanf(wordFile, "%s%[ \n]", tempWordBuffer, newLineBuffer) != EOF)
                { 
                    int index = 0; 
                    for (index = 0; index < numUrls; index++)
                    {
                        if (strcmp(urls[index], tempWordBuffer) == 0)
                        {
                            countUrls[index] = countUrls[index] + 1; 
                            break; 
                        }
                    }

                    if (index == numUrls)
                    {
                        urls = realloc(urls, (numUrls + 1) * sizeof(char *));
                        countUrls = realloc(countUrls, (numUrls + 1) * sizeof(int));  
                        urls[index] = malloc(strlen(tempWordBuffer) + 1); 
                        
                        strcpy(urls[numUrls], tempWordBuffer); 
                        countUrls[index] = 1;   
                        numUrls++; 
                    }

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

    // for (int i = 0; i < numUrls; i++)
    // {
    //     printf("urls = %s\tnumMatching = %d\n", urls[i], countUrls[i]); 
    // }

    sortPageRank(pagerankOfInterest, countUrls, urls, tempPR, temp, tempUrls, numUrls); 
    
    // printPageRanks(pagerankOfInterest, urls, numUrls); 
    
    // if (numUrls < 30)
    // {
        for (int j = 0; j < numUrls && j < 30; j++)
        {
            printf("%s\n", urls[j]); 
        }
    // }

    free(pagerankOfInterest);
    freeUrls(urls, numUrls); 
    freeUrls(words, numWords); 
    free(countUrls); 
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