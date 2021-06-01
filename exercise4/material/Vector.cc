#include <iostream>
#include <cmath>
#include <limits>

#include "Vector.hh"

namespace scprog {

Vector::Vector (size_type const size) {
  data_ = std::vector<value_type> (size, 0);
}


// standard access operators
Vector::value_type& Vector::operator[] (size_type const i) {
    return data_[i];
}

Vector::value_type const& Vector::operator[] (size_type const i) const {
  return data_[i];
}


// size information
Vector::size_type Vector::size () const {
  return data_.size();
}


// inner product
Vector::value_type Vector::dot (Vector const& x) const {
    if (x.size() != data_.size())
    {
      throw std::invalid_argument("Vectors need to be of same size.");
    }
    Vector::value_type res = 0;
    for (int i = 0; i < x.size(); ++i)
    {
      res += x[i] * this->data_[i];
    }
    return res;
}


// standard arithmetic operators
Vector Vector::operator+(const Vector &b) const {
  Vector res = Vector(data_.size());
  for (int i = 0; i < res.size(); ++i)
  {
    res[i] = data_[i] + b[i];
  }
  return res;
}

Vector Vector::operator-(const Vector &b) const {
  Vector res = Vector(data_.size());
  for (int i = 0; i < res.size(); ++i)
  {
    res[i] = data_[i] - b[i];
  }
  return res;
}


// print out the vector
void Vector::print () const {
  if (data_.size() == 0){
    std::cout << "[]\n";
  }
  std::cout << "[";
  for (int i = 0; i < data_.size() - 1; ++i)
  {
    std::cout << (*this)[i] << ", ";
  }
  std::cout << data_[data_.size() - 1] << "]\n";
}


// check if x is (almost) the zero vector
bool Vector::is_null() const {
    value_type eps = std::numeric_limits<value_type>::epsilon();
    for(int i = 0; i < data_.size(); ++i) {
        if(std::abs(data_[i]) > eps){
            return false;
        }
    }
    return true;
}

}
