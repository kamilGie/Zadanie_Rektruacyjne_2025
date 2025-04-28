#include <gtest/gtest.h>

#include <vector>

#include "src/Application.h"
#include "src/SearchBar.h"

class ApplicationTest : public ::testing::Test {
   protected:
    Application apk;

    void SetUp() override {
        apk.processCommand("add: Kiedy jest nowy rok w Chinach?");
        apk.processCommand("add: Kiedy jest nowy rok w Tajlandii?");
    }
};

TEST_F(ApplicationTest, FindsMatchingAsksByCommand) {
    std::stringstream buffer;
    std::streambuf *oldCout = std::cout.rdbuf(buffer.rdbuf());
    apk.processCommand("ask: Kiedy jest nowy rok");

    std::cout.rdbuf(oldCout);

    ASSERT_EQ(buffer.str(),
              "result: Kiedy jest nowy rok w Chinach?\n"
              "result: Kiedy jest nowy rok w Tajlandii?\n");
}

class SearchBarTest : public ::testing::Test {
   protected:
    SearchBar searchBar;

    void SetUp() override {
        searchBar.add("Kiedy jest nowy rok w Chinach?");
        searchBar.add("Kiedy jest nowy rok w Tajlandii?");
    }
};

TEST_F(SearchBarTest, FindsMatchingAsks) {
    ASSERT_EQ(searchBar.ask("Kiedy jest nowy rok"),
              (std::vector<std::string>{"Kiedy jest nowy rok w Chinach?",
                                        "Kiedy jest nowy rok w Tajlandii?"}));
}

TEST_F(SearchBarTest, ReturnsEmptyWhenNoMatchFound) {
    ASSERT_EQ(searchBar.ask("Ile ma lat"), std::vector<std::string>{});
}

TEST(ApplicationEmptyTest, ReturnsEmptyWhenNoAsksAdded) {
    SearchBar apk;
    ASSERT_EQ(apk.ask("Kiedy jest nowy rok"), std::vector<std::string>{});
}
