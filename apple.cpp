#include "apple.h"

Apple::Apple(Point coord)
    : m_coord{coord}
{
    // Everything is initialised
}

Point Apple::getCoord() {
    return m_coord;
}
