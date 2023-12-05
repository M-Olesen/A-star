#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#define ROW 9
#define COL 10

// Function to read input from a file and populate a 2D array (grid)
void input(int grid[][COL]) {
    FILE *in_file = fopen("Minefield_input.txt", "r");

    // Check if the file exists
    if (in_file == NULL) {
        printf("Error: File doesn't exist!");
        exit(-1);
    }

    // Loop through each row in the grid (assuming there are 9 rows)
    for (int row = 0; row < 9; ++row) {
        // Temporary array to store a line of text from the file
        char temp[100];
        
        // Read a line from the file into the temporary array
        fgets(temp, 100, in_file);

        // Tokenize the line using space as a delimiter
        char *token;
        token = strtok(temp, " ");

        // Loop through each column in the grid (assuming there are 10 columns)
        for (int col = 0; col < 10; ++col) {
            // Convert the token to an integer and store it in the grid
            grid[row][col] = atoi(token);

            // Move to the next token (next integer in the line)
            token = strtok(NULL, " ");
        }
    }

    fclose(in_file);
}


// Function to write output to a file, including the path and the updated grid
void output(int grid[][COL], struct Stack Path) {
    FILE *out_file = fopen("Minefield_output.txt", "a");

    // Print a header for the path information in the file
    fprintf(out_file, "\nThe Path is: ");

    // Process each element in the stack until it's empty
    while (isEmpty(&Path) != 1) {
        Pair p = peek(&Path);
        pop(&Path);

        // Increment the corresponding value in the grid to show the path
        grid[p.first][p.second] += 1;

        // Print the coordinates of the current element in the path to the file
        fprintf(out_file, "-> (%d,%d) ", p.first, p.second);
    }

    // Print a newline to separate the path information from the grid
    fprintf(out_file, "\n");

    // Loop through each row in the grid
    for (int i = 0; i < ROW; i++) {
        // Loop through each column in the current row
        for (int l = 0; l < COL; l++) {
            // Print the value of the grid element to the file
            fprintf(out_file, "%d ", grid[i][l]);
        }
        // Print a newline to move to the next row in the grid
        fprintf(out_file, "\n");
    }

    fclose(out_file);
}


void clear_output_file(){
    FILE *out_file = fopen("Minefield_output.txt", "w");
    fprintf(out_file, "");
    fclose(out_file);
}