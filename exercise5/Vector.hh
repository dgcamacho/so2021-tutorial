#pragma once

#include <iostream>
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
    Vector (Vector const&);
    
    Vector& operator =(Vector const&);

    Vector& operator+=(Vector const&);
    Vector& operator-=(Vector const&);
    Vector& operator*=(value_type const);
    Vector& operator/=(value_type const);

    // mutable access to the matrix entries
    value_type& operator[] (size_type i);

    // const access to the matrix entries
    value_type const& operator[] (size_type i) const;
    
    void fill(value_type val);

    // return the number of vector entries
    size_type size () const;

  private:
    std::vector<double> data_;
  };
  
  Vector operator+(Vector const& lhs, Vector const& rhs);
  Vector operator-(Vector const& lhs, Vector const& rhs);
  Vector operator*(Vector::value_type const factor, Vector const& vec);
  Vector operator*(Vector const& vec, Vector::value_type const factor);
  Vector operator/(Vector const& vec, Vector::value_type const factor);
  
  std::ostream& operator<<(std::ostream& out, Vector const& other);

} // end namespace scprog
