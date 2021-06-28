#pragma once

#include <array>
#include <iostream>

namespace lagrange {

using Size = std::size_t;

template <typename T, Size n> using Arr = std::array<T, n>;

template <typename T> using InitializerList = std::initializer_list<T>;

using OStream = std::ostream;

} // namespace lagrange
