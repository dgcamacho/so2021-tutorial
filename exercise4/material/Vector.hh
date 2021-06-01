#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <limits>
#include <vector>

namespace scprog 
{
    class Vector 
    {
        public:
            using size_type = std::size_t;
            using value_type = double;
        public:
            // construct empty vector
            Vector():rows_{0} {}

            // construct zero vector of given size
            Vector(size_type nrows):rows_{nrows} {
                data_ = std::vector<value_type>(nrows);
            }
            
            // copy constructor
            Vector(Vector const& v);

            // access operator
            value_type& operator[] (size_type i);

            // access operator to ask for specific entry but not change it
            value_type const& operator[](size_type i) const;

            size_type size() const;

            Vector& operator+=(Vector const& v);

            Vector& operator*=(value_type const scale);

            // fill initial vector with data-vector
            Vector& fill(std::vector<value_type> data, size_type size);

            // return maximum entry of vector
            value_type max() const;

            // return minimum entry of vector
            value_type min() const;

            // return index of maximum entry of vector
            size_type argmax() const;

            // return index of minimum entry of vector
            size_type argmin() const;

            // print vector
            void printV() const;

            friend Vector operator+(Vector tmp, Vector const& v);

            // usual vector dotproduct
            friend value_type dot(Vector const& v1, Vector const& v2);

            friend Vector operator*(value_type const scale, Vector const& v);

            friend Vector operator-(Vector tmp, Vector const& v);

            friend bool operator==(Vector const& v1, Vector const& v2);

        private:
            size_type rows_;
            std::vector<value_type> data_;
    };
}


