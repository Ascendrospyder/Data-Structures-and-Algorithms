
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

static void preorder(BSTree t, int *array, int temporary); 

int minDiff(BSTree t, int l) {
    // TODO
    int *tempArray = malloc(sizeof(int*) * 10000); 
    int temp = 0; 
    preorder(t, tempArray, temp); 
    int result = 1000; 

    for (int i = temp - 1; i - 1 >= 0; i--)
    {
        if (result > (tempArray[i] - tempArray[i - 1]))
        {
            result = tempArray[i] - tempArray[i - 1]; 
        }
    }
    return result; 
}

static void preorder(BSTree t, int *array, int temporary)
{
    if (t == NULL)
    {
        return; 
    }
    preorder(t->left, array, temporary); 
    array[temporary++] = t->key; 
    preorder(t->right, array, temporary); 
}

int* a;
int temp;
void preorder(struct TreeNode* root)
{
    if(root==NULL) return;
    preorder(root->left);
    a[temp++]=root->val;
    preorder(root->right);
}
int getMinimumDifference(struct TreeNode* root) {
    a=(int*)malloc(sizeof(int)*10000);
    temp=0;
    preorder(root);
    int result=1000;
    for(int i=temp-1;i-1>=0;i--) //this loop can write in preorder();
    {
        if(result>(a[i]-a[i-1]))
            result=a[i]-a[i-1];
    }
    return result;
}
