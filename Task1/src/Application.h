#pragma once

#include "SearchBar.h"

class Application {
   public:
    // Constructor: creates a SearchBar instance
    // Pass an empty string ("") to create an empty database without a file
    explicit Application(std::filesystem::path file = "date.txt") : searchBar(std::move(file)) {}

    // Processes a single user command `line`
    void processCommand(const std::string &line);

    const SearchBar &getSearchBar() const;
    bool setSearchBar(const SearchBar &newSearchBar);

   private:
    SearchBar searchBar;
};
