//
// Created by kaspe on 11/12/2023.
//
#include "DroneSimulation.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "windows.h"
void set_text_colorr(int color) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

#define BLUE 0x1
#define GREEN 0x2
#define AQUA 0x3
#define RED 0x4
#define PURPLE 0x5
#define YELLOW 0x6
#define DEFAULT 0x7
#define GRAY 0x8
#define LIGHT_BLUE 0x9
#define LIGHT_GREEN 0xA
#define LIGHT_AQUA 0xB
#define LIGHT_RED 0xC
#define LIGHT_PURPLE 0xD
#define LIGHT_YELLOW 0xE
void drone_simulation(int grid[ROW][COL]){


    int fog_of_war[ROW][COL];
    memset(fog_of_war, -1, sizeof(fog_of_war));

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            set_text_colorr(LIGHT_PURPLE);
            if(j != COL -1){
                printf("# ");
            }
            else{
                printf("#\n");
            }
        }
    }
    // We start in positive direction
    int positive = 1;
    for (int i = ROW-1; i >= 0; --i) {
        if(positive == 1){
            for (int j = 0; j < COL; ++j) {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                fog_of_war[i][j] = grid[i][j];

                for (int k = 0; k < ROW; ++k) {
                    for (int l = 0; l < COL; ++l) {
                        switch(fog_of_war[k][l]){
                            case -1:
                                set_text_colorr(LIGHT_PURPLE);

                                if(l != COL -1){
                                    printf("# ");
                                }
                                else{
                                    printf("#\n");
                                }
                                break;
                            case 0:
                                set_text_colorr(RED);

                                if(l != COL -1){
                                    printf("0 ");
                                }
                                else{
                                    printf("0\n");
                                }
                                break;
                            case 1:
                                set_text_colorr(GREEN);

                                if(l != COL -1){
                                    printf("1 ");
                                }
                                else{
                                    printf("1\n");
                                }
                                break;
                        }

                    }
                }

                Sleep(100);
            }
            positive = 0;
        }
        else{
            for (int j = COL; j >= 0; --j) {
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                fog_of_war[i][j] = grid[i][j];
                for (int k = 0; k < ROW; ++k) {
                    for (int l = 0; l < COL; ++l) {
                        switch(fog_of_war[k][l]){
                            case -1:
                                set_text_colorr(LIGHT_PURPLE);

                                if(l != COL -1){
                                    printf("# ");
                                }
                                else{
                                    printf("#\n");
                                }
                                break;
                            case 0:
                                set_text_colorr(RED);

                                if(l != COL -1){
                                    printf("0 ");
                                }
                                else{
                                    printf("0\n");
                                }
                                break;
                            case 1:
                                set_text_colorr(GREEN);

                                if(l != COL -1){
                                    printf("1 ");
                                }
                                else{
                                    printf("1\n");
                                }
                                break;
                        }
                    }
                }
                Sleep(100);
            }
            positive = 1;
        }



    }

    set_text_colorr(DEFAULT);

}