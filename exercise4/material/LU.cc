#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

#include <iostream>

namespace scprog
{

/*
If the matrix m has only one row (so has only one element), then L has only one entry "1" and U is the matrix m. 
Otherwise, we separate the first row and column to get a block matrix (A11, A12 // A21, A22). 
From A11, A12, A21 we can calculate the first row and column of L and U and then recursively decomposite A22. Then we need to put everything back together.
*/
void LU::compute (DenseMatrix const& m)
{
	DenseMatrix::size_type const n{m.rows()};
  if (n == 1){
    decomposition_ = m;
    return;
  }

  DenseMatrix::value_type L11{1}, U11{ m(0, 0) };
  Vector m12{n-1}, m21{n-1}, L12{n-1}, L21{n-1}, U12{n-1}, U21{n-1};
	DenseMatrix m22{n-1, n-1}, L22{n-1, n-1}, U22{n-1, n-1}, S22{n-1, n-1};
	LU recurs{m.rows()};

	//m11 = m(0, 0);
	//m12 = m(0, 1:n);
	for (DenseMatrix::size_type i{1}; i < n; ++i) {
		m12[i-1] = m(0, i);
	}
	
	//m21 = m(1:n, 0);
	for (DenseMatrix::size_type i{1}; i < n; ++i) {
		m21[i-1] = m(i, 0);
	}
	
	//m22 = m(1:n, 1:n);
	for (DenseMatrix::size_type i{1}; i < n; ++i) {
		for (DenseMatrix::size_type j{1}; j < n; ++j) {
			m22(i-1, j-1) = m(i, j);
		}
	}

	//L11 = 1;
	//U11 = m11;
	//L12 = zeros
	U12 = m12;
	L21 = m21;
	L21.scale(1/U11);
	//U21 = zeros
	S22 = m22 - prod(L21, U12);
	recurs.compute (S22);

	decomposition_(0, 0) = U11;
	for (DenseMatrix::size_type i{1}; i < n; ++i) {
		decomposition_(0, i) = U12[i-1];
	}
	for (DenseMatrix::size_type i{1}; i < n; ++i) {
		decomposition_(i, 0) = L21[i-1];
	}
	for (DenseMatrix::size_type i{1}; i < n; ++i) {
		for (DenseMatrix::size_type j{1}; j < n; ++j) {
			decomposition_(i, j) = recurs.decomposition_ (i-1, j-1);
		}
	}
}

/*
First we solve L*y = b, then U*x = y. Because of the triangular matrices, we start at the first or last row and compute one component with each row.
In the second loop, i goes from n-1 to 0. Since i is unsigned, the check isn't "i >= 0" but "i < n".
*/
void LU::apply (Vector const b, Vector& x) const
{
  DenseMatrix::size_type const n{decomposition_.rows()};
  Vector y{n};
  DenseMatrix::value_type tmp{};

	y[0] = b[0]; // first row of L has only a one
  for (DenseMatrix::size_type i{1}; i < n; ++i) {
    tmp = b[i];
    for (DenseMatrix::size_type j{0}; j < i; ++j) {
      tmp -= decomposition_(i, j) * y[j];
    }
    y[i] = tmp; // its tmp/L(i,i), but the diagonal of L is 1
  }

  for (DenseMatrix::size_type i{n-1}; i < n; --i) {
	  tmp = y[i];
    for (DenseMatrix::size_type j{i+1}; j < n; ++j) {
      tmp -= decomposition_(i, j) * x[j];
    }
    x[i] = tmp / decomposition_(i, i);
  }
}

DenseMatrix LU::get ()
{
	return decomposition_;
}

} // end namespace