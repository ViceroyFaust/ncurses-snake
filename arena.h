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

    // Returns a copy of the snake
    Snake getSnake();

    // Returns a copy of the apple
    Apple getApple();

    // Should be run only once to initialize the random number generator
    void seedRNG();

    // Generates a random location for the apple
    void generateApple();

    // Moves snake forward
    void moveSnake();

    // Grows the snake
    void growSnake();

    // Set the snake's move direction
    void setSnakeDirection(Direction direction);

    // Checks whether the snake is colliding with a wall
    bool snakeWallCollision();

    // Checks whether the snake is colliding with itself
    bool snakeSelfCollision();

    // Checks whether the snake is colliding with the apple
    bool snakeAppleCollision();

    // Runs one turn of the game. Returns true if nothing happened; False if the snake died
    bool nextTurn();
};

#endif
