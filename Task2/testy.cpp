#include "src/Application.h"
#include <gtest/gtest.h>
#include <vector>

class ApplicationTest : public ::testing::Test {
protected:
  Application apk;

  void SetUp() override {
    apk.add("Kiedy jest nowy rok w Chinach?");
    apk.add("Kiedy jest nowy rok w Tajlandii?");
  }
};

TEST_F(ApplicationTest, FindsMatchingAsks) {
  ASSERT_EQ(apk.ask("Kiedy jest nowy rok"),
            (std::vector<std::string>{"Kiedy jest nowy rok w Chinach?",
                                      "Kiedy jest nowy rok w Tajlandii?"}));
}

TEST_F(ApplicationTest, ReturnsEmptyWhenNoMatchFound) {
  ASSERT_EQ(apk.ask("Ile ma lat"), std::vector<std::string>{});
}

TEST(ApplicationEmptyTest, ReturnsEmptyWhenNoAsksAdded) {
  Application apk;
  ASSERT_EQ(apk.ask("Kiedy jest nowy rok"), std::vector<std::string>{});
}
