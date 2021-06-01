#pragma once

#include <cassert>
#include <cmath>
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
        // construct and initialize the vector of dimension size
        Vector (size_type size);

        // mutable access to the vector entries
        value_type& operator[] (size_type i);

        // const access to the vector entries
        value_type const& operator[] (size_type i) const;

        // return the number of vector entries
        size_type size () const;

        // print a vector
        void print();

        // arithmetic compound assignment operators for vectors
        Vector& operator+= (Vector const& v);     // addition
        Vector& operator-= (Vector const& v);     // difference
        Vector& operator*= (value_type const k);  // scalar multiplication

    private:
        std::vector<double> data_;
    };

    // arithmetic operators for vectors
    Vector operator+ (Vector tmp, Vector& v2);          // addition
    Vector operator- (Vector tmp, Vector& v2);          // difference
    Vector operator* (Vector::value_type k, Vector v);  // scalar multplication

    // more functions appliable on vectors
    Vector::value_type dot(Vector const& v, Vector const& w);   // dot product
    double norm (Vector const& v);                              // euclidean norm

} // end namespace scprog
