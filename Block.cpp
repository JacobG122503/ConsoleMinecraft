#include <ncurses.h>
#include "Block.h"


Grass::Grass() noexcept {}

char Grass::getIcon() const {
    return '#';
}

int Grass::getColor() const {
    return COLOR_GREEN;
}

Dirt::Dirt() noexcept {}

char Dirt::getIcon() const {
    return '#';
}

int Dirt::getColor() const {
    return COLOR_YELLOW;
}