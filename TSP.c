#include "TSP.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Define the maximum number of cities
#define MAX_CITIES 10

// Define the structure for a city
typedef struct {
    double x, y;
} City;

// Global variables for TSP
City cities[MAX_CITIES];
int numCities;
int bestPath[MAX_CITIES];
double bestCost = INT_MAX;

// Function to calculate the Euclidean distance between two cities
double calculateDistance(City city1, City city2) {
    return sqrt(pow(city1.x - city2.x, 2) + pow(city1.y - city2.y, 2));
}

// Function to check if a city is already in the path
int isVisited(int* path, int city, int n) {
    for (int i = 0; i < n; i++) {
        if (path[i] == city) {
            return 1; // City is already visited
        }
    }
    return 0; // City is not visited
}

// Function to solve the TSP using recursive backtracking
void solveTSP(int* path, int level, double currentCost) {
    if (level == numCities) {
        // Completed a full tour, check if it's the best so far
        currentCost += calculateDistance(cities[path[level - 1]], cities[path[0]]); // Return to the starting city
        if (currentCost < bestCost) {
            bestCost = currentCost;
            memcpy(bestPath, path, sizeof(int) * numCities);
        }
    } else {
        // Try visiting each unvisited city
        for (int i = 0; i < numCities; i++) {
            if (!isVisited(path, i, level)) {
                path[level] = i;
                double newCost = currentCost + (level == 0 ? 0 : calculateDistance(cities[path[level - 1]], cities[i]));
                solveTSP(path, level + 1, newCost);
            }
        }
    }
}

// Modify your aStarSearch function to solve the TSP using A*
void tspAStar(int grid[][COL], Pair src) {
    // Assuming that cities[] array is populated with the coordinates of cities

    // Set the number of cities
    numCities = 4;  // Adjust this based on the actual number of cities

    // Initialize the path array
    int path[MAX_CITIES];
    memset(path, -1, sizeof(int) * MAX_CITIES);

    // Start the TSP from the source city
    path[0] = src.first;

    // Solve the TSP using recursive backtracking
    solveTSP(path, 1, 0.0);

    // Output the best path and cost
    printf("Best TSP Path: ");
    for (int i = 0; i < numCities; i++) {
        printf("%d ", bestPath[i]);
    }
    printf("\nBest TSP Cost: %f\n", bestCost);
}

