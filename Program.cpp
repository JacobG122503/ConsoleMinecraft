#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

#include "Block.h"
#include "Logger.h"

//Prototypes
void UpdateTime(int );
void GenerateMap();
void PrintMap();
void PrintCommands();
void ClearStatusLine();
void DeleteMap();
void SetupColors();

//Constants
#define ROW_OFFSET 6
#define COLUMN_OFFSET 35

//Game settings
int rows = 0;
int columns = 0;
int randomTickSpeed = 3; 

//Global
Block*** map;

int main() {
    int seed = time(0);
    srand(seed);

    //Start ncurses
    initscr();
    raw(); 
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    MEVENT event;
    SetupColors();

    //Clear log file
    std::ofstream file("logs.txt", std::ios::trunc);

    //Get terminal size and set r and c respectively
    //Also make room for other text
    getmaxyx(stdscr, rows, columns); 
    if (rows < 21 || columns < 80) {
        endwin();
        std::cout << "\033[2J\033[H";
        std::cout << "Please set your terminal size to be bigger than 21x80." << std::endl;
        return 0;
    }
    rows -= ROW_OFFSET;
    columns -= COLUMN_OFFSET;

    //Allocate the new map size
    map = new Block**[rows];
    for (int i = 0; i < rows; i++) {
        map[i] = new Block*[columns];
    }
    
    GenerateMap();
    PrintMap();
    PrintCommands();
    refresh();

    //Set up loop
    bool running = true;
    int command;
    bool waitingForInput = false;
    
    Log("Program started with seed: %d", seed);

    int ticks = 0;

    while (running) {
        if (!waitingForInput) {
            //Minecraft chooses 3 random blocks (randomTickSpeed) in the chunk and ticks them. 
            //A tick happens every .05 seconds. 
            for (int i = 0; i < randomTickSpeed; i++) {
                Block* randomBlock = map[rand() % rows][rand() % columns];
                randomBlock->Tick(map, rows, columns);
                UpdateTime(++ticks/3);
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
            ClearStatusLine();
            // Place Grass Block
            if (command == 'G') {
                waitingForInput = true;

                int x, y;
                //Must turn blocking off in order to read the click area
                timeout(-1);
                command = getch();
                if (command == KEY_MOUSE && getmouse(&event) == OK) {
                    x = event.y;
                    y = event.x - 4;
                }
                timeout(0); 

                if (x > -1 && y > -1) {  
                    refresh();
                    //Check out of bounds
                    if (x >= 0 && x < rows && y >= 0 && y < columns) {
                        delete map[x][y];
                        map[x][y] = new Grass(x, y);
                        ClearStatusLine();
                        mvprintw(rows + 4, 0, "Placed Grass at %d, %d", x, y);
                        Log("Placed Grass at %d, %d", x, y);
                    }
                }
                waitingForInput = false;
            }
            // Place Mycelium Block
            else if (command == 'M') {
                waitingForInput = true;

                int x, y;
                //Must turn blocking off
                timeout(-1);
                command = getch();
                if (command == KEY_MOUSE && getmouse(&event) == OK) {
                    x = event.y;
                    y = event.x - 4;
                }
                timeout(0); 

                if (x > -1 && y > -1) {  
                    refresh();
                    //Check out of bounds
                    if (x >= 0 && x < rows && y >= 0 && y < columns) {
                        delete map[x][y];
                        map[x][y] = new Mycelium(x, y);
                        ClearStatusLine();
                        mvprintw(rows + 4, 0, "Placed Mycelium at %d, %d", x, y);
                        Log("Placed Mycelium at %d, %d", x, y);
                    }
                }
                waitingForInput = false;
            }
            // Place Wheat Field
            else if (command == 'W') {
                waitingForInput = true;

                int x1, y1;
                int x2, y2;

                timeout(-1);
                //Get both corners
                command = getch();
                if (command == KEY_MOUSE && getmouse(&event) == OK) {
                    x1 = event.y;
                    y1 = event.x - 4;
                }
                command = getch();
                if (command == KEY_MOUSE && getmouse(&event) == OK) {
                    x2 = event.y;
                    y2 = event.x - 4;
                }
                timeout(0); 

                if ((x1 > -1 && y1 > -1) && (x2 > -1 && y2 > -1)) {  
                    refresh();
                    //Check out of bounds
                    if ((x1 >= 0 && x1 < rows && y1 >= 0 && y1 < columns) && (x2 >= 0 && x2 < rows && y2 >= 0 && y2 < columns)) {

                        for (int i = x1; i < x2; i++) {
                            for (int j = y1; j < y2; j++) {
                                delete map[i][j];
                                map[i][j] = new Wheat(i, j);
                            }
                        }
                    }
                }
                waitingForInput = false;
            }
            else if (command == KEY_UP) {
                randomTickSpeed *= 10;
                Log("Speed increased to %d", randomTickSpeed);
            }
            else if (command == KEY_DOWN) {
                if (randomTickSpeed != 3) randomTickSpeed /= 10;
                Log("Speed decreased to %d", randomTickSpeed);
            }
            //Quit
            else if (command == 'Q') {
                running = false;
                Log("Quitting...");
            }
        }
    }

    endwin();
    DeleteMap();
    return 0;
}

void UpdateTime(int ticks) {
    int totalMinutes = ticks / 1200; 
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;

    mvprintw(15, columns + 7, "Time Elapsed: %02dh %02dm", hours, minutes);
}



void GenerateMap() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            map[i][j] = new Dirt(i, j);
        }
    }
}

void PrintMap() {
    for (int i = 0; i < rows; i++) {
        //Print row numbers
        if (i < 10) {
            mvprintw(i, 2, "%d", i);
        } else {
            mvprintw(i, 1, "%d", i);
        }
        for (int j = 0; j < columns; j++) {
            //Print column numbers
            std::string colStr = std::to_string(j);
            if (j < 10) {
                mvprintw(rows, j + 4, " ");
                mvprintw(rows + 1, j + 4, "%c", colStr[0]);
            } else {
                mvprintw(rows, j + 4, "%c", colStr[0]);
                mvprintw(rows + 1, j + 4, "%c", colStr[1]);
            }
            attron(COLOR_PAIR(map[i][j]->color));
            mvprintw(i, j + 4, "%c", map[i][j]->icon);
            attroff(COLOR_PAIR(map[i][j]->color));         
        }
    }
}

void PrintCommands() {
    //Print border
    mvaddch(2, columns + 6, ACS_ULCORNER);
    //Horizontal is 1/2 a cell so double it 
    for (int i = 1; i <= 20; i++) {
        mvaddch(2, columns + 6 + i, ACS_HLINE);
    }
    //Vertical
    for (int i = 1; i <= 10; i++) {
        mvaddch(2 + i, columns + 6, ACS_VLINE);
    }

    //Print text
    mvprintw(1, columns + 7, "COMMANDS");
    mvprintw(3, columns + 7, "G - Place Grass");
    mvprintw(4, columns + 7, "M - Place Mycelium");
    mvprintw(5, columns + 7, "W - Place Wheat");
    mvprintw(6, columns + 7, "Up and Down - Change speed");
    mvprintw(12, columns + 7, "Q - Quit");
}

void ClearStatusLine() {
    //rows + 4, 0
    for (int i = 0; i < columns + COLUMN_OFFSET; i++) {
        mvprintw(rows + 4, i, " "); 
    }
}

void DeleteMap() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            delete map[i][j]; 
        }
    }    
}

//Actual minecraft colors
enum CustomColors {
    COLOR_DIRT = 100, 
    COLOR_GRASS,
    COLOR_MYCELIUM,
    COLOR_GREEN_WHEAT,
    COLOR_YELLOW_WHEAT,
    COLOR_SOIL,
};

//RGB * 1000 / 255
void SetupColors() {
    start_color();
    init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
    //Custom Colors
    init_color(COLOR_DIRT, 573, 424, 302); 
    init_pair(COLOR_DIRT, COLOR_DIRT, COLOR_DIRT); 
    init_color(COLOR_GRASS, 388, 498, 251); 
    init_pair(COLOR_GRASS, COLOR_GRASS, COLOR_GRASS); 
    init_color(COLOR_MYCELIUM, 412, 380, 439);
    init_pair(COLOR_MYCELIUM, COLOR_MYCELIUM, COLOR_MYCELIUM); 
    init_color(COLOR_SOIL, 329, 176, 110);
    init_pair(COLOR_GREEN_WHEAT, COLOR_GREEN, COLOR_SOIL);
    init_pair(COLOR_YELLOW_WHEAT, COLOR_YELLOW, COLOR_SOIL);
}