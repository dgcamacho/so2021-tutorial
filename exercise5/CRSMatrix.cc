#include "CRSMatrix.hh"
#include "Vector.hh"

#include <cmath>
#include <vector>

namespace scprog
{
	template <typename T>
	CRSMatrix<T>::CRSMatrix (size_type rows, size_type cols, size_type maxNonzero)
	  : nrows(rows)
	  , ncols(cols)
	  , offset(rows+1)
	  , indices(maxNonzero*rows)
	  , values(maxNonzero*rows) 
	{}	
	
	template <typename T>
	void CRSMatrix<T>::add (size_type i, size_type j, value_type value)
	{
		// check whether entry already exists
		size_type const lb = offset[i];
		size_type const up = offset[i+1];
		for (std::size_t k = lb; k<up; ++k)
		{
			if (indices[k] == j)
			{
				// index exists: add it up
				values[k] += value;
			}
			
			if (indices[k] > j)
			{
				// index does not exist
				// insert index/value at position k and shift the whole register one position further
				indices.insert(indices.begin() + k, j);
				values.insert(values.begin() + k, value);
				
				// repair offset-vector (add 1 to each position after the i'th position):
				for (std::size_t k=i+1; k<offset.size(); ++k)
				{
					offset[k] += 1;
				}
				break;
			}	
		}	
	}	

	template <typename T>	
	void CRSMatrix<T>::set (size_type i, size_type j, value_type value)
	{
		// check whether entry already exists
		size_type const lb = offset[i];
		size_type const up = offset[i+1];
		for (std::size_t k = lb; k<up; ++k)
		{
			if(indices[k] == j)
			{
				// index exists: replace it
				values[k] = value;
			}
			
			if (indices[k] > j)
			{
				// index does not exist
				// insert index/value at position k and shift the whole register one position further
				indices.insert(indices.begin() + k, j);
				values.insert(values.begin() + k, value);
				
				// repair offset-vector (add 1 to each position after the i'th position):
				for (std::size_t k=i+1; k<offset.size(); ++k)
				{
					offset[k] += 1;
				}
				break;
			}	
		}	
	}	
	
	template <typename T>
	void CRSMatrix<T>::compress()
	{
		// go through the values[]-vector to search for zero-entries
		// if only nonzero-entries: finished
		// if a zero-entry appears: delete entry, delete the corresponding index
		// in the indices-vector and repair offset-vector
		
		for (size_type i=0; i<values.size(); ++i)
		{
			if (std::abs(values[i]) < 1e-14) // checks for values[i] == 0
			{
				values.erase(values.begin()+i);
				indices.erase(indices.begin()+i);
				for (std::size_t k=i+1; k<offset.size(); ++k)
				{
					offset[k] -= 1;
				}
			}	
		}	
	}	
	
	template <typename T>
	void CRSMatrix<T>::mv (Vector const& x, Vector& y) const
	{
		for (size_type i=0; i < nrows; ++i)
		{
			size_type const lb = offset[i];
			size_type const ub = offset[i+1];
			
			for (size_type j = lb; j < ub; ++j)
			{
				y[i] += values[j] * x[ indices[j] ];
			}	
		}
	}	
} // end namespace scprog	
