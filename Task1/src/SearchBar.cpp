#include "./SearchBar.h"
#include <vector>

SearchBar::SearchBar(std::filesystem::path file) : file(std::move(file)) {}

std::vector<std::string> SearchBar::ask(const std::string &question) const {
  std::vector<std::string> res;
  for (const std::string &ask : asks) {
    if (ask.find(question) != std::string::npos) {
      res.emplace_back(ask);
    }
  }
  return res;
}

void SearchBar::add(std::string question) { asks.emplace_back(question); }

const std::filesystem::path &SearchBar::getFile() const { return file; }
const std::vector<std::string> &SearchBar::getAsks() const { return asks; }
