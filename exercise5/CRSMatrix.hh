#pragma once

#include <vector>

namespace scprog
{
	class Vector;

	template <typename T>
	class CRSMatrix
	{
	  public:
		using value_type = T;
		using size_type = std::size_t;
		
	  public:
		
		CRSMatrix (size_type rows, size_type cols, size_type maxNonzero);
		
		void add (size_type i, size_type j, value_type value);
		void set (size_type i, size_type j, value_type value);
		void compress();
		
		void mv (Vector const& x, Vector& y) const;
		
	  private:
		size_type const nrows, ncols;
		std::vector<size_type> offset;
		std::vector<size_type> indices;
		std::vector<value_type> values;
		
	};	
}
