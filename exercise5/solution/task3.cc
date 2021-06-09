// compile with c++ -std=c++17 Vector.cc task3.cc

#include <cmath>
#include <iostream>
#include <limits>

#include "Vector.hh"
#include "Tests.hh"

using namespace scprog;

bool almost_equal (double const x, double const y, int ulp = 2)
{
  return std::abs(x-y) <= std::numeric_limits<double>::epsilon() * std::abs(x+y) * ulp
      || std::abs(x-y) < std::numeric_limits<double>::min();
}

bool almost_equal (Vector const& lhs, Vector const& rhs, int ulp = 2)
{
  if (lhs.size() != rhs.size())
    return false;

  for (Vector::size_type i = 0; i < lhs.size(); ++i)
    if (!almost_equal(lhs[i], rhs[i], ulp))
      return false;

  return true;
}

void fill (Vector& vec, Vector::value_type init = 0)
{
  for (Vector::size_type i = 0; i < vec.size(); ++i)
    vec[i] = init + i;
}

int main()
{
  Vector v1{5}, v2{5}, v3{5}, v4{6};

  // 2. test the construction
  SCPROG_TEST_EQ(v1.size(), 5);
  SCPROG_TEST_EQ(v2.size(), 5);
  SCPROG_TEST_EQ(v3.size(), 5);
  SCPROG_TEST_EQ(v4.size(), 6);

  fill(v1);
  fill(v2);
  fill(v3, 42);
  fill(v4);

  // 2. test the generated data and the test function
  SCPROG_TEST(almost_equal(v1,v1));
  SCPROG_TEST(almost_equal(v1,v2));
  SCPROG_TEST(!almost_equal(v1,v3));
  SCPROG_TEST(!almost_equal(v1,v4));

  // 3. test the arithmetic operations
  auto w1 = v1 + v2;
  auto w2 = v1;
  w2 += v2;
  SCPROG_TEST(almost_equal(w1,w2));

  auto w3 = v1 - v2;
  auto w4 = v1;
  w4 -= v2;
  SCPROG_TEST(almost_equal(w3,w4));

  auto w5 = v1 + v1;
  auto w6 = 2 * v1;
  auto w7 = v1 * 2;
  auto w8 = v1;
  w8 *= 2;
  SCPROG_TEST(almost_equal(w5,w6));
  SCPROG_TEST(almost_equal(w5,w7));
  SCPROG_TEST(almost_equal(w5,w8));

  auto w9 = v1 / 2;
  auto w10 = v1;
  w10 /= 2;
  SCPROG_TEST(almost_equal(w9,w10));

  auto w11 = -v3;
  auto w12 = -1 * v3;
  auto w13 = v3 * -1.0;
  SCPROG_TEST(almost_equal(w11,w12));
  SCPROG_TEST(almost_equal(w11,w13));

  return report_errors();
}