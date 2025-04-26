#pragma once

#include <filesystem>
#include <string>
#include <vector>

class SearchBar {
public:
  explicit SearchBar(std::filesystem::path file = "date.txt");

  std::vector<std::string> ask(const std::string &question) const;
  void add(std::string entry);

  const std::filesystem::path &getFile() const;
  const std::vector<std::string> &getAsks() const;

private:
  std::filesystem::path file;
  std::vector<std::string> asks;
};
