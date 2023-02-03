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
    const Snake& getSnake() const;

    // Returns a copy of the apple
    const Apple& getApple() const;

    // Returns the game score
    int getScore() const;

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
    bool snakeWallCollision() const;

    // Checks whether the snake is colliding with itself
    bool snakeSelfCollision() const;

    // Checks whether the snake is colliding with the apple
    bool snakeAppleCollision() const;

    // Runs one turn of the game. Returns true if nothing happened; False if the snake died
    bool nextTurn();
};

#endif
