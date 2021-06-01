#include "Vector.hh"

namespace scprog {

Vector::Vector (size_type const size) {
    data_ = std::vector<value_type>(size, 0.0);
}

Vector::value_type& Vector::operator[] (size_type const i) {
    return data_[i];
}

Vector::value_type const& Vector::operator[] (size_type const i) const {
    return data_[i];
}

Vector::size_type Vector::size () const {
    return data_.size();
}


// print a vector as inline list
void Vector::print () {
    std::cout << "[ ";
    for (Vector::size_type i = 0; i < this->size() - 1; ++i){
        std::cout << (*this)[i] << ", ";
    }
    std::cout << (*this)[this->size() - 1] << " ]" << std::endl;
}


// basic arithmetic operations for vectors (addition, difference, scalar multiplications)
// all operators are based on compound assignment operators

Vector& Vector::operator+= (Vector const& v) {
    assert(size() == v.size());
    for (Vector::size_type i = 0; i < size(); ++i)
        data_[i] += v[i];   // += operator for entries

    return *this;
}

Vector& Vector::operator-= (Vector const& v) {
    assert(size() == v.size());
    for (Vector::size_type i = 0; i < size(); ++i)
        data_[i] -= v[i];   // -= operator for entries

    return *this;
}

Vector& Vector::operator*= (Vector::value_type const k) {
    for (Vector::size_type i = 0; i < size(); ++i)
        data_[i] *= k;      // *= operator for entries

    return *this;
}

Vector operator+ (Vector tmp, Vector& v2) {
    assert(tmp.size() == v2.size());
    tmp += v2;    // += operator for Vector

    return tmp;
}

Vector operator- (Vector tmp, Vector& v2) {
    assert(tmp.size() == v2.size());
    tmp -= v2;    // -= operator for Vector

    return tmp;
}

Vector operator* (Vector::value_type const k, Vector v) {
    v *= k;     // *= operator for Vector
    return v;
}


Vector::value_type dot (Vector const& v, Vector const& w) {
    assert(v.size() == w.size());
    Vector::value_type result = {0};
    for (Vector::size_type i = 0; i < v.size(); ++i){
        result += v[i] * w[i];
    }
    return result;
}

double norm (Vector const& v) {
    return std::sqrt(dot(v,v));
}


} // end namespace scprog
