#include "DenseMatrix.hh"
#include "Vector.hh"
#include "Util.hh"

#include <cassert>

namespace scprog {

DenseMatrix::DenseMatrix (size_type const rows, size_type const cols)
{
  /*...*/
}


DenseMatrix::value_type& DenseMatrix::operator() (size_type const i, size_type const j)
{
  /*...*/
}


DenseMatrix::value_type const& DenseMatrix::operator() (size_type const i, size_type const j) const
{
  /*...*/
}


DenseMatrix::size_type DenseMatrix::rows () const
{
  /*...*/
}


DenseMatrix::size_type DenseMatrix::cols () const
{
  /*...*/
}


void DenseMatrix::mv (Vector const& x, Vector& y) const
{
  /*...*/
}

} // end namespace scprog
