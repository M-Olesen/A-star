#include "stack.h"


#define ROW 9
#define COL 10

typedef struct {
    int parent_i, parent_j;
    double f, g, h;
} cell;

int isValid(int row, int col);
int isUnBlocked(int grid[][COL], int row, int col);
int isDestination(int row, int col, Pair dest);
double calculateHValue(int row, int col, Pair dest);
void tracePath(Pair dest, int grid[][COL]);
void aStarSearch(int grid[][COL], Pair src, Pair dest);
