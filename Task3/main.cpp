#include <concepts>
#include <iostream>

struct MyType {
  int value;
  static MyType identity() { return MyType{0}; }
};

MyType f(MyType n, MyType mt) { return MyType{mt.value + n.value}; }

template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation) {
  { operation(first, second) } -> std::convertible_to<T>;
  { T::identity() } -> std::convertible_to<T>;
};

template <class BinaryOp, class ValueType>
  requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp &f) {
  ValueType res = ValueType::identity();

  for (int i = 0; i < n; i++) {
    res = f(value, res);
  }

  return res;
}

int main() {
  MyType x{7};
  auto result1 = calculate(3, x, f);
  auto result2 = f(f(x, x), x);
  std::cout << result1.value << "  " << result2.value << std::endl;
  return 0;
}
