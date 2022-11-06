// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Place.h"
#include "PQ.h"

////////////////////////////////////////////////////////////////////////
// Your task

double findDistanceBetweenPlace(Place placeOne, Place placeTwo)
{
    return sqrt((placeOne.x - placeTwo.x) * (placeOne.x - placeTwo.x) + 
    (placeOne.y - placeTwo.y) * (placeOne.y - placeTwo.y)); 
}

void freeGraph(Graph g, Graph mst)
{
    // finally free everything 
    GraphFree(mst); 
    GraphFree(g); 
}

int findMinimumCost(int numCities, Place cities[], Place powerPlant, 
                    PowerLine powerLines[], Graph g, Graph mst)
{
    int cost = 0; 
    for (int i = 0; i < numCities; i++)
    {
        if (GraphIsAdjacent(mst, i, numCities))
        {
            cost++; 
            PowerLine newPowerLine = {cities[i], powerPlant}; 
            powerLines[cost - 1] = newPowerLine; 
        }

        for (int j = i + 1; j < numCities; j++)
        {
            if (GraphIsAdjacent(mst, i, j))
            {
                cost++; 
                PowerLine newPowerLine = {cities[i], cities[j]}; 
                powerLines[cost - 1] = newPowerLine; 
            }
        }
    }   
    return cost; 
}

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid1(Place cities[], int numCities, Place powerPlant,
              PowerLine powerLines[]) {
    // TODO: Complete this function

    Graph g = GraphNew(numCities + 1); // create a new graph with numCities + 1 vertices 

    // loop through the cities array and finds mst from powerplant 
    for (int i = 0; i < numCities; i++)
    {
        // the following code inserts the findDistanceBetweenPlace into graph 
        double dist = findDistanceBetweenPlace(cities[i], powerPlant); 
        Edge distEdge = {i, numCities, dist}; 
        GraphInsertEdge(g, distEdge); 

        for (int j = i + 1; j < numCities; j++)
        {
            dist = findDistanceBetweenPlace(cities[i], cities[j]); 
            Edge new = {i, j, dist}; 
            GraphInsertEdge(g, new); 
        }
    }

    // create a new mst graph 
    Graph mst = GraphMST(g);
    int count = findMinimumCost(numCities, cities, powerPlant, powerLines, g, mst); 
    freeGraph(g, mst);
    return count;
} // done and tested 

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(Place cities[], int numCities,
              Place powerPlants[], int numPowerPlants,
              PowerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
