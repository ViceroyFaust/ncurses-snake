#include "terminal.h"
#include "structures.h"
#include <unistd.h>
#include <string>

Terminal::Terminal(int width, int height) :
        m_arenaWidth{width}, m_arenaHeight{height}, 
        m_windowWidth{width * 2 + 2}, m_windowHeight{height + 2}, 
        m_window{nullptr}, m_game{width, height} {
    init();
}

Terminal::~Terminal() {
    clean();
}

void Terminal::init() {
    initscr();
    cbreak(); // no line buffering
    keypad(stdscr, true); //enable keypad and special keys
    noecho(); // Don't print input

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    m_window = newwin(m_windowHeight, m_windowWidth, (rows - m_windowHeight) / 2 , (cols - m_windowWidth) / 2 );
    curs_set(0); // Make the cursor invisible
}

void Terminal::clean() {
    nocbreak(); // enable line buffering
    echo(); // enable output for terminal
    delwin(m_window); // clean arena's memory
    endwin(); // clean remaining window memory
}

void Terminal::displayMenu() const {
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

void Terminal::displayEnd() const {
    int row, col;
    getmaxyx(stdscr, row, col);
    std::string theEnd = "Game over!";
    std::string scoreReport = "Your final score was: ";
    scoreReport += std::to_string(m_game.getScore());
    std::string pressQ = "Press Q to exit";
    mvprintw(row/2 - 1, (col - theEnd.length())/2, "%s", theEnd.c_str());
    mvprintw(row/2, (col - scoreReport.length())/2, "%s", scoreReport.c_str());
    mvprintw(row/2 + 1, (col - pressQ.length())/2, "%s", pressQ.c_str());
    refresh();
    nodelay(stdscr, false); // to disable timeout
    while (getch() != 'q') {}
    clear();
}

void Terminal::drawScore() const {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    mvprintw((rows + m_windowHeight) / 2, (cols - m_windowWidth) / 2, "Score: %d", m_game.getScore());
}

void Terminal::drawSnake() const {
    for (int i = 0; i < m_game.getSnake().size(); i++) {
        const BodyPart& part = m_game.getSnake().partAt(i);
        // Characters are taller than they are wide, thus we multiply x by 2
        // There is padding around the window, therefore we add 1
        mvwaddch(m_window, part.coord.y + 1, (part.coord.x + 1) * 2, 'X'); 
    }
}

void Terminal::drawApple() const {
    // Characters are taller than they are wide, thus we multiply x by 2
    // There is padding around the window, therefore we add 1
    mvwaddch(m_window, m_game.getApple().getCoord().y + 1, (m_game.getApple().getCoord().x + 1) * 2, '0'); 
}

void Terminal::startGame() {
    displayMenu();

    nodelay(stdscr, true); // to enable input timeout

    int input;
    bool run = true;
    while (run) {

        wclear(m_window);
        drawScore();
        box(m_window, 0, 0);
        drawApple();
        drawSnake();
        wrefresh(m_window);
        usleep(80000);
        input = getch();

        switch (input) {
            case KEY_UP: // Up
                m_game.setSnakeDirection(d_up);
                break;
            case KEY_DOWN: // Down
                m_game.setSnakeDirection(d_down);
                break;
            case KEY_LEFT: // Left
                m_game.setSnakeDirection(d_left);
                break;
            case KEY_RIGHT: // Right
                m_game.setSnakeDirection(d_right);
                break;
            case 'q':
                run = false;
        }

        if (!m_game.nextTurn())
            run = false;
    }

    clear();
    displayEnd();
}

