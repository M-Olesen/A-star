#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#define ROW 9
#define COL 10

void input(int grid[][COL]) {
    FILE *in_file = fopen("Minefield_input.txt", "r");

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

void output(int grid[][COL], struct Stack Path){
    FILE *out_file = fopen("Minefield_output.txt", "a");
    fprintf(out_file,"\nThe Path is: ");
    while (isEmpty(&Path) != 1)
    {
        Pair p = peek(&Path);
        pop(&Path);
        grid[p.first][p.second] += 1;
        fprintf(out_file,"-> (%d,%d) ", p.first, p.second);
    }
    fprintf(out_file,"\n");

    for (int i = 0; i < ROW; i++)
    {
        for (int l = 0; l < COL; l++)
        {
            fprintf(out_file, "%d ", grid[i][l]);
        }
        fprintf(out_file, "\n");
    }
}

void clear_output_file(){
    FILE *out_file = fopen("Minefield_output.txt", "w");
    fprintf(out_file, "");
}