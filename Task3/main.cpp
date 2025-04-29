#include <format>
#include <iostream>

#include "src/Templates.hpp"
#include "src/Types.hpp"

int main() {
    auto f = stringType::Add;
    stringType x{"Hello World "};

    stringType result1 = calculate(3, x, f);
    stringType result2 = f(f(x, x), x);

    std::cout << std::format("result 1: {}\nresult 2: {}\n", result1.value, result2.value);
}
