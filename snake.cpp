#include "snake.h"

Snake::Snake(Direction startDir, int startx, int starty)
    : m_head{startDir, startx, starty}, m_body{m_head}
{
    // Everything is initialised
}

void Snake::grow() {

}

void Snake::move() {
    for (BodyPart part : m_body) {
        switch(part.movDirection) {
            /* The coordinate plane starts at 0,0 in
               the upper left corner */
            case d_up:
                part.y -= 1;
                break;
            case d_down:
                part.y += 1;
                break;
            case d_left:
                part.x -= 1;
                break;
            case d_right:
                part.x += 1;
                break;
        }
    }
}

void Snake::setDirection(Direction direction) {
    m_head.movDirection = direction;
}

int Snake::getSize() {
    return m_body.size();
}
