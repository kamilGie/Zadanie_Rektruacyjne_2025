#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

class Application {
public:
  explicit Application(std::filesystem::path file = "date.txt");

  std::vector<std::string> ask(const std::string_view &question) const;
  void add(std::string_view entry);

  const std::filesystem::path &getFile() const;
  const std::vector<std::string> &getAsks() const;

private:
  std::filesystem::path file;
  std::vector<std::string> asks;
};
