#include <gtest/gtest.h>

#include "src/Templates.hpp"
#include "src/Types.h"

TEST(ApplicationEmptyTest, ReturnsEmptyWhenNoAsksAdded) {
    intType (*f)(intType, intType) = intType::f;
    intType x{7};
    auto result1 = calculate(3, x, f);
    auto result2 = f(f(x, x), x);
    ASSERT_EQ(result2.value, result1.value);
}
