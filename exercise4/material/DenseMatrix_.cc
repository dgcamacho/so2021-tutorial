#include <iostream>

#include "DenseMatrix_.hh"
#include "Vector_.hh"

namespace scprog
{
    using size_type = DenseMatrix::size_type;
    using value_type = DenseMatrix::value_type;

    DenseMatrix::DenseMatrix (DenseMatrix const& mat) {
        assert((DenseMatrix::cols() == mat.cols()) && 
               (DenseMatrix::rows() == mat.rows()));
        for (size_type i = 0; i < mat.rows(); ++i) {
            for (size_type j = 0; j < mat.cols(); ++j)
                data_[i*DenseMatrix::cols() + j] = mat(i,j);
        }
    }

    value_type& DenseMatrix::operator()(size_type i, size_type j)
    {
        return data_[DenseMatrix::cols()*i + j];
    }

    value_type const& DenseMatrix::operator()(size_type i, size_type j) const 
    {
        return data_[DenseMatrix::cols()*i + j];
    }

    size_type DenseMatrix::rows() const 
    {
        return rows_;
    }

    size_type DenseMatrix::cols() const 
    {
        return cols_;
    }

    void DenseMatrix::mv(Vector const& x, Vector& y) const
    {
        assert(x.size() == DenseMatrix::rows());
        //assert(y.size() == DenseMatrix::cols());
        if (y.size() != DenseMatrix::cols()) 
            y = Vector(DenseMatrix::cols());
        for (size_type i = 0; i < y.size(); ++i) {
            value_type tmp = 0.0;
            for (size_type j = 0; j < x.size(); ++j) 
                tmp += DenseMatrix::operator()(i,j)*x[j];
            y[i] = tmp;
        }
    }
}
