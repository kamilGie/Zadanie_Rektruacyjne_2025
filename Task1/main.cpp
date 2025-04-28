#include <iostream>

#include "src/Application.h"

int main() {
    Application application;

    std::string line;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty()) break;
        application.processCommand(line);
    }
}
