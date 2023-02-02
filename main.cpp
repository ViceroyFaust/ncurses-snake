#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "structures.h"
#include "snake.h"
#include "apple.h"

WINDOW* arena;

void cursesInit() {
    initscr();
    cbreak(); // no line buffering
    keypad(stdscr, true); //enable keypad and special keys
    noecho(); // Don't print input
    arena = newwin(16, 32, 1, 1);
    curs_set(0);
}

void clean() {
    nocbreak(); // enable line buffering
    echo(); // enable output for terminal
    delwin(arena); // clean arena's memory
    endwin(); // clean remaining window memory
}

void drawBox(int x, int y) {
    addch(ACS_ULCORNER);
    for (int i = 0; i < x-2; i++) {
        addch(ACS_HLINE);
    }
    addch(ACS_URCORNER);

    for(int i = 0; i < y-2; i++) {
        mvaddch(getcury(stdscr)+1, 0, ACS_VLINE);
        mvaddch(getcury(stdscr), x-1, ACS_VLINE);
    }
    move (getcury(stdscr)+1, 0);
    addch(ACS_LLCORNER);
    for (int i = 0; i < x-2; i++) {
        addch(ACS_HLINE);
    }
    addch(ACS_LRCORNER);
}

void displayMenu() {
    int row, col;
    getmaxyx(stdscr, row, col);
    std::string welcome = "Welcome to C++ Snake!";
    std::string prsAnyKey = "Press any key to start / q to exit";
    std::string signature = "Created by Danylo Rybchynskyi, 2021";
    mvprintw(row/2, (col - welcome.length())/2, "%s", welcome.c_str());
    mvprintw(row/2+1, (col - prsAnyKey.length())/2, "%s", prsAnyKey.c_str());
    mvprintw(row-1, 0, "%s", signature.c_str());
    getch(); // Any key to continue. Player can press esc when game starts
    clear();
}

void displayEnd(int score) {
    int row, col;
    getmaxyx(stdscr, row, col);
    std::string theEnd = "Game over!";
    std::string scoreReport = "Your final score was: ";
    scoreReport += std::to_string(score);
    std::string pressQ = "Press Q to exit";
    mvprintw(row/2 - 1, (col - theEnd.length())/2, "%s", theEnd.c_str());
    mvprintw(row/2, (col - scoreReport.length())/2, "%s", scoreReport.c_str());
    mvprintw(row/2 + 1, (col - pressQ.length())/2, "%s", pressQ.c_str());
    refresh();
    while (getch() != 'q') {}
    clear();
}

Apple makeApple(const Snake& snake) {
    Point coord;
    bool done;
    do {
        done = true;
        coord = Point{rand()%16, rand()%16}; // Coordinates are 0-15
        for (int i = 0; i < snake.size(); i++) {
            const BodyPart& part = snake.partAt(i);
            if ((part.coord.x == coord.x) && (part.coord.y == coord.y)) {
                done = false;
                break;
            }
        }

    } while (!done);
    return Apple(coord);
}

void drawScore(int score) {
    // Display score a few lines below the box
    mvprintw(18, 0, "Score: %d", score);
}

void drawApple(WINDOW* win, const Apple& apple) {
    mvwaddch(win, apple.getCoord().y, apple.getCoord().x * 2, '0'); // Multiplied by 2 due width > height
}

void snakeDraw(WINDOW* win, const Snake& snake) {
    for (int i = 0; i < snake.size(); i++) {
        const BodyPart& part = snake.partAt(i);
        mvwaddch(win, part.coord.y, part.coord.x * 2, 'X'); // Multiplied by 2 due width > height
    }
}

void startGame(Snake& snake, Apple& apple) {
    int input{};
    drawBox(34, 18); // Draw the border. box and border methods don't work
    nodelay(stdscr, true); // to enable timeout
    wrefresh(arena); // to show window
    bool run = true;
    while (run) {
        wclear(arena);
        drawScore(snake.size()-1);
        drawApple(arena, apple);
        snakeDraw(arena, snake);
        wrefresh(arena);
        usleep(80000);
        input = getch();
        switch (input) {
            case KEY_UP: // Up
                snake.setDirection(d_up);
                break;
            case KEY_DOWN: // Down
                snake.setDirection(d_down);
                break;
            case KEY_LEFT: // Left
                snake.setDirection(d_left);
                break;
            case KEY_RIGHT: // Right
                snake.setDirection(d_right);
                break;
            case 'q':
                run = false;
        }
        snake.move();
        if (snake.eatApple(apple)) {
            apple = makeApple(snake);
        }
        if (snake.checkCollision()) {
            run = false;
        }
    }
    clear();
}



int main() {
    Snake snake = Snake(d_down, Point{0, 0});
    Apple apple = Apple(Point{7, 7});

    cursesInit();
    displayMenu();
    startGame(snake, apple);
    displayEnd(snake.size()-1);
    clean();
}
