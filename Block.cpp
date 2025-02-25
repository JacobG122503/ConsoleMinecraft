#include <ncurses.h>
#include "Block.h"


Grass::Grass() noexcept {
    icon = '#';
    color = COLOR_GREEN;
}

Dirt::Dirt() noexcept {
    icon = '#';
    color = COLOR_YELLOW;
}