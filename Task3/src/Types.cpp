#include "Types.h"

intType intType::f(intType n, intType mt) {
    return intType{mt.value + n.value};
}
