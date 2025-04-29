#include <gtest/gtest.h>

#include <random>

#include "src/Templates.hpp"
#include "src/Types.hpp"

TEST(IntTypeTest, ZeroAdd) {
    intType (*f)(const intType &, const intType &) = intType::Add;
    intType x{0};
    auto result1 = calculate(3, x, f);
    auto result2 = f(f(x, x), x);
    ASSERT_EQ(result1.value, result2.value);
}

TEST(IntTypeTest, RandomAddWithRandomN) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> value_dist(1, 100000);
    std::uniform_int_distribution<int> n_dist(1, 10000);

    auto f = intType::Add;

    for (int i = 0; i < 100; ++i) {
        int random_value = value_dist(rng);
        int random_n = n_dist(rng);

        intType x{random_value};

        auto result1 = calculate(random_n, x, f);

        intType manual = x;
        for (int j = 1; j < random_n; ++j) {
            manual = f(manual, x);
        }

        ASSERT_EQ(result1.value, manual.value) << "Failed at random_value=" << random_value << ", n=" << random_n;
    }
}

TEST(StringTypeTest, EmptyAdd) {
    stringType (*f)(const stringType &, const stringType &) = stringType::Add;
    stringType x{""};
    auto result1 = calculate(3, x, f);
    auto result2 = f(f(x, x), x);
    ASSERT_EQ(result1.value, result2.value);
}

TEST(StringTypeTest, RandomAddWithRandomN) {
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> n_dist(1, 1000);
    std::uniform_int_distribution<int> length_dist(1, 100);
    std::uniform_int_distribution<std::size_t> dist(0, charset.size() - 1);

    auto f = stringType::Add;

    for (int i = 0; i < 100; ++i) {
        int random_n = n_dist(rng);
        int random_length = length_dist(rng);

        std::string random_value;
        random_value.reserve(random_length);

        for (std::size_t i = 0; i < random_length; ++i) {
            random_value += charset[dist(rng)];
        }

        stringType x{random_value};

        auto result1 = calculate(random_n, x, f);

        stringType manual = x;
        for (int j = 1; j < random_n; ++j) {
            manual = f(manual, x);
        }

        ASSERT_EQ(result1.value, manual.value) << "Failed at random_string=" << random_value << ", n=" << random_n;
    }
}
