#include "Vector.hh"
#include <algorithm>
#include <iostream>
#include <vector>



namespace scprog 
{
    using size_type = Vector::size_type;
    using value_type = Vector::value_type;

    template <typename T>
    bool almost_equal(T const x, T const y, int ulp = 2)
    // machine-dependent tolerance value for equality-comparisons
    {
        double const eps = std::numeric_limits<T>::epsilon();
        double const min = std::numeric_limits<T>::min();

        return ((std::abs(x - y) <= eps*std::abs(x + y) * ulp ) ||
                (std::abs(x - y) <= min));

    }

    // copy constructor
    Vector::Vector (Vector const& v) {
        // the size of the initial vector is resized to fit the size of the 
        // vector to be copied and the data is deleted to free memory space
        if(Vector::size() != v.size()) {
            // free up memory space occupied by the old data
            data_.clear();
            rows_ = v.size();
            data_ = std::vector<value_type>(v.size());
        }
        for (size_type i = 0; i < v.size(); ++i) 
            data_[i] = v.data_[i];
    }

    // access vector-entries and change them
    value_type& Vector::operator[](size_type i)
    {
        return data_[i];
    }

    // ask for specific  vector-entries
    value_type const& Vector::operator[](size_type i) const
    {
        return data_[i];
    }

    size_type Vector::size() const 
    {
        return rows_;
    }

    Vector& Vector::operator+=(Vector const& v)
    {
        assert(size() == v.size());
        for (size_type i = 0; i < size(); ++i)
            data_[i] += v[i];
        return *this;
    }

    Vector& Vector::operator-=(Vector const& v)
    {
        assert(size() == v.size());
        for (size_type i = 0; i < size(); ++i)
            data_[i] -= v[i];
        return *this;
    }

    Vector& Vector::operator*=(value_type const scale)
    {
        for (size_type i = 0; i < size(); ++i)
            data_[i] *= scale;
        return *this;
    }

    Vector& Vector::operator/=(value_type const scale)
    {
        for (size_type i = 0; i < size(); ++i)
            data_[i] /= scale;
        return *this;
    }

    // fill a vector with a given data-vector
    Vector& Vector::fill(std::vector<value_type> data, size_type size)
    {
        if (data.size() != Vector::size()) {
            data_.clear();
            rows_ = size;
            data_ = std::vector<value_type>(data.size());
        }
        for (size_type i = 0; i < data.size(); ++i)
            data_[i] = data[i];
        
        return *this;
    }

    // find the maximum of a given vector
    value_type Vector::max() const {
        value_type val_max = data_[0];
        for (size_type i = 1; i < size(); ++i) 
            val_max = std::max(val_max, data_[i]);
        return val_max;
    }

    // find the minimum of a given vector
    value_type Vector::min() const {
        value_type val_min = data_[0];
        for (size_type i = 1; i < size(); ++i)
            val_min = std::min(val_min, data_[i]);
        return val_min;
    }

    // find the index of the maximum of a given vector
    size_type Vector::argmax() const {
        size_type imax = 0;
        for (size_type i = 1; i < size(); ++i) 
            imax = (std::abs(data_[imax]) > std::abs(data_[i])) ? imax : i;
        return imax;
    }

    // find the index of the minimum of a given vector
    size_type Vector::argmin() const {
        size_type imin = 0;
        for (size_type i = 1; i < size(); ++i)
            imin = (std::abs(data_[imin]) < std::abs(data_[i])) ? imin : i;
        return imin;
    }

    void Vector::printV() const {
        for (size_type i = 0; i < this->size(); ++i) {
            std::cout << this->operator[](i) << std::endl;
        }
    }

    Vector operator+(Vector const& vec_1, Vector const& vec_2)
    {
        Vector tmp(vec_1);
        return tmp+=vec_2;
    }

    Vector operator-(Vector const& vec_1, Vector const& vec_2)
    {
        Vector tmp(vec_1);
        return tmp+=vec_2;
    }

    // calculates vector dotproduct
    value_type dot(Vector const& v1, Vector const& v2)
    {
        assert(v1.size() == v2.size());
        double dotproduct = 0.0;
        for (size_type i = 0; i < v1.size(); ++i)
            dotproduct += v1[i]*v2[i];
        return dotproduct;
    }

    // scales all entries of a given vector
    Vector operator*(value_type const scale, Vector const& v)
    {
        Vector tmp{v};
        return tmp*=scale;
    }

    Vector operator*(Vector const& v, value_type const scale)
    {
        Vector tmp(v);
        return tmp*=scale;
    }

    Vector operator/(Vector const& v, value_type const scale)
    {
        Vector tmp(v);
        return tmp/=scale;
    }

    // checks equality of two vectors using the tolerance function implemented
    // above
    bool operator==(Vector const& v1, Vector const& v2)
    {
        assert(v1.size() == v2.size());
        for (size_type i = 0; i < v1.size(); ++i)
            assert(almost_equal(v1[i], v2[i]));
        return 1;
    }
}
