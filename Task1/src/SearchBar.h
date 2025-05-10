#pragma once

#include <filesystem>
#include <string_view>
#include <vector>

#include "Components/trieNode.h"

// SearchBar class - handles saving and searching user queries
class SearchBar {
   public:
    // Constructor: loads existing queries from a file or creates a new one;
    // pass an empty string `""` to create an empty database without a file
    explicit SearchBar(std::filesystem::path filePath = "data.txt");

    // Destructor: automatically saves queries to the file
    ~SearchBar();

    // Searches for queries matching the given `query` prefix
    std::vector<std::string> search(std::string_view query);

    // Adds a `newQuery` to the trie
    void addQuery(std::string newQuery);

    const std::filesystem::path& getFilePath() const;
    const trieNode& getQueriesRoot() const;

   private:
    // Saves all queries to the file
    void saveQueriesToFile();

    // Normalizes the text (converts to lowercase, removes redundant spaces)
    std::string normalizeString(std::string_view text);

    // Collect all words that follow the given prefix from this node
    void collectWords(trieNode* node, std::string currentPrefix, std::vector<std::string>& result);

    std::filesystem::path dataFile;
    trieNode queriesRoot;
};
