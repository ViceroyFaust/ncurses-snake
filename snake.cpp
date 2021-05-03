#include "snake.h"

Snake::Snake(Direction startDir, int startx, int starty)
    : m_body{BodyPart(startDir, startx, starty)}
{
    // Everything is initialised
}

void Snake::grow() {
    BodyPart& oldTail = m_body.at(m_body.size()-1);
    BodyPart newPart;
    switch(oldTail.movDirection) {
            /* The coordinate plane starts at 0,0 in
               the upper left corner */
            case d_up:
                newPart = BodyPart(oldTail.movDirection, oldTail.x, oldTail.y+1);
                break;
            case d_down:
                newPart = BodyPart(oldTail.movDirection, oldTail.x, oldTail.y-1);
                break;
            case d_left:
                newPart = BodyPart(oldTail.movDirection, oldTail.x+1, oldTail.y);
                break;
            case d_right:
                newPart = BodyPart(oldTail.movDirection, oldTail.x-1, oldTail.y);
                break;
    }
    m_body.push_back(newPart);
}

void Snake::move() {
    for (int i = 0; i < m_body.size(); i++) {
        BodyPart& part = m_body.at(i);
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
    m_body.front().movDirection = direction;
}

int Snake::getSize() {
    return m_body.size();
}
std::vector<BodyPart> Snake::getBody() {
    return m_body;
}

