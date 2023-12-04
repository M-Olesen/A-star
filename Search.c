#include <math.h>
#include <string.h>
#include "search.h"

#define ROW 9
#define COL 10
cell cellDetails[ROW][COL];
int foundDest = 0;
Set openList;
int closedList[ROW][COL];

void process_successor(int i, int j, Pair dest, Pair src, int grid[][COL], int diagonel){
if (foundDest== 0){


    // Only process this cell if this is a valid one
    if (isValid(i, j) == 1) {
        // If the destination cell is the same as the
        // current successor
        if (isDestination(i, j, dest) == 1) {
            // Set the Parent of the destination cell
            cellDetails[i][j].parent_i = i;
            cellDetails[i][j].parent_j = j;
            printf("The destination cell is found\n");
            tracePath(dest, src, grid);
            foundDest = 1;
            return;
        }
            // If the successor is already on the closed
            // list or if it is blocked, then ignore it.
            // Else do the following
        else if (closedList[i][j] == 0
                 && isUnBlocked(grid, i, j)
                    == 1) {
            double gNew;
            if (diagonel == 0){
                gNew = cellDetails[i][j].g + 1.0;
            } else {
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
            if (cellDetails[i][j].f == 2147483647
                || cellDetails[i][j].f > fNew) {
                Pair pair1 = {i, j};
                pPair pPair1 = {fNew, pair1};
                addToSet(&openList, pPair1);

                // Update the details of this cell
                cellDetails[i][j].f = fNew;
                cellDetails[i][j].g = gNew;
                cellDetails[i][j].h = hNew;
                cellDetails[i][j].parent_i = i;
                cellDetails[i][j].parent_j = j;
            }
        }
    }
}
}

int isValid(int row, int col) {
    // Returns 1 if row number and column number
    // is in range
    return (row >= 0) && (row < ROW) && (col >= 0)
           && (col < COL);
}

int isUnBlocked(int grid[][COL], int row, int col) {
    // Returns 1 if the cell is not blocked else 0
    if (grid[row][col] == 1)
        return (1);
    else
        return (0);
}

int isDestination(int row, int col, Pair dest) {
    if (row == dest.first && col == dest.second)
        return (1);
    else
        return (0);
}

double calculateHValue(int row, int col, Pair dest)
{
    // Return using the distance formula
    return ((double)sqrt(
            (row - dest.first) * (row - dest.first)
            + (col - dest.second) * (col - dest.second)));
}


void tracePath(Pair dest, Pair src, int grid[][COL])
{
    printf("\nThe Path is: ");
    int row = dest.first;
    int col = dest.second;

    struct Stack* Path = createStack(100);

    while (!(cellDetails[row][col].parent_i == src.first
             && cellDetails[row][col].parent_j == src.second)) {
        Pair item = {row, col};
        push(Path, item);
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Pair item = {row, col};
    push(Path, item);

    printf("%d", isEmpty(Path));
    while (isEmpty(Path) != 1) {
        Pair p = peek(Path);
        pop(Path);
        grid[p.first][p.second] += 1;
        printf("-> (%d,%d) ", p.first, p.second);
    }
    printf("\n");

    for (int i = 0; i < ROW; i++) {
        for (int l = 0; l < COL; l++) {
            printf("%d ", grid[i][l]);
        }
        printf("\n");
    }
}

void aStarSearch(int grid[][COL], Pair src, Pair dest) {
    // If the source is out of range
    if (isValid(src.first, src.second) == 0) {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (isValid(dest.first, dest.second) == 0) {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if (isUnBlocked(grid, src.first, src.second) == 0
        || isUnBlocked(grid, dest.first, dest.second)
           == 0) {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest)
        == 1) {
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

    for (i = 0; i < ROW; i++) {
        for (j = 0; j < COL; j++) {
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


    while (!isSetEmpty(&openList)) {
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

        // To store the 'g', 'h' and 'f' of the 8 successors

        //----------- 1st Successor (North) ------------
        process_successor(i - 1, j, dest, src, grid, 0);
        process_successor(i + 1, j, dest, src, grid, 0);
        process_successor(i, j + 1, dest, src, grid, 0);
        process_successor(i, j - 1, dest, src, grid, 0);
        process_successor(i - 1, j + 1, dest, src, grid, 1);
        process_successor(i - 1, j - 1, dest, src, grid, 1);
        process_successor(i + 1, j + 1, dest, src, grid, 1);
        process_successor(i + 1, j - 1, dest, src, grid, 1);
        // Only process this cell if this is a valid one

        // When the destination cell is not found and the open
        // list is empty, then we conclude that we failed to
        // reach the destination cell. This may happen when the
        // there is no way to destination cell (due to
        // blockages)
    }
        if (foundDest == 0)
            printf("Failed to find the Destination Cell\n");

    }
