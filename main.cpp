#include <iostream>
#include <string.h>
#include <ncurses.h>

void cursesInit() {
    initscr();
    raw(); // no line buffering
    keypad(stdscr, true); //enable keypad and special keys
    noecho(); // Don't print input
    curs_set(0);
}

void clean() {
    noraw(); //Disable raw for reasons
    endwin();
}

void displayMenu() {
    int row, col;
    getmaxyx(stdscr, row, col);
    char welcome[] = "Welcome to C++ Snake!";
    char prsAnyKey[] = "Press any key to start";
    char signature[] = "Created by Danylo Rybchynskyi, 2021";
    mvprintw(row/2, (col-strlen(welcome))/2, "%s", welcome);
    mvprintw(row/2-1, (col-strlen(prsAnyKey))/2, "%s", prsAnyKey);
    mvprintw(row-1, 0, "%s", signature);
    getch();
    clear();
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
    getch();
}

int main()
{
    cursesInit();
    displayMenu();
    drawBox(32, 32);
    clean();
}
