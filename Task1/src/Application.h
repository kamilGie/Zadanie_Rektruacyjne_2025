#pragma once
#include "SearchBar.h"

class Application {
   public:
    explicit Application(std::filesystem::path file = "date.txt") : searchBar(file) {}
    void processCommand(const std::string &line);

    const SearchBar &getSearchBar() const;
    void setSearchBar(const SearchBar &newSearchBar);

   private:
    SearchBar searchBar;
};
