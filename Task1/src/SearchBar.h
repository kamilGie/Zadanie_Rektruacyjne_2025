#pragma once

#include <filesystem>
#include <span>
#include <string>
#include <vector>

class SearchBar {
   public:
    explicit SearchBar(std::filesystem::path file = "date.txt");
    ~SearchBar();

    std::span<const std::string> ask(const std::string &ask);
    void add(std::string entry);

    const std::filesystem::path &getFile() const;
    const std::vector<std::string> &getAsks() const;

   private:
    void save_questions_to_file();
    std::string normalize_string(const std::string &str);

    std::filesystem::path dataFile;
    std::vector<std::string> asks;
};
