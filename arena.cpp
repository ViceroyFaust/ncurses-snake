#include "arena.h"
#include "structures.h"
#include <stdlib.h>

Arena::Arena(int width, int height) : m_width(width), m_height(height), m_snake(d_right, Point{1, height / 2}) {}

// Generates a random location for the apple
bool Arena::generateApple() {
    Point newAppleCoordinate;
    bool done;
    do {
        done = true;
        newAppleCoordinate = Point{rand() % width, rand() % height}; // Coordinates are 0 to width or height
        for (int i = 0; i < snake.size(); i++) {
            BodyPart part = snake.partAt(i);
            if ((part.coord.x == newAppleCoordinate.x) && (part.coord.y == newAppleCoordinte.y)) {
                done = false;
                break; // Break out of the for loop, as to not waste time
            }
        }

    } while (!done);

    m_apple(coord);
}

// Moves snake forward
void Arena::moveSnake() {
    m_snake.move();
}

// Grows the snake
void Arena::growSnake() {
    m_snake.grow();
}

// Checks whether the snake is colliding with a wall
bool Arena::snakeWallCollision() {
    Point headCoord = m_snake.partAt(0).coord;
    return (headCoord.x < 0 || headCoord.x > width - 1 || headCoord.y < 0 || headCoord.y > height - 1);
}

// Checks whether the snake is colliding with itself
bool Arena::snakeSelfCollision() {
    Point headCoord = m_snake.partAt(0).coord;
    // Start at 1, skipping the snake's head
    for(int i = 1; i < m_body.size(); ++i) {
        Point coord = m_snake.partAt(i).coord;
        if ((coord.x == headCoord.x) && (coord.y == headCoord.y)) {
            return true;
        }
    }
    return false;
}

// Checks whether the snake is colliding with the apple
bool Arena::snakeAppleCollision() {
    Point headCoord = m_snake.partAt(0).coord;
    Point appleCoord = m_apple.getCoord();
    return (headCoord.x == appleCoord.x) && (headCoord.y == appleCoord.y);
}

