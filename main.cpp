#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <string.h>
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
    echo();
    delwin(arena);
    endwin();
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
    char welcome[] = "Welcome to C++ Snake!";
    char prsAnyKey[] = "Press any key to start / esc to exit";
    char signature[] = "Created by Danylo Rybchynskyi, 2021";
    mvprintw(row/2, (col-strlen(welcome))/2, "%s", welcome);
    mvprintw(row/2+1, (col-strlen(prsAnyKey))/2, "%s", prsAnyKey);
    mvprintw(row-1, 0, "%s", signature);
    getch(); // Any key to continue. Player can press esc when game starts
    clear();
}

void displayEnd(int score) {
    int row, col;
    getmaxyx(stdscr, row, col);
    char theEnd[] = "Game over!";
    char scoreReport[] = "Your final score was: ";
    mvprintw(row/2, (col-strlen(theEnd))/2, "%s", theEnd);
    mvprintw(row/2+1, (col-strlen(scoreReport))/2, "%s%d", scoreReport, score);
    getch(); // Any key to eixt
    clear();
}

Apple makeApple(Snake& snake) {
    Point coord;
    bool done;
    do {
        done = true;
        coord = Point(rand()%16, rand()%16); // Coordinates are 0-15
        for(auto &part : snake.getBody()) {
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

void drawApple(WINDOW* win, Apple& apple) {
    mvwaddch(win, apple.getCoord().y, apple.getCoord().x * 2, '0'); // Multiplied by 2 due width > height
}

void snakeDraw(WINDOW* win, Snake& snake) {
    for (BodyPart part : snake.getBody()) {
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
        drawScore(snake.getBody().size()-1);
        drawApple(arena, apple);
        snakeDraw(arena, snake);
        wrefresh(arena);
        usleep(80000);
        input = getch();
        switch (input) {
            case 259: // Up
                snake.setDirection(d_up);
                break;
            case 258: // Down
                snake.setDirection(d_down);
                break;
            case 260: // Left
                snake.setDirection(d_left);
                break;
            case 261: // Right
                snake.setDirection(d_right);
                break;
            case 27:
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
    nodelay(stdscr, false); // disable timeout for end screen
}



int main() {
    Snake snake = Snake(d_down, Point(0, 0));
    Apple apple = Apple(Point(7, 7));

    cursesInit();
    displayMenu();
    startGame(snake, apple);
    displayEnd(snake.getBody().size()-1);
    clean();
}
