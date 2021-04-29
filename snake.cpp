#include <list>
#include "snake.h"

Snake::Snake(Direction startDir, int startx, int starty)
    : m_head{startDir, startx, starty}, m_body{m_head}
{
    // Everything is initialised
}

void Snake::grow() {

}

void Snake::move() {

}

void Snake::setDirection(Direction& direction) {
    m_head.movDirection = direction;
}

int Snake::getSize() {
    return m_body.size();
}
