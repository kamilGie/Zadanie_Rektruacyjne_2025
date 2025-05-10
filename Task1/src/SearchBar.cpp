#include "./SearchBar.h"

#include <boost/algorithm/string.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/locale.hpp>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

SearchBar::~SearchBar() { saveQueriesToFile(); }

SearchBar::SearchBar(std::filesystem::path filePath) : dataFile(std::move(filePath)) {
    if (dataFile.empty()) return;

    if (std::ifstream inputFile{dataFile}; inputFile.is_open()) [[likely]] {
        for (std::string line; std::getline(inputFile, line);) {
            addQuery(line);
        }
    } else [[unlikely]] {
        std::ofstream newFile{dataFile};
        if (!newFile) {
            std::cerr << std::format("Cannot create file: {}\n", dataFile.string());
            return;
        }
    }
}

void SearchBar::saveQueriesToFile() {
    if (dataFile.empty()) return;

    // Create a temporary file to prevent data loss in case of a failure during save
    const auto tempFile = std::filesystem::temp_directory_path() / (dataFile.filename().string() + ".tmp");
    std::ofstream tmpOutput(tempFile);
    if (tmpOutput.is_open()) {
        for (const auto &query : search("")) {
            tmpOutput << query << "\n";
        }
    } else {
        std::cerr << "Cannot open temporary file " << tempFile << " for writing!\n";
        return;
    }

    // Replace the original file with the new temporary file
    std::error_code ec;
    std::filesystem::rename(tempFile, dataFile, ec);
    if (!ec) {
        std::cout << "Queries saved as: " << dataFile << std::endl;
    } else {
        std::cerr << "Error while renaming file: " << ec.message() << std::endl;
    }
}

std::string SearchBar::normalizeString(std::string_view text) {
    if (text.empty()) return {};

    std::string result(text);

    static boost::locale::generator generator;
    static std::locale polishLocale = generator("pl_PL.UTF-8");
    result = boost::locale::to_lower(result, polishLocale);
    boost::algorithm::trim(result);

    // Remove redundant spaces
    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, result, boost::is_any_of(" "), boost::token_compress_on);
    result = boost::algorithm::join(tokens, " ");

    return result;
}

void SearchBar::collectWords(trieNode *node, std::string currentPrefix, std::vector<std::string> &result) {
    if (node->isEnd) {
        result.emplace_back(currentPrefix);
    }
    for (auto &[key, child] : node->children) {
        collectWords(&child, currentPrefix + key, result);
    }
}

std::vector<std::string> SearchBar::search(std::string_view inputQuery) {
    std::string normalizedQuery = normalizeString(inputQuery);
    trieNode *current = &queriesRoot;
    for (char c : normalizedQuery) {
        if (!current->children.count(c)) {
            return {};
        }
        current = &current->children[c];
    };
    std::vector<std::string> res;
    collectWords(current, normalizedQuery, res);
    return res;
};

void SearchBar::addQuery(std::string newQuery) {
    newQuery = normalizeString(newQuery);
    trieNode *current = &queriesRoot;
    for (char c : newQuery) {
        if (!current->children.count(c)) {
            current->children[c] = trieNode();
        }
        current = &current->children[c];
    }
    current->isEnd = true;
}

const std::filesystem::path &SearchBar::getFilePath() const { return dataFile; }
const trieNode &SearchBar::getQueriesRoot() const { return queriesRoot; }
