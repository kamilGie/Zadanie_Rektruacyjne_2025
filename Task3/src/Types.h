#pragma once

struct intType {
  int value;
  static intType identity() { return intType{0}; }
  static intType f(intType n, intType mt);
};
