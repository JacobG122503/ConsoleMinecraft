#include <ncurses.h>
#include "Block.h"
#include <cstdlib>

Grass::Grass(int x, int y) noexcept : Block(x, y) {
    icon = '#';
    color = COLOR_GREEN;
}

void Grass::Tick(Block* map[ROWS][COLUMNS]) {
    for (int attempts = 0; attempts < 10; attempts++) {
        //Generate -1 to 1 inclusive
        int newX = x + ((rand() % 3) - 1);
        int newY = y + ((rand() % 3) - 1);
    
        //Check if not out of bounds or not itself
        if (((newX >= 0 && newX < ROWS) && (newY >= 0 && newY < COLUMNS))
                    && !(newX == x && newY == y)) {
            delete map[newX][newY];
            map[newX][newY] = new Grass(newX, newY);
            break;    
        } else {
            continue;
        }
    }
}

Mycelium::Mycelium(int x, int y) noexcept : Block(x, y) {
    icon = '#';
    color = COLOR_MAGENTA;
}

void Mycelium::Tick(Block* map[ROWS][COLUMNS]) {
    for (int attempts = 0; attempts < 10; attempts++) {
        //Generate -1 to 1 inclusive
        int newX = x + ((rand() % 3) - 1);
        int newY = y + ((rand() % 3) - 1);
    
        //Check if not out of bounds or not itself
        if (((newX >= 0 && newX < ROWS) && (newY >= 0 && newY < COLUMNS))
                    && !(newX == x && newY == y)) {
            delete map[newX][newY];
            map[newX][newY] = new Mycelium(newX, newY);
            break;    
        } else {
            continue;
        }
    }
}

Dirt::Dirt(int x, int y) noexcept : Block(x, y) {
    icon = '#';
    color = COLOR_YELLOW;
}

void Dirt::Tick(Block* map[ROWS][COLUMNS]) {
    //Ticking dirt does nothing
    return;
}