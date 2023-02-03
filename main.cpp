#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include "structures.h"
#include "snake.h"
#include "apple.h"
#include "arena.h"

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
    nodelay(stdscr, false); // to disable timeout
    while (getch() != 'q') {}
    clear();
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

void startGame() {
    displayMenu();

    Arena game(16, 16);
    int input{};
    drawBox(34, 18); // Draw the border. box and border methods don't work
    nodelay(stdscr, true); // to enable timeout
    wrefresh(arena); // to show window
    bool run = true;
    while (run) {
        wclear(arena);
        drawScore(game.getScore());
        drawApple(arena, game.getApple());
        snakeDraw(arena, game.getSnake());
        wrefresh(arena);
        usleep(80000);
        input = getch();
        switch (input) {
            case KEY_UP: // Up
                game.setSnakeDirection(d_up);
                break;
            case KEY_DOWN: // Down
                game.setSnakeDirection(d_down);
                break;
            case KEY_LEFT: // Left
                game.setSnakeDirection(d_left);
                break;
            case KEY_RIGHT: // Right
                game.setSnakeDirection(d_right);
                break;
            case 'q':
                run = false;
        }
        run = game.nextTurn();
    }
    clear();

    displayEnd(game.getScore());
}



int main() {
    cursesInit();
    startGame();
    clean();
}
