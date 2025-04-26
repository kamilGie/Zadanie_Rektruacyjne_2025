#include "./Application.h"
#include <iostream>

Application::Application(std::filesystem::path file) {
  searchBar = SearchBar(file);
}

void Application::processCommand(const std::string &line) {
  if (line.starts_with("add: ")) {
    searchBar.add(line.substr(5));
  } else if (line.starts_with("ask: ")) {
    for (const auto &res : searchBar.ask(line.substr(5))) {
      std::cout << "result: " << res << std::endl;
    }
  } else {
    std::cout << "Nieznana komenda. Dostępne komendy:\n";
    std::cout << "  add: <tekst> - dodaje wpis\n";
    std::cout << "  ask: <pytanie> - zadaje pytanie\n";
    std::cout << "  (pusta linia) - zakończenie programu\n";
  }
}

const SearchBar &Application::getSearchBar() const { return searchBar; }

void Application::setSearchBar(const SearchBar &newSearchBar) {
  searchBar = newSearchBar;
}
