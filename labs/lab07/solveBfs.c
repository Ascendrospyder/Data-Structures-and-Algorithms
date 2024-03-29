// BFS maze solver
// written by Arindam Mukherjee z5421641 
// date: 29/10/2022

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Queue.h"

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

void freeMaze(Cell **predMatrix, bool **boolMatrix, Queue q)
{
    freeBoolMatrix(boolMatrix); 
    freeCellMatrix(predMatrix); 
    QueueFree(q); 
}

/**
 * @brief - which takes in a maze and tries to find a path from start to finish 
 * using the breadth-first search algorithm. If there is a path, the function 
 * should mark the path on the maze using the MazeMarkPath() function and 
 * return true. Otherwise, the function should return false.
 * 
 * @param m 
 * @return true 
 * @return false 
 */
bool solve(Maze m) {
    // TODO: Complete this function 
    bool **visited = createBoolMatrix(MazeHeight(m), MazeWidth(m)); 
    Cell ** predMatrix = createCellMatrix(MazeHeight(m), MazeWidth(m));
    Cell start = MazeGetStart(m); 
    bool foundPath = false;
    Cell v; 


    // set the start as visited 
    visited[start.row][start.col] = true; 

    Queue q = QueueNew(); 
    QueueEnqueue(q, start);

    while (!QueueIsEmpty(q))
    {
        v = QueueDequeue(q);
        if (MazeVisit(m, v) == true)
        {
            while (v.row != start.row || v.col != start.col)
            {
                MazeMarkPath(m, v); 
                v = predMatrix[v.row][v.col]; 
            }
            MazeMarkPath(m, start); 
            MazeMarkPath(m, v);  
            freeMaze(predMatrix, visited, q); 
            foundPath = true; 
            return foundPath; 
        } else {
            for (int row = 0; row < MazeHeight(m); row++)
            {
                for (int col = 0; col < MazeWidth(m); col++)
                {
                    Cell w = {.row = row, .col = col}; 
                    if (visited[w.row][w.col] == false && checkAdjacent(m, v, w)) 
                    {
                        predMatrix[w.row][w.col] = v; 
                        MazeVisit(m, w);
                        visited[w.row][w.col] = true; 
                        QueueEnqueue(q, w); 
                    }
                }
            }
        }   
    } 
    freeMaze(predMatrix, visited, q); // free the maze after 
    return foundPath;
}

