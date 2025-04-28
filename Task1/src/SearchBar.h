#pragma once

#include <filesystem>
#include <span>
#include <string_view>
#include <vector>

// SearchBar class - handles saving and searching user queries
class SearchBar {
   public:
    // Constructor: loads existing queries from a file or creates a new one;
    // pass an empty string `""` to create an empty database without a file
    explicit SearchBar(std::filesystem::path filePath = "data.txt");

    // Destructor: automatically saves queries to the file
    ~SearchBar();

    // Searches for queries matching the given `query` prefix
    std::span<const std::string> search(std::string_view query);

    // Adds a `newQuery` to the list
    void addQuery(std::string newQuery);

    const std::filesystem::path& getFilePath() const;
    const std::vector<std::string>& getQueries() const;

   private:
    // Saves all queries to the file
    void saveQueriesToFile();

    // Normalizes the text (converts to lowercase, removes redundant spaces)
    std::string normalizeString(std::string_view text);

    std::filesystem::path dataFile;
    std::vector<std::string> queries;
};
