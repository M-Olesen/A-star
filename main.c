#include <stdio.h>
#include "Search.h"
#include <math.h>
#include <string.h>
#include "InputOutput.h"


#define ROW 9
#define COL 10

/* Description of the Grid-
     1--> The cell is not blocked
     0--> The cell is blocked    */
    /*int grid[ROW][COL] = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };
            */

int main()
{
    clear_output_file();

    int grid[ROW][COL];

    input(grid);
 
    // Source is the left-most bottom-most corner
    Pair src = {8, 0};
 
    // Destination is the left-most top-most corner
    Pair dest = {0, 9};
 
    aStarSearch(grid, src, dest);

    tspAStar(grid, src);
 
    return (0);
}
