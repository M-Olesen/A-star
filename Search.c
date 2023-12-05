#include <math.h>
#include <string.h>
#include "search.h"
#include "InputOutput.h"

#define ROW 9
#define COL 10
cell cellDetails[ROW][COL];
int foundDest = 0;
Set openList;
int closedList[ROW][COL];

// Function to set the current cells parrent based on a direction
void updateParrentCell(int dir, int i, int j)
{
    if (dir == 1)
    {
        cellDetails[i][j].parent_i = i + 1;
        cellDetails[i][j].parent_j = j;
    }
    else if (dir == 2)
    {
        cellDetails[i][j].parent_i = i - 1;
        cellDetails[i][j].parent_j = j;
    }
    else if (dir == 3)
    {
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j - 1;
    }
    else if (dir == 4)
    {
        cellDetails[i][j].parent_i = i;
        cellDetails[i][j].parent_j = j + 1;
    }
    else if (dir == 5)
    {
        cellDetails[i][j].parent_i = i + 1;
        cellDetails[i][j].parent_j = j - 1;
    }
    else if (dir == 6)
    {
        cellDetails[i][j].parent_i = i + 1;
        cellDetails[i][j].parent_j = j + 1;
    }
    else if (dir == 7)
    {
        cellDetails[i][j].parent_i = i - 1;
        cellDetails[i][j].parent_j = j - 1;
    }
    else
    {
        cellDetails[i][j].parent_i = i - 1;
        cellDetails[i][j].parent_j = j + 1;
    }
}

// Funtion to process a move in a direction
void process_successor(int i, int j, Pair dest, Pair src, int grid[][COL], int diagonel, int direction)
{   
    // Only run this function if the destination is NOT found
    if (foundDest == 0)
    {

        // Only process this cell if this is a valid one
        if (isValid(i, j) == 1)
        {
            // set the parrent of the cell depending if it is diagonal or not

            // If the destination cell is the same as the
            // current successor
            if (isDestination(i, j, dest) == 1)
            {
                updateParrentCell(direction, i, j);
                printf("The destination cell is found\n");
                tracePath(dest, src, grid);
                foundDest = 1;
            }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
            else if (closedList[i][j] == 0 && isUnBlocked(grid, i, j) == 1)
            {
                double gNew;
                if (diagonel == 0)
                {
                    gNew = cellDetails[i][j].g + 1.0;
                }
                else
                {
                    gNew = cellDetails[i][j].g + 1.414;
                }

                double hNew = calculateHValue(i, j, dest);
                double fNew = gNew + hNew;
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is
                // better, using 'f' cost as the measure.
                if (cellDetails[i][j].f == 2147483647 || cellDetails[i][j].f > fNew)
                {
                    Pair pair1 = {i, j};
                    pPair pPair1 = {fNew, pair1};
                    addToSet(&openList, pPair1);

                    // Update the details of this cell
                    cellDetails[i][j].f = fNew;
                    cellDetails[i][j].g = gNew;
                    cellDetails[i][j].h = hNew;
                    updateParrentCell(direction, i, j);
                }
            }
        }
    }
}
// Check if the cell is valid
int isValid(int row, int col)
{
    // Returns 1 if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}
// Check if the cell is unblocked
int isUnBlocked(int grid[][COL], int row, int col)
{
    // Returns 1 if the cell is not blocked else 0
    if (grid[row][col] == 1)
        return (1);
    else
        return (0);
}
// Check if the cell is the destination
int isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return (1);
    else
        return (0);
}
// Calculates the H value
double calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt(
        (row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

// Function to trace the path from destination to source in a grid and output the path
void tracePath(Pair dest, Pair src, int grid[][COL])
{
    // Extract the destination row and column
    int row = dest.first;
    int col = dest.second;

    // Create a stack to store the path
    struct Stack *Path = createStack(100);

    // Trace the path from destination to source until reaching the source
    while (!(cellDetails[row][col].parent_i == src.first && cellDetails[row][col].parent_j == src.second))
    {
        // Create a Pair with the current row and column and push it onto the stack
        Pair item = {row, col};
        push(Path, item);

        // Update the row and column to the parent coordinates
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    // Push the coordinates to the cell before the source onto the stack
    Pair item = {row, col};
    push(Path, item);

    // Push the source coordinates onto the stack 
    Pair item2 = {src.first, src.second};
    push(Path, item2);

    // Output the path and update the grid with the path information
    output(grid, *Path);
}
// The main funtion in the program, runs an Astar search on a grid given a source and a destination
void aStarSearch(int grid[][COL], Pair src, Pair dest)
{
    // If the source is out of range
    if (isValid(src.first, src.second) == 0)
    {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (isValid(dest.first, dest.second) == 0)
    {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if (isUnBlocked(grid, src.first, src.second) == 0 || isUnBlocked(grid, dest.first, dest.second) == 0)
    {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest) == 1)
    {
        printf("We are already at the destination\n");
        return;
    }

    // Create a closed list and initialise it to 0 which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array

    memset(closedList, 0, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    // of that cell

    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = 2147483647;
            cellDetails[i][j].g = 2147483647;
            cellDetails[i][j].h = 2147483647;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    /*
     Create an open list having information as-
     <f, <i, j>>
     where f = g + h,
     and i, j are the row and column index of that cell
     Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     This open list is implemented as a set of pair.*/

    initializeSet(&openList);

    // Put the starting cell on the open list and set its
    // 'f' as 0
    Pair pair1 = {i, j};
    pPair pPair1 = {0.0, pair1};
    addToSet(&openList, pPair1);

    // We set this boolean value as 0 as initially
    // the destination is not reached.

    while (!isSetEmpty(&openList))
    {
        pPair p = Begin(&openList);

        // Remove this vertex from the open list
        removeFromSet(&openList, Begin(&openList));

        // Add this vertex to the closed list
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = 1;

        /*
         Generating all the 8 successor of this cell

             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E

         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/

        //----------- 1st Successor (North) ------------
        process_successor(i - 1, j, dest, src, grid, 0, 1);
        process_successor(i + 1, j, dest, src, grid, 0, 2);
        process_successor(i, j + 1, dest, src, grid, 0, 3);
        process_successor(i, j - 1, dest, src, grid, 0, 4);
        process_successor(i - 1, j + 1, dest, src, grid, 1, 5);
        process_successor(i - 1, j - 1, dest, src, grid, 1, 6);
        process_successor(i + 1, j + 1, dest, src, grid, 1, 7);
        process_successor(i + 1, j - 1, dest, src, grid, 1, 8);

        // When the destination cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destination cell. This may happen when the
        // there is no way to destination cell (due to
        // blockages)
    }
    if (foundDest == 0)
        printf("Failed to find the Destination Cell\n");
}
