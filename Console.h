//
// Created by kaspe on 11/12/2023.
//

#ifndef ASTAR_CONSOLE_H
#define ASTAR_CONSOLE_H

#endif //ASTAR_CONSOLE_H
#include "windows.h"
void set_text_color(int color) {

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