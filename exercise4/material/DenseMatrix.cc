#include "DenseMatrix.hh"
#include "Vector.hh"

#include <iostream>

namespace scprog
{
    using size_type = DenseMatrix::size_type;
    using value_type = DenseMatrix::value_type;

    // copy constructor
    DenseMatrix::DenseMatrix (DenseMatrix const& mat) {
        // if matrices do not have the same size, initial matrix is re-
        // initialized to match the matrix that is to be copied
        if(!(mat.rows() == DenseMatrix::rows()) && 
           !(mat.cols() == DenseMatrix::cols())) {
            // erase all initial data to free memory space
            data_.clear();
            rows_ = mat.rows();
            cols_ = mat.cols();
            data_ = std::vector<value_type>(rows_*cols_);
        }
        // write the input to be copied into the initial matrix
        for (size_type i = 0; i < mat.rows(); ++i) {
            for (size_type j = 0; j < mat.cols(); ++j)
                data_[i*DenseMatrix::cols() + j] = mat(i,j);
        }
    }

    // operator to access matrix-entries and change them 
    // *Comment: It would be nice to use operator[], however that operator 
    // only allows one function argument. Hence, this is not useful for 
    // matrices
    value_type& DenseMatrix::operator()(size_type i, size_type j)
    {
        return data_[DenseMatrix::cols()*i + j];
    }

    // operator to ask for specific matrix-entries 
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

    // returns the maximum of a given column
    value_type DenseMatrix::colmax(size_type k) const 
    {
        value_type val_colmax = DenseMatrix::operator()(0, k);
        for (size_type i = 1; i < rows(); ++i)
            val_colmax = std::max(val_colmax, DenseMatrix::operator()(i,k));
        return val_colmax;
    }

    // returns the maximum of a given row
    value_type DenseMatrix::rowmax(size_type k) const
    {
        value_type val_rowmax = DenseMatrix::operator()(k, 0);
        for (size_type j = 1; j < cols(); ++j)
            val_rowmax = std::max(val_rowmax, DenseMatrix::operator()(k, j));
        return val_rowmax;
    }

    // returns the index of a column maximum
    size_type DenseMatrix::colargmax(size_type k) const
    {
        size_type imax = 0;
        for (size_type i = 1; i < rows(); ++i) {
            imax = (std::abs(DenseMatrix::operator()(imax, k)) > 
                    std::abs(DenseMatrix::operator()(i, k))) ? imax : i;
        }
        return imax;
    }

    // returns the index of a row maximum
    size_type DenseMatrix::rowargmax(size_type k) const
    {
        size_type jmax = 0;
        for (size_type j = 1; j < cols(); ++j) {
            jmax = (std::abs(DenseMatrix::operator()(k, jmax)) > 
                    std::abs(DenseMatrix::operator()(k, j))) ? jmax : j;
        }
        return jmax;
    }

    // calculate y = A*x
    void DenseMatrix::mv(Vector const& x, Vector& y) const
    {
        assert(x.size() == DenseMatrix::rows());
        if (y.size() != DenseMatrix::cols()) 
            y = Vector(DenseMatrix::cols());
        for (size_type i = 0; i < y.size(); ++i) {
            value_type tmp = 0.0;
            for (size_type j = 0; j < x.size(); ++j) 
                tmp += DenseMatrix::operator()(i,j)*x[j];
            y[i] = tmp;
        }
    }

    // fill a DenseMatrix with a given data-vector
    DenseMatrix& DenseMatrix::fill(std::vector<value_type> data, 
                                   size_type const rows, 
                                   size_type const cols)    
    {
        // if the given data is not of the same size as the initial matrix, the
        // matrix is resized and the initial data is deleted
        if (data.size() != DenseMatrix::rows()*DenseMatrix::cols()) {
            data_.clear();
            data_ = std::vector<value_type>(data.size());
            rows_ = rows;
            cols_ = cols;
        }

        for (size_type i = 0; i < data.size(); ++i)
            data_[i] = data[i];
        return *this;
    }

    // specific fill method, create a quadratic identity matrix of given size
    DenseMatrix& DenseMatrix::eyes(size_type const rows, size_type const cols)
    {
        // the initial matrix is resized and refilled to meet the given 
        // specifications
        if (rows*cols != DenseMatrix::rows()*DenseMatrix::cols()) {
            data_.clear();
            data_ = std::vector<value_type>(rows*cols);
            rows_ = rows;
            cols_ = cols;
        }

        for (size_type i = 0; i < rows; ++i) {
            for (size_type j = 0; j < cols; ++j) {
                if (i == j) {
                    DenseMatrix::operator()(i,j) = 1.0;
                } else {
                    DenseMatrix::operator()(i,j) = 0.0;
                }
            }
        }
        return *this;
    }

    // copy a given DenseMatrix into another pre-initialized DenseMatrix
    DenseMatrix& DenseMatrix::operator=(DenseMatrix const& that)
    {
        // if both matrices are not equal from the beginning, the initial 
        // matrix is resized and the data is deleted, so that it can fit the
        // matrix to be copied
        if (this != &that) {
            data_.clear();
            rows_ = that.rows();
            cols_ = that.cols();
            data_ = std::vector<value_type>(rows_*cols_);

            for (size_type i = 0; i < rows_*cols_; ++i)
                data_[i] = that.data_[i];
        }
        return *this;
    }
}
