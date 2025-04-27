#pragma once
#include <concepts>

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
