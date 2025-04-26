#include "src/Application.h"
#include <iostream>

int main() {
  Application application;

  std::string line;

  while (true) {
    std::cout << "> ";
    std::getline(std::cin, line);
    if (line.empty())
      break;
    application.processCommand(line);
  }
}
