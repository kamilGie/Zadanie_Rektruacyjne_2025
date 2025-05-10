#include <gmock/gmock.h>

#include <vector>

#include "src/Application.h"
#include "src/SearchBar.h"

// APPLICATION TESTS

class ApplicationEdgeCaseTest : public ::testing::Test {
   protected:
    Application app{""};

    void SetUp() override {
        app.processCommand("add: Kiedy jest nowy rok w Chinach?");
        app.processCommand("add: Kiedy jest nowy rok w Tajlandii?");
    }
};

TEST_F(ApplicationEdgeCaseTest, FindsMatchingAsksByCommand) {
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    app.processCommand("ask: Kiedy jest nowy rok");

    std::cout.rdbuf(oldCout);

    ASSERT_EQ(buffer.str(),
              "result: kiedy jest nowy rok w tajlandii?\n"
              "result: kiedy jest nowy rok w chinach?\n");
}

TEST_F(ApplicationEdgeCaseTest, SearchWithoutAdds) {
    std::stringstream out;
    auto oldCout = std::cout.rdbuf(out.rdbuf());
    app.processCommand("ask: xyz");
    std::cout.rdbuf(oldCout);

    ASSERT_TRUE(out.str().empty());
}

TEST_F(ApplicationEdgeCaseTest, MixedCaseAndSpacesNormalization) {
    app.processCommand("add:   HeLLo   WoRLd  ");
    std::stringstream out;
    auto oldCout = std::cout.rdbuf(out.rdbuf());
    app.processCommand("ask: hello");
    std::cout.rdbuf(oldCout);

    ASSERT_EQ(out.str(), "result: hello world\n");
}

TEST_F(ApplicationEdgeCaseTest, PolishLetters) {
    app.processCommand("add: ŻĄĘŁĘŃĆ");
    std::stringstream out;
    auto oldCout = std::cout.rdbuf(out.rdbuf());
    app.processCommand("ask: Ż");
    std::cout.rdbuf(oldCout);

    ASSERT_EQ(out.str(), "result: żąęłęńć\n");
}

// SEARCH BAR TESTS

class SearchBarTest : public ::testing::Test {
   protected:
    SearchBar searchBar{""};

    void SetUp() override {
        searchBar.addQuery("Kiedy jest nowy rok w Chinach?");
        searchBar.addQuery("Kiedy jest nowy rok w Tajlandii?");
    }
};

TEST_F(SearchBarTest, FindsMatchingAsksTwo) {
    auto result = searchBar.search("Kiedy jest nowy rok");
    std::vector<std::string> resultVector(result.begin(), result.end());
    std::vector<std::string> goalVector(std::vector<std::string>{
        "kiedy jest nowy rok w tajlandii?",
        "kiedy jest nowy rok w chinach?",
    });

    ASSERT_EQ(resultVector, goalVector);
}

TEST_F(SearchBarTest, FindsMatchingAsksOne) {
    auto result = searchBar.search("Kiedy jest nowy rok w t");
    std::vector<std::string> resultVector(result.begin(), result.end());
    std::vector<std::string> goalVector(std::vector<std::string>{"kiedy jest nowy rok w tajlandii?"});

    ASSERT_EQ(resultVector, goalVector);
}

TEST_F(SearchBarTest, FindsMatchingAsksZero) {
    auto result = searchBar.search("Kiedy jest nowy rok w tajlandiii");
    std::vector<std::string> resultVector(result.begin(), result.end());
    std::vector<std::string> goalVector(std::vector<std::string>{});

    ASSERT_EQ(resultVector, goalVector);
}

class SearchBarNormalizationTest : public ::testing::Test {
   protected:
    SearchBar sb{""};
};

TEST_F(SearchBarNormalizationTest, TrimsAndLowercases) {
    sb.addQuery("   TeST   CaSe  ");
    auto res = sb.search("test");
    std::vector<std::string> vec(res.begin(), res.end());
    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "test case");
}

TEST_F(SearchBarNormalizationTest, InsertsInOrder) {
    sb.addQuery("banana");
    sb.addQuery("apple");
    sb.addQuery("cherry");

    auto all = sb.search("");
    EXPECT_THAT(all, ::testing::UnorderedElementsAre("banana", "apple", "cherry"));
}

TEST_F(SearchBarNormalizationTest, DuplicateEntriesKept) {
    sb.addQuery("pow");
    sb.addQuery("pow");
    sb.addQuery("pow");

    auto res = sb.search("p");
    std::vector<std::string> vec(res.begin(), res.end());

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "pow");
}

TEST_F(SearchBarNormalizationTest, PartialPrefixSearch) {
    sb.addQuery("prefixTest");
    sb.addQuery("prelude");
    sb.addQuery("other");
    auto res = sb.search("pre");
    std::vector<std::string> vec(res.begin(), res.end());
    ASSERT_EQ(vec.size(), 2);
    EXPECT_THAT(res, ::testing::UnorderedElementsAre("prelude", "prefixtest"));
}

TEST_F(SearchBarNormalizationTest, NoMatchReturnsEmpty) {
    sb.addQuery("one");
    sb.addQuery("two");
    auto res = sb.search("three");
    ASSERT_TRUE(res.empty());
}
