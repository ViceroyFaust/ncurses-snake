#include "apple.h"

Apple::Apple(int startx, int starty)
    : m_coord{startx, starty}
{
    // Everything is initialised
}

Point Apple::getCoord() {
    return m_coord;
}
