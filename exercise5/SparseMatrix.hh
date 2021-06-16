#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iterator>
#include <utility>
#include <vector>

#include "Vector.hh"

namespace scprog {

template <typename T>
class CRSMatrix {
	public:
		using value_type = T;
		using size_type = std::size_t;
	
	
		CRSMatrix( size_type rowCnt, size_type colCnt, size_type maxNonZeroEntriesPerRow ) : offset(rowCnt, 0), rowCount(rowCnt), colCount(colCnt) {}
		
		void add( size_type i, size_type j, value_type value );
		void set( size_type i, size_type j, value_type value );
		
		void compress() {};
		
		void mv( Vector const& x, Vector&y ) const;
    
    template < typename U >
    friend std::ostream& operator<<(std::ostream& out, CRSMatrix<U> const& other);
	
	private:
		bool entryExists( size_type i, size_type j ) const;
		size_type findValuesIndex( size_type i, size_type j ) const;
		void insertEntry( size_type i, size_type j, value_type value );
	
		std::vector<T> 	values;
		std::vector<size_type>  indices, offset;
		size_type const rowCount, colCount;
};

template < typename T >
bool CRSMatrix<T>::entryExists( size_type i, size_type j ) const {
	return std::binary_search( offset[i] == indices.size() ? indices.end() : indices.begin() + offset[i], i+1 == offset.size() ? indices.end() : indices.begin() + offset[i+1], j );
}
template < typename T >
typename CRSMatrix<T>::size_type CRSMatrix<T>::findValuesIndex( CRSMatrix::size_type i, CRSMatrix::size_type j ) const {
	assert( entryExists(i,j) );
	
	auto const valueIterator = std::find( offset[i] == indices.size() ? indices.end() : indices.begin() + offset[i], i == offset.size() ? indices.end() : indices.begin() + offset[i+1] , j );
	return std::distance( indices.begin(), valueIterator );
}

template < typename T >
void CRSMatrix<T>::insertEntry( CRSMatrix::size_type i, CRSMatrix::size_type j, CRSMatrix::value_type value ) {
	assert( ! entryExists(i,j) );
	
	auto indicesInsertPos = std::lower_bound( offset[i] == indices.size() ? indices.end() : indices.begin() + offset[i], i+1 == offset.size() ? indices.end() : indices.begin() + offset[i+1], j );
	values.insert( values.begin() + std::distance( indices.begin(), indicesInsertPos) , value ); // insert value at the same position as in indices - std::distance() returns the index
	indices.insert( indicesInsertPos, j ); // inserts j BEFORE the position pointed at by indicesInsertPos
	
	//update offset, starting at i+1
	std::transform( offset.begin() + i+1, offset.end(), offset.begin() + i+1, [](CRSMatrix::size_type const index) { return index + 1; } );
}

template < typename T >
void CRSMatrix<T>::add( CRSMatrix::size_type i, CRSMatrix::size_type j, CRSMatrix::value_type value) {
	if( entryExists( i,j ) ) {
		values[ findValuesIndex(i,j) ] += value;
	}
	else {
		insertEntry( i, j, value );
	}
}

template < typename T >
void CRSMatrix<T>::set( CRSMatrix::size_type i, CRSMatrix::size_type j, CRSMatrix::value_type value) {
	if( entryExists( i,j ) ) {
		values[ findValuesIndex(i,j) ] = value;
	}
	else {
		insertEntry( i, j, value );
	}
}

template < typename T >
void CRSMatrix<T>::mv( Vector const& x, Vector& y ) const {
  using size_type = CRSMatrix<T>::size_type;
  
	assert( x.size() == y.size() && colCount == x.size() );
	
	//initialize y with 0
	y.fill( CRSMatrix::value_type{0} );
	
	//store current offset-index to access the correct row
	size_type i = 0;
	for( size_type k = 0; k < values.size(); k++ ) {
		//update the row index
		if( offset[i+1] == k )
			i++;
		
		y[ i ] += values[k] * x[ indices[k] ];
	}
}

template < typename T >
std::ostream& operator<<(std::ostream& out, CRSMatrix<T> const& other) {
  using size_type = CRSMatrix<T>::size_type;
  
  size_type k = 0;
  for( size_type i = 0; i < other.rowCount; i++ ) {
    for( size_type j = 0; j < other.colCount; j++ ) {
      if( other.offset[i] <= k and other.indices[k] == j ) {
        out << std::setw(10) << other.values[k++] << ' ';
      }
      else {
        out << std::setw(10) << 0 << ' ';
      }
    }
    out << std::endl;
  }
  
  return out;
}

}
