#include "Vector_.hh"

namespace scprog 
{
    using size_type = Vector::size_type;
    using value_type = Vector::value_type;

    template <typename T>
    bool almost_equal(T const x, T const y, int ulp = 2)
    {
        double const eps = std::numeric_limits<T>::epsilon();
        double const min = std::numeric_limits<T>::min();

        return ((std::abs(x - y) <= eps*std::abs(x + y) * ulp ) ||
                (std::abs(x - y) <= min));

    }

    Vector::Vector (Vector const& v) {
        assert(Vector::size() == v.size());
        for (size_type i = 0; i < v.size(); ++i) 
            data_[i] = v.data_[i];
    }

    value_type& Vector::operator[](size_type i)
    {
        return data_[i];
    }

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

    Vector& Vector::operator*=(value_type const scale)
    {
        for (size_type i = 0; i < size(); ++i)
            data_[i] *= scale;
        return *this;
    }

    Vector operator+(Vector tmp, Vector const& v)
    {
        assert(tmp.size() == v.size());
        return tmp+=v;
    }

    value_type dot(Vector const& v1, Vector const& v2)
    {
        assert(v1.size() == v2.size());
        double dotproduct = 0.0;
        for (size_type i = 0; i < v1.size(); ++i)
            dotproduct += v1[i]*v2[i];
        return dotproduct;
    }

    Vector operator*(value_type const scale, Vector const& v)
    {
        Vector v_scale{v};
        return v_scale*=scale;
    }

    Vector operator-(Vector tmp, Vector const& v)
    {
        Vector v_negative = -1.0*v;
        return tmp+=-1.0*v;
    }

    bool operator==(Vector const& v1, Vector const& v2)
    {
        assert(v1.size() == v2.size());
        for (size_type i = 0; i < v1.size(); ++i)
            assert(almost_equal(v1[i], v2[i]));
        return 1;
    }
}
