#include <ncurses.h>
#include <cstdlib>

#include "Block.h"
#include "Logger.h"

enum CustomColors {
    COLOR_DIRT = 100, 
    COLOR_GRASS,
    COLOR_MYCELIUM,
    COLOR_GREEN_WHEAT,
    COLOR_YELLOW_WHEAT,
};


Grass::Grass(int x, int y) noexcept : Block(x, y) {
    icon = ' ';
    color = COLOR_GRASS;
}

void Grass::Tick(Block*** map, int rows, int columns) {
    for (int attempts = 0; attempts < 10; attempts++) {
        //Generate -1 to 1 inclusive
        int newX = x + ((rand() % 3) - 1);
        int newY = y + ((rand() % 3) - 1);
    
        //Check if not out of bounds or not itself or not grass already.
        //And is dirt (Can only spread to dirt)
        if (((newX >= 0 && newX < rows) && (newY >= 0 && newY < columns))
                    && !(newX == x && newY == y) && dynamic_cast<Grass*>(map[newX][newY]) == nullptr
                    && dynamic_cast<Dirt*>(map[newX][newY]) != nullptr) {
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
    icon = ' ';
    color = COLOR_MYCELIUM;
}

void Mycelium::Tick(Block*** map, int rows, int columns) {
    for (int attempts = 0; attempts < 10; attempts++) {
        //Generate -1 to 1 inclusive
        int newX = x + ((rand() % 3) - 1);
        int newY = y + ((rand() % 3) - 1);
    
        //Check if not out of bounds or not itself also not already Mycelium
        //And is dirt (Can only spread to dirt)
        if (((newX >= 0 && newX < rows) && (newY >= 0 && newY < columns))
                    && !(newX == x && newY == y) && dynamic_cast<Mycelium*>(map[newX][newY]) == nullptr
                    && dynamic_cast<Dirt*>(map[newX][newY]) != nullptr) {
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
    icon = ' ';
    color = COLOR_DIRT;
}

void Dirt::Tick(Block*** map, int rows, int columns) {
    //Ticking dirt does nothing
    return;
}

Wheat::Wheat(int x, int y) noexcept : Block(x, y) {
    color = COLOR_GREEN_WHEAT;
    stage = 0;
    icon = '.';
}

//All wheat logic is assuming dry farmland.
void Wheat::Tick(Block*** map, int rows, int columns) {
    //Already full grown. Skip
    if (stage == 7) return;

    float points = 2.0f;
    bool halfProb = false;
    bool halfPoints = false;

    bool north = false, south = false, east = false, west = false;

    //Wheat logic is super odd. There are two factors.
    //Add .25 points for each wheat in surrounding area
    //If there is a diagonal wheat, half the probability at the end
    //If not in rows, half the points
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newX = x + i;
            int newY = y + j;

            //If itself, continue or if out of bounds. 
            if (newX == 0 && newY == 0 || newX < 0 || newX >= rows || newY < 0 || newY >= columns) continue;

            //If it is wheat, if not continue
            if (dynamic_cast<Wheat*>(map[newX][newY]) != nullptr) {
                points += .25f;
            } else {
                continue;
            }

            //If has diagonal
            if (i + j == 0 || abs(i + j) == 2) {
                halfProb = true;
                halfPoints = true;
            }

            //If has block going North, etc.
            if (i == 0 && j == 1) north = true;
            if (i == 0 && j == -1) south = true;
            if (i == 1 && j == 0) east = true;
            if (i == -1 && j == 0) west = true;

            //Now check if in rows or not.
            if (north && east) halfPoints = true;
            if (north && west) halfPoints = true;
            if (south && east) halfPoints = true;
            if (south && west) halfPoints = true;
        }
    }
    
    if (halfPoints) points /= 2.0f;
    Log("Wheat %d, %d has points:  %f", x, y, points);
    //This probability is taken from Minecraft logic
    float probability = 1.0f / (floor(25.0f / points) + 1);
    if (halfProb) probability /= 2;
    Log("Wheat %d, %d has probability to grow of %f", x, y, probability);

    if ((rand() % 100) < (probability * 100)) {
        //Grow to next stage
        if (stage < 7) {
            stage++;

            switch (stage) {
                case 0:
                    icon = '.';
                    break;
                case 1:
                    icon = ',';
                    break;
                case 2:
                    icon = '_';
                    break;
                case 3:
                    icon = '=';
                    break;
                case 4:
                    icon = 'u';
                    break;
                case 5:
                    icon = 'w';
                    break;
                case 6:
                    icon = 'W';
                    break;
                case 7:
                    icon = 'W';
                    color = COLOR_YELLOW_WHEAT;
                    break;
                default:
                    icon = 'e';
                    break;
            }
        }
    }

    return;
}