#pragma once

namespace scprog
{
	class Vector;

	class DenseMatrix; 

	class LU
	{
	public:
		// constructor to get decompositions_ as a n*n matrix  
		LU (DenseMatrix::size_type const n) : decomposition_(n,n) {}

		// decomposing the matrix m, without modifing it
		void compute (DenseMatrix const& m);

		// solves L*U*x = b
		void apply (Vector const b, Vector& x) const;

		// returns decomposition_
		DenseMatrix get ();

	private:
		DenseMatrix decomposition_; // store the decomposition in this matrix
	};

} // end namespace scprog
