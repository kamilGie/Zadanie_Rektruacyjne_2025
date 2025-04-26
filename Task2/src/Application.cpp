#include "./Application.h"
#include <vector>

Application::Application(std::filesystem::path file) : file(std::move(file)) {}

std::vector<std::string>
Application::ask(const std::string_view &question) const {
  std::vector<std::string> res;
  for (const std::string &ask : asks) {
    if (ask.find(question) != std::string::npos) {
      res.emplace_back(ask);
    }
  }
  return res;
}

void Application::add(std::string_view question) {
  asks.emplace_back(question);
}

const std::filesystem::path &Application::getFile() const { return file; }
const std::vector<std::string> &Application::getAsks() const { return asks; }
