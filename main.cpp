#include "terminal.h"
#include <iostream>
#include <vector>
#include <string>

// Checks if a string represents a positive integer
bool isPositiveInt(const std::string& str) {
    for (char c : str) {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

void printHelp() {
    std::cout << "=== Snake Game Help ===\n"
        << "Run the executable with no parameters for standard game\n"
        << "--size [width] [height]: run the game with custom arena size\n"
        << "-h or --help: print this help screen\n";
}

int main(int argc, char* argv[]) {
    // Run the standard game loop with no custom arguments
    if (argc <= 1) {
        Terminal term = Terminal(16, 16);
        term.startGame();
        return 0;
    }

    // Copy all of the arguments into a vector of strings to make things easier
    std::vector<std::string> arguments(argv, argv + argc);
    std::string argument = arguments[1]; // The command argument is the second token

    if (argument == "-h" || argument == "--help") {
        printHelp();
        return 0;
    }

    // Run the game with custom arena size specified by the user
    // There must be 3 tokens (e.g. --size 25 50) and the last 2 tokens must be positive integers
    if (argument == "--size" && argc == 4 && isPositiveInt(arguments[2]) && isPositiveInt(arguments[3])) {
        Terminal term = Terminal(std::stoi(arguments[2]), std::stoi(arguments[3]));
        term.startGame();
        return 0;
    }

    // All user input was incorrect - print error!
    std::cout << "Error: Improper arguments!\n";
    return -1;

}
