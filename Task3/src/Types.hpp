#pragma once
#include <string>

struct intType {
    int value{0};
    constexpr static intType identity() noexcept { return {0}; }

    constexpr intType operator+(const intType& m) const noexcept { return {value + m.value}; }
    static intType Add(const intType& n, const intType& m) noexcept { return n + m; }
};

struct stringType {
    std::string value;
    static stringType identity() noexcept { return {""}; }

    stringType operator+(const stringType& other) const { return {value + other.value}; }
    static stringType Add(const stringType& n, const stringType& m) noexcept { return n + m; }
};
