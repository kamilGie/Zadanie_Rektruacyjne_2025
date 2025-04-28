#include "./SearchBar.h"

#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <format>
#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <vector>

SearchBar::~SearchBar() { saveQueriesToFile(); }

SearchBar::SearchBar(std::filesystem::path filePath) : dataFile(std::move(filePath)) {
    if (dataFile.empty()) return;

    if (std::ifstream inputFile{dataFile}; inputFile.is_open()) [[likely]] {
        for (std::string line; std::getline(inputFile, line);) {
            queries.push_back(std::move(line));
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
        for (const auto &query : queries) {
            tmpOutput << query << std::endl;
        }
    } else {
        std::cerr << "Cannot open temporary file " << tempFile << " for writing!" << std::endl;
        return;
    }

    // Replace the original file with the new temporary file
    try {
        std::filesystem::rename(tempFile, dataFile);
        std::cout << "Queries saved as: " << dataFile << std::endl;
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error while renaming file: " << e.what() << std::endl;
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

std::span<const std::string> SearchBar::search(std::string_view inputQuery) {
    std::string normalizedQuery = normalizeString(inputQuery);

    if (normalizedQuery.empty() || queries.empty()) return {};

    // Find the range (from the first to the last matching element) in the sorted list based on the query prefix
    auto prefixView = [&](const std::string &str) { return std::string_view(str).substr(0, normalizedQuery.size()); };
    auto [lowerBound, upperBound] = std::ranges::equal_range(queries, normalizedQuery, std::ranges::less{}, prefixView);
    return std::span{lowerBound, upperBound};
}

void SearchBar::addQuery(std::string newQuery) {
    newQuery = normalizeString(newQuery);
    auto insertPos = std::lower_bound(queries.begin(), queries.end(), newQuery);
    bool unique = insertPos == queries.end() || *insertPos != newQuery;
    if (unique) queries.insert(insertPos, std::move(newQuery));
}

const std::filesystem::path &SearchBar::getFilePath() const { return dataFile; }
const std::vector<std::string> &SearchBar::getQueries() const { return queries; }
