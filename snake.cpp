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
    auto prevDirection = m_body.front().movDirection;
    for(auto &part : m_body) {
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
        std::swap(part.movDirection, prevDirection);
    }
}

void Snake::setDirection(Direction direction) {
    Direction current = m_body.front().movDirection;
    // The snake changes direction only in 90 degree turns
    if (current == d_left && direction != d_right)
        m_body.front().movDirection = direction;
    else if (current == d_right && direction != d_left)
        m_body.front().movDirection = direction;
    else if (current == d_up && direction != d_down)
        m_body.front().movDirection = direction;
    else if (current == d_down && direction != d_up)
        m_body.front().movDirection = direction;

}

int Snake::getSize() {
    return m_body.size();
}
std::vector<BodyPart> Snake::getBody() {
    return m_body;
}

