#include "src/Application.h"
#include <iostream>

void processCommand(const std::string &line, Application &app) {
  if (line.starts_with("add: ")) {
    app.add(line.substr(5));
  } else if (line.starts_with("ask: ")) {
    for (const auto &res : app.ask(line.substr(5))) {
      std::cout << "result: " << res << std::endl;
    }
  } else {
    std::cout << "Nieznana komenda. Dostępne komendy:\n";
    std::cout << "  add: <tekst> - dodaje wpis\n";
    std::cout << "  ask: <pytanie> - zadaje pytanie\n";
    std::cout << "  (pusta linia) - zakończenie programu\n";
  }
}

int main() {
  Application SearchBar;

  std::string line;

  while (true) {
    std::cout << "> ";
    std::getline(std::cin, line);
    if (line.empty())
      break;
    processCommand(line, SearchBar);
  }
}
