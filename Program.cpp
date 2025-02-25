#include <iostream>
#include <ncurses.h>

#include "Block.h"

//Prototypes
void GenerateMap();
void PrintMap();
void DeleteMap();
void SetupColors();
#include <cstdlib>
#include <unistd.h>

//Constants
#define ROWS 21
#define COLUMNS 80
#define randomTickSpeed 300 //Minecrafts tick speed is 3

//Global
Block* map[ROWS][COLUMNS];

int main() {
    srand(time(0));

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

    //Set up loop
    bool running = true;
    char command;
    bool waitingForInput = false;
    
    while (running) {
        if (!waitingForInput) {
            //Minecraft chooses 3 random blocks (randomTickSpeed) in the chunk and ticks them. 
            //A tick happens every .05 seconds. 
            for (int i = 0; i < randomTickSpeed; i++) {
                Block* randomBlock = map[rand() % ROWS][rand() % COLUMNS];
                randomBlock->Tick(map);
            }

            PrintMap();
            refresh();
            //.05 seconds
            usleep(50000);
        }

        //Player commands
        timeout(0);
        command = getch();
        
        if (command != ERR) {
            // Place Grass Block
            if (command == 'G') {
                waitingForInput = true;
                char input[100];

                int x, y;
                //Must turn blocking off in order to type the string
                timeout(-1);
                getstr(input);
                timeout(0); 
                sscanf(input, "%d %d", &x, &y);

                if (x > -1 && y > -1) {  
                    refresh();
                    //Check out of bounds
                    if (x >= 0 && x < ROWS && y >= 0 && y < COLUMNS) {
                        delete map[x][y];
                        map[x][y] = new Grass(x, y);
                        mvprintw(ROWS + 4, 0, "Placed Grass at %d %d", x, y);
                    }
                }
                waitingForInput = false;
            }
            // Place Mycelium Block
            if (command == 'M') {
                waitingForInput = true;
                char input[100];

                int x, y;
                //Must turn blocking off in order to type the string
                timeout(-1);
                getstr(input);
                timeout(0); 
                sscanf(input, "%d %d", &x, &y);

                if (x > -1 && y > -1) {  
                    refresh();
                    //Check out of bounds
                    if (x >= 0 && x < ROWS && y >= 0 && y < COLUMNS) {
                        delete map[x][y];
                        map[x][y] = new Mycelium(x, y);
                        mvprintw(ROWS + 4, 0, "Placed Mycelium at %d %d", x, y);
                    }
                }
                waitingForInput = false;
            }
            //Quit
            else if (command == 'Q') {
                running = false;
            }
        }
    }

    endwin();
    DeleteMap();
    return 0;
}

void GenerateMap() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            map[i][j] = new Dirt(i, j);
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