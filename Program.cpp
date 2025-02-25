#include <iostream>
#include <ncurses.h>

#include "Block.h"

//Prototypes
void GenerateMap();
void PrintMap();
void DeleteMap();
void SetupColors();

//Constants
#define ROWS 21
#define COLUMNS 80

//Global
Block* map[ROWS][COLUMNS];

int main() {
    //Start ncurses
    initscr();
    raw(); 
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    SetupColors();
    
    GenerateMap();
    PrintMap();
    refresh();

    char command = 'c';
    command = getch();

    endwin();
    DeleteMap();
    return 0;
}

void GenerateMap() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            map[i][j] = new Dirt();
        }
    }
}

void PrintMap() {
    for (int i = 0; i < ROWS; i++) {
        //Print row numbers
        if (i < 10) {
            mvprintw(i, 2, "%d", i);
        } else {
            mvprintw(i, 1, "%d", i);
        }
        for (int j = 0; j < COLUMNS; j++) {
            //Print column numbers
            std::string colStr = std::to_string(j);
            if (j < 10) {
                mvprintw(ROWS, j + 4, " ");
                mvprintw(ROWS + 1, j + 4, "%c", colStr[0]);
            } else {
                mvprintw(ROWS, j + 4, "%c", colStr[0]);
                mvprintw(ROWS + 1, j + 4, "%c", colStr[1]);
            }
            attron(COLOR_PAIR(map[i][j]->color));
            mvprintw(i, j + 4, "%c", map[i][j]->icon);
            attroff(COLOR_PAIR(map[i][j]->color));         
        }
    }
}

void DeleteMap() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            delete map[i][j]; 
        }
    }    
}

void SetupColors() {
    start_color();
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
}