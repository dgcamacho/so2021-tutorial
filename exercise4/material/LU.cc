#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

#include <iostream>

namespace scprog
{
void LU::compute (DenseMatrix const& m)
  {
    std::size_t NumberRows = m.rows();
    std::size_t NumberCols = m.cols();

    DenseMatrix L(NumberRows, NumberCols);
    decomposition_ = m;
      
    // goes through all the columns
    for (std::size_t k=0; k<NumberCols; ++k) 
    {   
      // goes through lines i=k+1 till NumberRows
      for (std::size_t i=k+1; i<NumberRows; ++i)
      {   
	    L(i,k) = decomposition_(i,k) / decomposition_(k,k);
	    decomposition_(i,k) = 0;	
			
	    // goes through columns j=k+1 till NumberCols
	    for (std::size_t j=k+1; j<NumberCols; ++j)
   	    {
	      decomposition_(i,j) = decomposition_(i,j) - L(i,k) * decomposition_(k,j);
	    }
	  }	
	}
	   
    // fill values of L into decomposition_
    
	// goes through rows
	for (std::size_t i=1; i<NumberRows; ++i)
	{
	  // goes through columns
	  for (std::size_t j=0; j<i; ++j)
	  {
		decomposition_(i,j) = L(i,j); 
	  }	  
	}	   
  }
  
void LU::apply (Vector const& b, Vector& x) const
  {
    // forwards application: solve L*y=b    
    std::size_t const n = x.size();
    double sum = 0;
    Vector y(n);
    y[0] = b[0];
 
    // calculate components y[1],...,y[n-1]
    for (std::size_t i = 1; i<n; ++i)
    {
	  // calculate sum for component y[i]
	  for (std::size_t k=0; k<i; ++k) 
	  {
	    sum += decomposition_(i,k) * y[k];
	  }
	  y[i] = b[i] - sum;
	  sum = 0;
	}
      
    // backwards application: solve U*x=y
    x[n-1] = y[n-1] / decomposition_(n-1,n-1);
    for (std::size_t i=n-1; i>0; --i)
    {
	  sum = 0;
	  for (std::size_t k = i+1; k<n; ++k)
	  {
	    sum += decomposition_(i,k) * x[k];
	  } 
	    x[i] = (y[i] - sum) / decomposition_(i,i);
	  }
	  
	  // component x[0] now solved manually
	  sum = 0;
	  for (std::size_t k = 1; k<n; ++k)
	  {
	    sum += decomposition_(0,k) * x[k];
	  }
	  x[0] = (y[0] - sum) / decomposition_(0,0);    
  }
} // end namespace scprog
