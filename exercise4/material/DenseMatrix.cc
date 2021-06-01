#include <cassert>
#include <iomanip>

#include "DenseMatrix.hh"
#include "Vector.hh"

namespace scprog {

DenseMatrix::DenseMatrix (size_type const rows, size_type const cols)
{
    rows_ = rows;
    cols_ = cols;
    data_ = std::vector<value_type>(rows_ * cols_, 0.0);
}

DenseMatrix::value_type& DenseMatrix::operator() (size_type const i, size_type const j)
{
    return data_[i * cols_ + j];
}


DenseMatrix::value_type const& DenseMatrix::operator() (size_type const i, size_type const j) const
{
    return data_[i * cols_ + j];
}


DenseMatrix::size_type DenseMatrix::rows () const
{
    return rows_;
}


DenseMatrix::size_type DenseMatrix::cols () const
{
    return cols_;
}


void DenseMatrix::mv (Vector const& x, Vector& y) const
{
    for (DenseMatrix::size_type i = 0; i < rows(); ++i){
        // iterate over rows to compute each entry of y
        y[i] = 0;
        for (DenseMatrix::size_type j = 0; j < cols(); ++j){
            // iterate over all entries in a coloumn
            y[i] += (*this)(i,j) * x[j];
        }
    }
}

void DenseMatrix::print () {
    int const wid = 6;
    int const prec = 2;
    std::cout.setf(std::ios::fixed);

    for (DenseMatrix::size_type i = 0; i < rows_; ++i){
        std::cout << "  [ ";
        for (DenseMatrix::size_type j = 0; j < cols_ - 1; ++j){
            std::cout << std::setw(wid) << std::setprecision(prec) << (*this)(i,j) << ", ";
        }
        std::cout << std::setw(wid) << std::setprecision(prec) << (*this)(i, cols_ - 1) << " ]" << std::endl;
    }
}

} // end namespace scprog
