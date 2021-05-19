#pragma once

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
            Vector():rows_{0} {}

            Vector(size_type nrows):rows_{nrows} {
                data_ = std::vector<value_type>(nrows);
            }
            
            Vector(Vector const& v);

            value_type& operator[] (size_type i);

            value_type const& operator[](size_type i) const;

            size_type size() const;

            Vector& operator+=(Vector const& v);

            Vector& operator*=(value_type const scale);

            friend Vector operator+(Vector tmp, Vector const& v);

            friend value_type dot(Vector const& v1, Vector const& v2);

            friend Vector operator*(value_type const scale, Vector const& v);

            friend Vector operator-(Vector tmp, Vector const& v);

            friend bool operator==(Vector const& v1, Vector const& v2);

        private:
            size_type rows_;
            std::vector<value_type> data_;
    };
    
    /*
    template <typename T>
    bool inline almost_equal(T const x, T const y)
    {
        double const eps = std::numeric_limits<T>::epsilon();
        double const min = std::numeric_limits<T>::min();

        int ulp = 2;

        return ((std::abs(x - y) <= eps*std::abs(x + y) * ulp ) ||
                (std::abs(x - y) <= min));
    }
    */

}


