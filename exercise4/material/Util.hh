#pragma once

#include <initializer_list>
#include <iostream>
#include <vector>

namespace scprog {
  // The data type of the matrix/vector entries
  using Value = double;

  // The data type of the size and indices
  using Size = std::size_t;

  using OStream = std::ostream;

  template <typename T>
  using InitializerList = std::initializer_list<T>;
}
