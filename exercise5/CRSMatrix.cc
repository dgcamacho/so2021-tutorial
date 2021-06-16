#include "CRSMatrix.hh"

#include <iomanip>
#include <iostream>

namespace scprog {

template < typename T >
std::ostream& operator<<(std::ostream& out, CRSMatrix<T> const& other) {
  using size_type = CRSMatrix<T>::size_type;

  size_type k = 0;
  for( size_type i = 0; i < other.rowCount; i++ ) {
    for( size_type j = 0; j < other.colCount; j++ ) {
      // differ between compressed / uncompressed state
      // potential bug: dense matrix
      if( other.indices.size() < other.rowCount * other.maxNonzeroPerRow ) {
        //prints the corresponding entry or 0
        if( other.offset[i] <= k and other.indices[k] == j ) {
          out << std::setw(10) << other.values[k++] << ' ';
        }
        else {
          out << std::setw(10) << 0 << ' ';
        }
      }
      else {
        out << std::setw(10) << (other.entryExists(i,j) ? other.values[other.findValuesIndex(i,j)] : 0);
      }
    }
    out << std::endl;
  }



  return out;

}

}
