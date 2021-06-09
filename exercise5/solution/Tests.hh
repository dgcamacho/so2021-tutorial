#pragma once

#include <iostream>
#include <type_traits>

// inspired by boost/core/lightweight_test.hpp - lightweight test library

// Macro tests whether an expression is true
#define SCPROG_TEST(expr) \
  ::scprog::impl::_test(expr, #expr, __FILE__, __LINE__)

// Macro tests whether an expression is equal to value
#define SCPROG_TEST_EQ(expr, value) \
  ::scprog::impl::_test_eq(expr, value, #expr, #value, __FILE__, __LINE__)

// Macro tests whether an expression is unequal to value
#define SCPROG_TEST_NE(expr, value) \
  ::scprog::impl::_test_ne(expr, value, #expr, #value, __FILE__, __LINE__)

// Macro tests whether an expression is approximately equal to value
#define SCPROG_TEST_TOL 1.e-10
#define SCPROG_TEST_APPROX(expr, value) \
  ::scprog::impl::_test_approx(expr, value, #expr, #value, __FILE__, __LINE__)

// Macro tests whether an expression throws an exception
#ifdef SCPROG_NO_THROW
  #define SCPROG_TEST_THROWS(expr)
#else
  #define SCPROG_TEST_THROWS(expr) \
    try { \
      expr; \
      ::scprog::impl::_test_throws(#expr, __FILE__, __LINE__); \
    } catch(...) {}
#endif

namespace scprog
{
  namespace impl
  {
    /// global counter for the number of detected errors
    inline int& num_errors()
    {
      static int num = 0;
      return num;
    }

  } // end namespace impl


  /// Returns 0 if no errors are detected, otherwise returns 1. Must be called at the end
  /// of main().
  inline int report_errors()
  {
    int errors = impl::num_errors();

    if (errors == 0) {
      std::cout  << "No errors detected.\n";
      return 0;
    } else {
      std::cerr << errors << " error(s) detected.\n";
      return 1;
    }
  }


  namespace impl
  {
    /// Tests whether an expression evaluates to true
    inline void _test(bool success,
                      char const* expr, char const* file, size_t line)
    {
      if (!success) {
        std::cerr << file << ":" << line
                 << "  TEST( " << expr << " ) failed\n";
        num_errors()++;
      }
    }

    /// Tests whether the value of an expression is equal to an expected value
    template <class T1, class T2>
    inline void _test_eq(T1 const& expr_value, T2 const& value,
                         char const* expr_str, char const* value_str, char const* file, size_t line)
    {
      using T = std::common_type_t<T1,T2>;
      if (T(expr_value) != T(value)) {
        std::cerr << file << ":" << line
                 << "  TEST( " << expr_str << " == " << value_str << " ) failed:  " << expr_value << " != " << value << "\n";
        num_errors()++;
      }
    }

    /// Tests whether the value of an expression is not equal to an expected value
    template <class T1, class T2>
    inline void _test_ne(T1 const& expr_value, T2 const& value,
                         char const* expr_str, char const* value_str, char const* file, size_t line)
    {
      using T = std::common_type_t<T1,T2>;
      if (T(expr_value) == T(value)) {
        std::cerr << file << ":" << line
                 << "  TEST( " << expr_str << " != " << value_str << " ) failed:  " << expr_value << " == " << value << "\n";
        num_errors()++;
      }
    }

    template <class T>
    constexpr T _abs(T const& x) { return x < T(0) ? -x : x; }

    /// Tests whether the value of an expression is approximately equal to an expected value
    // implementation for scalars
    template <class T1, class T2,
      std::enable_if_t<std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>, int>* = nullptr>
    inline void _test_approx(T1 const& expr_value, T2 const& value,
                             char const* expr_str, char const* value_str, char const* file, size_t line)
    {
      if (_abs(expr_value - value) > SCPROG_TEST_TOL) {
        std::cerr << file << ":" << line
                 << "  TEST( " << expr_str << " ~= " << value_str << " ) failed:  " << expr_value << " != " << value << "\n";
        num_errors()++;
      }
    }

    // implementation for pair
    template <class T11, class T12, class T21, class T22>
    inline void _test_approx(std::pair<T11,T12> const& expr_value, std::pair<T21,T22> const& value,
                             char const* expr_str, char const* value_str, char const* file, size_t line)
    {
      if (_abs(expr_value.first - value.first) > SCPROG_TEST_TOL ||
          _abs(expr_value.second - value.second) > SCPROG_TEST_TOL)
      {
        std::cerr << file << ":" << line
                 << "  TEST( " << expr_str << " ~= " << value_str << " ) failed:  (" << expr_value.first << "," << expr_value.second << ") != (" << value.first << "," << value.second << ")\n";
        num_errors()++;
      }
    }

    // implementation for ranges
    template <class T1, class T2,
      class = decltype(std::declval<T1>().cbegin(), std::declval<T2>().cbegin()) >
    inline void _test_approx(T1 const& expr_range, T2 const& range,
                             char const* expr_str, char const* value_str, char const* file, size_t line)
    {
      auto it1 = expr_range.cbegin();
      auto it2 = range.cbegin();

      for(; it1 != expr_range.cend(); ++it1, ++it2)
        _test_approx(*it1, *it2, expr_str, value_str, file, line);
    }

    /// Tests whether an expression throws an exception
    template <class T1, class T2>
    inline void _test_throws(char const* expr, char const* file, size_t line)
    {
      std::cerr << file << ":" << line
               << "  EXPR( " << expr << " ) should throw\n";
      num_errors()++;
    }
  } // end namspace impl

} // end namespace scprog
