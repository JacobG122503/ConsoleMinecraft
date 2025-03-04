#include <ncurses.h>
#include <cstdlib>

#include "Block.h"
#include "Logger.h"


Grass::Grass(int x, int y) noexcept : Block(x, y) {
    icon = '#';
    color = COLOR_GREEN;
}

void Grass::Tick(Block*** map, int rows, int columns) {
    for (int attempts = 0; attempts < 10; attempts++) {
        //Generate -1 to 1 inclusive
        int newX = x + ((rand() % 3) - 1);
        int newY = y + ((rand() % 3) - 1);
    
        //Check if not out of bounds or not itself or not grass already.
        if (((newX >= 0 && newX < rows) && (newY >= 0 && newY < columns))
                    && !(newX == x && newY == y) && dynamic_cast<Grass*>(map[newX][newY]) == nullptr) {
            delete map[newX][newY];
            map[newX][newY] = new Grass(newX, newY);
            Log("Grass (%d, %d) spread to %d, %d", x, y, newX, newY);
            break;    
        } else {
            continue;
        }
    }
}
/*
To check if it is grass
if (dynamic_cast<Grass*>(map[x][y]) != nullptr) {
    // The block at (x, y) is a Grass block
}
*/

Mycelium::Mycelium(int x, int y) noexcept : Block(x, y) {
    icon = '#';
    color = COLOR_MAGENTA;
}

void Mycelium::Tick(Block*** map, int rows, int columns) {
    for (int attempts = 0; attempts < 10; attempts++) {
        //Generate -1 to 1 inclusive
        int newX = x + ((rand() % 3) - 1);
        int newY = y + ((rand() % 3) - 1);
    
        //Check if not out of bounds or not itself also not already Mycelium
        if (((newX >= 0 && newX < rows) && (newY >= 0 && newY < columns))
                    && !(newX == x && newY == y) && dynamic_cast<Mycelium*>(map[newX][newY]) == nullptr) {
            delete map[newX][newY];
            map[newX][newY] = new Mycelium(newX, newY);
            Log("Mycelium (%d, %d) spread to %d, %d", x, y, newX, newY);
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

void Dirt::Tick(Block*** map, int rows, int columns) {
    //Ticking dirt does nothing
    return;
}