#include "./SearchBar.h"

#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include <vector>

SearchBar::~SearchBar() { save_questions_to_file(); }

SearchBar::SearchBar(std::filesystem::path f) : dataFile(std::move(f)) {
    if (dataFile == "") {
        return;
    }

    std::ifstream data(dataFile);

    if (data.is_open()) {
        std::string line;
        while (std::getline(data, line)) {
            asks.push_back(line);
        }
    } else {
        std::cerr << "Nie można otworzyć pliku: " << dataFile << std::endl;
    }
}

void SearchBar::save_questions_to_file() {
    if (dataFile == "") {
        return;
    }

    std::filesystem::path tmpFile = "tmp.txt";
    {
        std::ofstream tmp(tmpFile);
        if (tmp.is_open()) {
            for (const auto &ask : asks) {
                tmp << ask << std::endl;
            }
        } else {
            std::cerr << "Nie można otworzyć pliku " << tmpFile << " do zapisu!" << std::endl;
            return;
        }
    }

    try {
        std::filesystem::rename(tmpFile, dataFile);
        std::cout << "zapytania zapisane jako: " << dataFile << std::endl;
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Błąd przy zmianie nazwy pliku: " << e.what() << std::endl;
    }
};

std::string SearchBar::normalize_string(const std::string &str) {
    if (str.empty()) return str;

    static boost::locale::generator gen;
    static std::locale loc = gen("pl_PL.UTF-8");

    std::string s = str;

    s = boost::locale::to_lower(s, loc);
    boost::algorithm::trim(s);

    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, s, boost::is_any_of(" "), boost::token_compress_on);

    s = boost::algorithm::join(tokens, " ");
    return s;
}

std::span<const std::string> SearchBar::ask(const std::string &question) {
    std::string normalizeQuestion = normalize_string(question);

    if (normalizeQuestion.empty() || empty(asks)) return {};

    // Searching for the upper and lower bound in a sorted vector by prefix
    auto prefix_view = [&](const std::string &s) { return std::string_view(s).substr(0, normalizeQuestion.size()); };
    auto [upper, lower] = std::ranges::equal_range(asks, normalizeQuestion, std::ranges::less{}, prefix_view);
    return std::span{upper, lower};
}

void SearchBar::add(std::string question) {
    std::string normalizeQuestion = normalize_string(question);
    auto it = std::lower_bound(asks.begin(), asks.end(), normalizeQuestion);
    asks.insert(it, std::move(normalizeQuestion));
}

const std::filesystem::path &SearchBar::getFile() const { return dataFile; }
const std::vector<std::string> &SearchBar::getAsks() const { return asks; }
