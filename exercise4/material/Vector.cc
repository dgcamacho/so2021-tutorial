#include "Vector.hh"

#include <cassert>
#include <iomanip>
#include <iostream>

namespace scprog {

Vector::Vector (size_type const size) : data_(size,0) {}

Vector& Vector::operator+=(Vector const& other) {
    for( size_type i{0}; i < size(); i++ ) {
        (*this)[i] += other[i];
    }

    return *this;
}

Vector& Vector::operator-=(Vector const& other) {
    for( size_type i{0}; i < size(); i++ ) {
        (*this)[i] -= other[i];
    } 

    return *this;
}

Vector& Vector::operator*=(Vector::value_type const factor) {
    for( size_type i{0}; i < size(); i++ ) {
        (*this)[i] *= factor;
    }

    return *this;
}

Vector& Vector::operator/=(Vector::value_type const factor) {
    for( size_type i{0}; i < size(); i++ ) {
        (*this)[i] /= factor;
    }

    return *this;
}

Vector::value_type& Vector::operator[] (size_type const i)
{
    assert(i <= size() );
    return data_[i];
}


Vector::value_type const& Vector::operator[] (size_type const i) const
{
    assert( i <= size() );
    return data_[i];
}


Vector::size_type Vector::size () const
{
    return data_.size();
}

Vector operator+(Vector const& lhs, Vector const& rhs) {
    auto tmp{lhs};
    return tmp += rhs;
}
Vector operator-(Vector const& lhs, Vector const& rhs) {
    auto tmp{lhs};
    return tmp-= rhs;
}
Vector operator*(Vector::value_type const factor, Vector const& vec) {
    auto tmp{vec};
    return tmp *= factor;
}
Vector operator*(Vector const& vec, Vector::value_type const factor) {
    auto tmp{vec};
    return tmp *= factor;
}
Vector operator/(Vector const& vec, Vector::value_type const factor) {
    Vector tmp{vec};
    return tmp /= factor;
}

std::ostream& operator<<(std::ostream& out, Vector const& other) {
    using SizeType = Vector::size_type;
  
    for( SizeType i{0}; i < other.size(); i++ ) {
      out << std::setw(10) << other[i] << ' ';
    }
    out << std::endl;
    
    return out;
  }

} // end namespace scprog
