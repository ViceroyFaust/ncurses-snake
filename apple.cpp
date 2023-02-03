#include "apple.h"

Apple::Apple(Point coord)
    : m_coord{coord}
{
    // Everything is initialised
}

const Point& Apple::getCoord() const {
    return m_coord;
}
