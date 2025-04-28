#include "./Application.h"

#include <format>
#include <iostream>

void Application::processCommand(const std::string &line) {
    if (line.starts_with("add: ")) {
        searchBar.addQuery(line.substr(5));
    } else if (line.starts_with("ask: ")) {
        for (const auto &res : searchBar.search(line.substr(5))) {
            std::cout << std::format("result: {}", res) << std::endl;
        }
    } else {
        std::cout << "Nieznana komenda. Dostępne komendy:\n";
        std::cout << "  add: <tekst> - dodaje wpis\n";
        std::cout << "  ask: <pytanie> - zadaje pytanie\n";
        std::cout << "  (pusta linia) - zakończenie programu\n";
    }
}

const SearchBar &Application::getSearchBar() const { return searchBar; }

bool Application::setSearchBar(const SearchBar &newSearchBar) {
    searchBar = newSearchBar;
    return true;
}
