#include <iostream>
#include <string.h>
#include <ncurses.h>

using namespace std;

void cursesInit() {
    initscr();
    raw(); // no line buffering
    keypad(stdscr, true); //enable keypad and special keys
    noecho(); // Don't print input
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
}

int main()
{
    cursesInit();
    displayMenu();
    clean();
}
