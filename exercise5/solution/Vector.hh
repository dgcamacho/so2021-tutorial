#pragma once

#include <cassert>
#include <vector>

namespace scprog
{
  class Vector
  {
  public:
    // The data type of the matrix entries
    using value_type = double;

    // The data type of the size and indices
    using size_type = std::size_t;

  public:
    // construct and initialize the matrix of size rows x cols
    Vector (size_type size);

    // mutable access to the matrix entries
    value_type& operator[] (size_type i)
    {
      assert(i < size());
      return data_[i];
    }

    // const access to the matrix entries
    value_type const& operator[] (size_type i) const
    {
      assert(i < size());
      return data_[i];
    }

    // return the number of vector entries
    size_type size () const
    {
      return data_.size();
    }

    // elementwise addition
    Vector& operator+=(Vector const&);

    // elementwise subtraction
    Vector& operator-=(Vector const&);

    // elementwise multiplication with factor
    Vector& operator*=(value_type factor);

    // elementwise division by factor
    Vector& operator/=(value_type factor);

    // negation
    Vector operator-();

  private:
    std::vector<double> data_;
  };

  // addition
  Vector operator+(Vector const&, Vector const&);

  // subtraction
  Vector operator-(Vector const&, Vector const&);

  // multiplication from the left with factor
  Vector operator*(Vector::value_type factor, Vector const&);

  // multiplication from the right with factor
  Vector operator*(Vector const&, Vector::value_type factor);

  // division from the right by factor
  Vector operator/(Vector const&, Vector::value_type factor);

} // end namespace scprog
