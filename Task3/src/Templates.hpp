#pragma once
#include <concepts>
#include <stdexcept>

template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation) {
    { operation(first, second) } -> std::convertible_to<T>;
    { T::identity() } -> std::convertible_to<T>;
};

template <class BinaryOp, class ValueType>
    requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp& f) {
    if (n <= 0) throw std::invalid_argument{"calculate: n must be non-negative"};

    ValueType result = ValueType::identity();
    ValueType acc = value;

    while (n > 0) {
        if (n & 1) result = f(result, acc);
        acc = f(acc, acc);
        n >>= 1;
    }
    return result;
}
