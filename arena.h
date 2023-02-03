#ifndef ARENA_H
#define ARENA_H

#include "snake.h"
#include "apple.h"

class Arena {
private:
    int m_width;
    int m_height;

    Snake m_snake;
    Apple m_apple;

public:
    Arena(int width, int height);

    // Generates a random location for the apple
    bool generateApple();

    // Moves snake forward
    void moveSnake();

    // Grows the snake
    void growSnake();

    // Checks whether the snake is colliding with a wall
    bool snakeWallCollision();

    // Checks whether the snake is colliding with itself
    bool snakeSelfCollision();

    // Checks whether the snake is colliding with the apple
    bool snakeAppleCollision();
};

#endif
