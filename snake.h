#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include <vector>
#include "structures.h"
#include "apple.h"

class Snake {
private:
    std::vector<BodyPart> m_body;

public:
    Snake(Direction startDir, Point coord);

    void grow();
    void move();
    void setDirection(Direction direction);

    bool eatApple(Apple apple);
    bool checkCollision();

    int getSize();
    std::vector<BodyPart>& getBody();

};

#endif // SNAKE_H_INCLUDED
