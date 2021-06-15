#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

class Vector
{
  std::vector<double> data_;

public:
  Vector (std::size_t const length)
    : data_(length)
  {}

  Vector (std::vector<double> const& data)
    : data_(data)
  {}

  // set all entries to `value`
  Vector& operator= (double const value)
  {
    data_.assign(data_.size(), value);
    return *this;
  }

  // copmute the Euclidean inner product with `y`
  double dot (Vector const y) const
  {
    double sum = 0.0;
    for (size_t i = 0; i < data_.size(); ++i) {
      sum += data_[i] * y(i);
    }
    return sum;
  }

  // compute the Euclidean 2-norm
  double two_norm () const
  {
    return std::sqrt(this->dot(*this));
  }

  // mutable access to ith entry
  double& operator() (std::size_t const i)
  {
    return data_[i];
  }

  // const access to ith entry
  double const& operator() (std::size_t const i) const
  {
    return data_[i];
  }

  // number of entries
  std::size_t size () const
  {
    return data_.size();
  }

  // add y from this elementwise
  Vector& operator+= (Vector const y)
  {
    for (std::size_t i = 0; i < (*this).size(); ++i) {
      (*this)(i) += y(i);
    }
    return *this;
  }

  // subtract y from this elementwise
  Vector& operator-= (Vector const y)
  {
    for (std::size_t i = 0; i < (*this).size(); ++i) {
      (*this)(i) -= y(i);
    }
    return *this;
  }
};

// Elementwise sum of two vectors
Vector operator+ (Vector const x, Vector const y)
{
  Vector tmp(x.size());
  for (std::size_t i = 0; i < x.size(); ++i) {
    tmp(i) = x(i)+y(i);
  }
  return tmp;
}

// Elementwise difference of two vectors
Vector operator- (Vector const x, Vector const y)
{
  Vector tmp(x.size());
  for (std::size_t i = 0; i < x.size(); ++i) {
    tmp(i) = x(i)-y(i);
  }
  return tmp;
}

// Scale the vector from left by `factor`
Vector operator* (double const factor, Vector const y)
{
  Vector tmp(y.size());
  for (std::size_t i = 0; i < y.size(); ++i) {
    tmp(i) = factor*y(i);
  }
  return tmp;
}

// print the vector to the output stream
std::ostream& operator<< (std::ostream& str, Vector const v)
{
  if (v.size() == 0) {
    str << "Vector of size 0";
    return str;
  }
  str << "[" << v(0);
  for (std::size_t i = 1; i < v.size(); ++i) {
    str << ", " << v(i);
  }
  str << "]";
  return str;
}
