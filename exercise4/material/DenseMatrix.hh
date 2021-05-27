#pragma once

#include <vector>

namespace scprog
{
	// forward declaration
	class Vector;

	class DenseMatrix
	{
	public:
		// The data type of the matrix entries
		using value_type = double;

		// The data type of the size and indices
		using size_type = std::size_t;

	public:
		// construct and initialize the matrix of size rows x cols
		DenseMatrix (size_type rows, size_type cols);

		// copy constructor
		DenseMatrix (DenseMatrix const& m);

		// mutable access to the matrix entries
		value_type& operator() (size_type i, size_type j);

		// const access to the matrix entries
		value_type const& operator() (size_type i, size_type j) const;

		DenseMatrix& operator*= (DenseMatrix const& other);

		DenseMatrix& operator-= (DenseMatrix const& other);

    DenseMatrix& operator= (DenseMatrix const& that);
		
		// return the number of rows
		size_type rows () const;

		// return the number of columns
		size_type cols () const;

		// matrix-vector product y = A*x
		void mv (Vector const& x, Vector& y) const;

		// scales the matrix by a factor, changes the matrix
		void scale (double factor);

	private:
		size_type rows_;
		size_type cols_;
		std::vector<value_type> data_;
	};

	// product of two vectors resulting in a matrix
	DenseMatrix prod (Vector const& vec1, Vector const& vec2);

} // end namespace scprog

scprog::DenseMatrix operator* (scprog::DenseMatrix const& lhs, scprog::DenseMatrix const& rhs);

scprog::DenseMatrix operator- (scprog::DenseMatrix const& lhs, scprog::DenseMatrix const& rhs);
