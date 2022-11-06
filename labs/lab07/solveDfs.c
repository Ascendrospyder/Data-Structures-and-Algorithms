// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

bool checkIfValid(Maze m, Cell w)
{
    int height = MazeHeight(m); 
    int width = MazeWidth(m); 

    if (w.row >= 0 && w.row < height && w.col >= 0 && w.col < width && MazeIsWall(m, w) == false) 
    {
        return true; 
    } else {
        return false;
    }
}


bool checkAdjacent(Maze m, Cell w, Cell v)
{
    Cell up = {w.row + 1, w.col}; 
    Cell down = {w.row - 1, w.col}; 
    Cell left = {w.row, w.col - 1}; 
    Cell right = {w.row, w.col + 1}; 

    // to check if adjacent check up, down, right and left 

    if (checkIfValid(m, v) && checkIfValid(m, w))
    {
        if (checkIfValid(m, up) == true)
        {
            if (up.row == v.row && up.col == v.col)
            {
                return true; 
            }
        }

        if (checkIfValid(m, down) == true)
        {
            if (down.row == v.row && down.col == v.col)
            {
                return true; 
            }
        }

        if (checkIfValid(m, left))
        {
            if (left.row == v.row && left.col == v.col)
            {
                return true; 
            }
        }

        if (checkIfValid(m, right))
        {
            if (right.row == v.row && right.col == v.col)
            {
                return true; 
            }
        }
    }
    return false; 
}

void freeMaze(Cell **predMatrix, bool **boolMatrix)
{
    freeBoolMatrix(boolMatrix); 
    freeCellMatrix(predMatrix); 
}

bool findPathDfs(Maze m, Cell **predMatrix, bool **boolMatrix, Cell v)
{
    MazeVisit(m, v);
    boolMatrix[v.row][v.col] = true;  

    for (int row = 0; row < MazeHeight(m); row++)
    {
        for (int col = 0; col < MazeWidth(m); col++)
        {
            Cell w = {.row = row, .col = col}; 
            if (checkAdjacent(m, v, w)) 
            {
                if (MazeVisit(m, w))
                {
                    MazeMarkPath(m, w); 
                    predMatrix[w.row][w.col] = v; 
                    Cell start = MazeGetStart(m); 

                    while (w.row != start.row || w.col != start.col)
                    {
                        MazeMarkPath(m, w); 
                        v = predMatrix[w.row][w.col]; 
                    }   

                    MazeMarkPath(m, start); 
                    return true;
                } else if (boolMatrix[w.row][w.col] == false) {
                    predMatrix[w.row][w.col] = v;

                    if (findPathDfs(m, predMatrix, boolMatrix, w))
                    {
                        return true; 
                    } 
                }
            }
        }
    }
    return false; 
}

bool solve(Maze m) {
    bool **visited = createBoolMatrix(MazeHeight(m), MazeWidth(m)); 
    Cell **predMatrix = createCellMatrix(MazeHeight(m), MazeWidth(m));
    Cell start = MazeGetStart(m); 
    bool foundPath = false;
    foundPath = findPathDfs(m, predMatrix, visited, start); 
    freeMaze(predMatrix, visited); 
    return foundPath;
}

