#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 9
#define COL 10

void input(int grid[][COL]) {
    FILE *in_file = fopen("Minefield_input.txt", "r");
    FILE *out_file = fopen("Minefield_output.txt", "w");

    if (in_file == NULL) {
        printf("Error file doesn't exsist!");
        exit(-1);
    }

    for (int row = 0; row < 9; ++row) {
       char temp[100];
        fgets(temp, 100, in_file);
        char *token;
        token = strtok(temp, " ");
        for (int col = 0; col < 10; ++col) {

            grid[row][col] = atoi(token);
            token = strtok(NULL, " ");
        }
    }
};

