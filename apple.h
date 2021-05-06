#ifndef APPLE_H_INCLUDED
#define APPLE_H_INCLUDED
#include "structures.h"

class Apple {
private:
    Point m_coord;
public:
    Apple(Point coord);
    Point getCoord();
};

#endif // APPLE_H_INCLUDED
