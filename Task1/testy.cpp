#include <gtest/gtest.h>

#include <vector>

#include "src/Application.h"
#include "src/SearchBar.h"

// APPLICATION TESTS

class ApplicationTest : public ::testing::Test {
   protected:
    Application apk;

    explicit ApplicationTest(const std::string& initialValue = "") : apk(initialValue) {}

    void SetUp() override {
        apk.processCommand("add: Kiedy jest nowy rok w Chinach?");
        apk.processCommand("add: Kiedy jest nowy rok w Tajlandii?");
    }
};

TEST_F(ApplicationTest, FindsMatchingAsksByCommand) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    apk.processCommand("ask: Kiedy jest nowy rok");

    std::cout.rdbuf(oldCout);

    ASSERT_EQ(buffer.str(),
              "result: Kiedy jest nowy rok w Chinach?\n"
              "result: Kiedy jest nowy rok w Tajlandii?\n");
}

// SEARCH BAR TESTS

class SearchBarTest : public ::testing::Test {
   protected:
    SearchBar searchBar;

    explicit SearchBarTest(const std::string& initialValue = "") : searchBar(initialValue) {}

    void SetUp() override {
        searchBar.add("Kiedy jest nowy rok w Chinach?");
        searchBar.add("Kiedy jest nowy rok w Tajlandii?");
    }
};

TEST_F(SearchBarTest, FindsMatchingAsks) {
    auto result = searchBar.ask("Kiedy jest nowy rok");
    std::vector<std::string> resultVector(result.begin(), result.end());
    std::vector<std::string> goalVector(
        std::vector<std::string>{"Kiedy jest nowy rok w Chinach?", "Kiedy jest nowy rok w Tajlandii?"});

    ASSERT_EQ(resultVector, goalVector);
}

TEST_F(SearchBarTest, ReturnsEmptyWhenNoMatchFound) {
    auto result = searchBar.ask("Ile ma lat");
    std::vector<std::string> resultVector(result.begin(), result.end());
    std::vector<std::string> goalVector(std::vector<std::string>{});

    ASSERT_EQ(resultVector, goalVector);
}

TEST(ApplicationEmptyTest, ReturnsEmptyWhenNoAsksAdded) {
    SearchBar emptySearchBar("");
    auto result = emptySearchBar.ask("Ile ma lat");
    std::vector<std::string> resultVector(result.begin(), result.end());
    std::vector<std::string> goalVector(std::vector<std::string>{});

    ASSERT_EQ(resultVector, goalVector);
}
