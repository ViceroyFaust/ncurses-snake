#include "arena.h"
#include "structures.h"
#include <stdlib.h>
#include <time.h>

Arena::Arena(int width, int height) :
        m_width(width), m_height(height), m_snake(d_right, Point{1, height / 2}), m_apple(Point{0, 0}) {
    generateApple();
    seedRNG();
}

// Returns a copy of the snake
const Snake& Arena::getSnake() const {
    return m_snake;
}

// Returns a copy of the apple
const Apple& Arena::getApple() const {
    return m_apple;
}

// Returns the game score
int Arena::getScore() const {
    return m_snake.size() - 1;
}

// Generates a random location for the apple
void Arena::generateApple() {
    Point newAppleCoordinate;
    bool done;
    do {
        done = true;
        newAppleCoordinate = Point{rand() % m_width, rand() % m_height}; // Coordinates are 0 to width or height
        for (int i = 0; i < m_snake.size(); i++) {
            BodyPart part = m_snake.partAt(i);
            if ((part.coord.x == newAppleCoordinate.x) && (part.coord.y == newAppleCoordinate.y)) {
                done = false;
                break; // Break out of the for loop, as to not waste time
            }
        }

    } while (!done);

    m_apple = Apple(newAppleCoordinate);
}

// Should be run only once to initialize the random number generator
void Arena::seedRNG() {
    srand(time(NULL)); // Use current time as seed to make every game unique
}

// Moves snake forward
void Arena::moveSnake() {
    m_snake.move();
}

// Grows the snake
void Arena::growSnake() {
    m_snake.grow();
}

// Set the snake's move direction
void Arena::setSnakeDirection(Direction direction) {
    m_snake.setDirection(direction);
}

// Checks whether the snake is colliding with a wall
bool Arena::snakeWallCollision() const {
    Point headCoord = m_snake.partAt(0).coord;
    return (headCoord.x < 0 || headCoord.x >= m_width || headCoord.y < 0 || headCoord.y >= m_height);
}

// Checks whether the snake is colliding with itself
bool Arena::snakeSelfCollision() const {
    Point headCoord = m_snake.partAt(0).coord;
    // Start at 1, skipping the snake's head
    for(int i = 1; i < m_snake.size(); ++i) {
        Point coord = m_snake.partAt(i).coord;
        if ((coord.x == headCoord.x) && (coord.y == headCoord.y)) {
            return true;
        }
    }
    return false;
}

// Checks whether the snake is colliding with the apple
bool Arena::snakeAppleCollision() const {
    Point headCoord = m_snake.partAt(0).coord;
    Point appleCoord = m_apple.getCoord();
    return (headCoord.x == appleCoord.x) && (headCoord.y == appleCoord.y);
}

// Runs one turn of the game. Returns true if nothing happened; False if the snake died
bool Arena::nextTurn() {
    m_snake.move();
    if (snakeWallCollision() || snakeSelfCollision())
        return false;
    if (snakeAppleCollision()) {
        m_snake.grow();
        generateApple();
    }

    return true;
}

