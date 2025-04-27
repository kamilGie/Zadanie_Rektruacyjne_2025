#include "src/Templates.hpp"
#include "src/Types.h"
#include <cassert>

int main() {

  intType (*f)(intType, intType);
  intType x{7};

  auto result1 = calculate(3, x, f);
  auto result2 = f(f(x, x), x);
  assert(result1.value == result2.value);
}
