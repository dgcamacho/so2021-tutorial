#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>

#include "Vector.hh"

namespace scprog {

template <typename T>
class CRSMatrix {
	public:
		using value_type = T;
		using size_type = std::size_t;
	
	
		CRSMatrix( size_type rowCnt, size_type colCnt, size_type maxNonZeroEntriesPerRow )
      : values(colCnt * maxNonZeroEntriesPerRow), indices(colCnt * maxNonZeroEntriesPerRow), offset(rowCnt, 0), rowCount(rowCnt), colCount(colCnt), maxNonzeroPerRow(maxNonZeroEntriesPerRow) {}
		
		void add( size_type i, size_type j, value_type value );
		void set( size_type i, size_type j, value_type value );
		
		void compress();
		
		void mv( Vector const& x, Vector&y ) const;
    
    template < typename U >
    friend std::ostream& operator<<(std::ostream& out, CRSMatrix<U> const& other);
	
	private:
		bool entryExists( size_type i, size_type j ) const;
		size_type findValuesIndex( size_type i, size_type j ) const;
		void insertEntry( size_type i, size_type j, value_type value );
	
		std::vector<T> 	values;
		std::vector<size_type>  indices, offset;
		size_type const rowCount, colCount, maxNonzeroPerRow;
};


#include "CRSMatrix.hh.impl"


}
