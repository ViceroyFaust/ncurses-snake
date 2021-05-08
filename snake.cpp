#include <vector>
#include "snake.h"
#include "structures.h"

Snake::Snake(Direction startDir, Point startCoord)
    : m_body{BodyPart(startDir, startCoord)}
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
                newPart = BodyPart(oldTail.movDirection, Point(oldTail.coord.x, oldTail.coord.y+1));
                break;
            case d_down:
                newPart = BodyPart(oldTail.movDirection, Point(oldTail.coord.x, oldTail.coord.y-1));
                break;
            case d_left:
                newPart = BodyPart(oldTail.movDirection, Point(oldTail.coord.x+1, oldTail.coord.y));
                break;
            case d_right:
                newPart = BodyPart(oldTail.movDirection, Point(oldTail.coord.x-1, oldTail.coord.y));
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
                part.coord.y -= 1;
                break;
            case d_down:
                part.coord.y += 1;
                break;
            case d_left:
                part.coord.x -= 1;
                break;
            case d_right:
                part.coord.x += 1;
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

bool Snake::eatApple(Apple apple) {
    Point snakeCoord = m_body[0].coord;
    Point appleCoord = apple.getCoord();
    if ((snakeCoord.x == appleCoord.x) && (snakeCoord.y == appleCoord.y)) {
        grow();
        return true;
    }
    return false;
}

bool Snake::checkCollision() {
    Point headCoord = m_body[0].coord;
    if (headCoord.x < 0 || headCoord.x > 15 || headCoord.y < 0 || headCoord.y > 15) {
        return true;
    }
    for(int i = 1; i < m_body.size(); ++i) {
        Point coord = m_body[i].coord;
        if ((coord.x == headCoord.x) && (coord.y == headCoord.y)) {
            return true;
        }
    }
    return false;
}

int Snake::getSize() {
    return m_body.size();
}
std::vector<BodyPart>& Snake::getBody() {
    return m_body;
}

