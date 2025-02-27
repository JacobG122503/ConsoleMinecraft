#include <iostream>
#include <ncurses.h>

#include "Block.h"

//Prototypes
void GenerateMap();
void PrintMap();
void PrintCommands();
void DeleteMap();
void SetupColors();
#include <cstdlib>
#include <unistd.h>

//Game settings
int rows = 0;
int columns = 0;
int randomTickSpeed = 3; 

//Global
Block*** map;

int main() {
    srand(time(0));

    //Start ncurses
    initscr();
    raw(); 
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    MEVENT event;
    SetupColors();

    //Get terminal size and set r and c respectively
    //Also make room for other text
    getmaxyx(stdscr, rows, columns); 
    if (rows < 21 || columns < 80) {
        endwin();
        std::cout << "\033[2J\033[H";
        std::cout << "Please set your terminal size to be bigger than 21x80." << std::endl;
        return 0;
    }
    rows -= 6;
    columns -= 35;

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
    
    while (running) {
        if (!waitingForInput) {
            //Minecraft chooses 3 random blocks (randomTickSpeed) in the chunk and ticks them. 
            //A tick happens every .05 seconds. 
            for (int i = 0; i < randomTickSpeed; i++) {
                Block* randomBlock = map[rand() % rows][rand() % columns];
                randomBlock->Tick(map, rows, columns);
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

                int x, y;
                //Must turn blocking off in order to type the string
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
                        mvprintw(rows + 4, 0, "Placed Grass at %d %d", x, y);
                    }
                }
                waitingForInput = false;
            }
            // Place Mycelium Block
            else if (command == 'M') {
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
                    if (x >= 0 && x < rows && y >= 0 && y < columns) {
                        delete map[x][y];
                        map[x][y] = new Mycelium(x, y);
                        mvprintw(rows + 4, 0, "Placed Mycelium at %d %d", x, y);
                    }
                }
                waitingForInput = false;
            }
            else if (command == KEY_UP) {
                randomTickSpeed *= 10;
            }
            else if (command == KEY_DOWN) {
                if (randomTickSpeed != 3) randomTickSpeed /= 10;
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
    mvprintw(5, columns + 7, "Up and Down - Change speed");
    mvprintw(12, columns + 7, "Q - Quit");
}

//TODO add a function that clears the status/info line

void DeleteMap() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
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