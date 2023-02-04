#include "terminal.h"
#include <iostream>
#include <vector>
#include <string>

bool isPositiveNumber(const std::string& str) {
    for (char c : str) {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    // Copy all of the arguments into a vector of strings
    std::vector<std::string> arguments(argv, argv + argc);
    if (argc > 1) {
        std::string argument = arguments[1];
        if (argument == "-h" || argument == "--help") {
            std::cout << "=== Snake Game Help ===\n"
                << "Run the executable with no parameters for standard game\n"
                << "--size [width] [height]: run the game with custom arena size\n"
                << "-h or --help: print this help screen\n";
            return 0;
        }
        if (argument == "--size") {
            if (argc != 4 ||
                    (!isPositiveNumber(arguments[2]) || !isPositiveNumber(arguments[3]))) {
                std::cout << "Error: Improper --size arguments!\n";
                return -1;
            }
            Terminal term = Terminal(std::stoi(arguments[2]), std::stoi(arguments[3]));
            term.startGame();
            return 0;
        }
        std::cout << "Error: Improper arguments!\n";
        return -1;
    }

    Terminal term = Terminal(16, 16);
    term.startGame();
    return 0;
}
