#ifndef TERMINAL_H
#define TERMINAL_H

#include "arena.h"
#include <curses.h>

class Terminal {
private:
    int m_arenaWidth;
    int m_arenaHeight;

    int m_windowWidth;
    int m_windowHeight;

    WINDOW* m_window;
    Arena m_game;

public:
    Terminal(int width, int height);
    ~Terminal();

    void init();
    void clean();

    void displayMenu() const;
    void displayEnd() const;

    void drawScore() const;
    void drawSnake() const;
    void drawApple() const;

    void startGame();

};

#endif

