#include <cmath> //needed for square root
#include <iostream> //needed for in-/output
#include <ctime> //needed for nice way randomization
#include <cstdlib> //needed for RAND_MAX

//access or change values of the matrix
double& access(double* A, int nrows, int ncols, int i, int j)
{
	return A[i * ncols + j];
}

//calculate the dot product of two vectors vec1, vec2 with a certain number of rows (nrows)
double dot_product(double* vec1, double* vec2, int nrows)
{
	double res = 0.0;

	for(int i = 0; i < nrows; i++)
		res += vec1[i] * vec2[i];

	return res;
}

//calculate the norm of a vector vec with a certain number of rows (nrows)
double norm(double* vec, int nrows)
{
	return std::sqrt(dot_product(vec, vec, nrows));
}

//determine the rayleigh quotient \sigma(A, r)
double rayleigh_quotient(double* A, double* r, int nrows, int ncols)
{
	//auxiliary variables for the elements of Ar and the return value
	//aTimesr is the vector Ar
	double elem = 0.0, result = 0.0;
	double* aTimesr = new double[nrows];

	//calculating Ar
	for(int i=0; i < nrows; i++)
	{
		for(int j=0; j < ncols; j++)
		{
			elem += access(A, nrows, ncols, i, j) * r[j];
		}
		aTimesr[i] = elem;
		elem = 0.0;
	}

	//save the rayleigh quotient as result to deallocate the pointer afterwards
	result = dot_product(r, aTimesr, nrows)/dot_product(r, r, nrows);
	delete[] aTimesr;

	return result;
}

//create a random vector that is not in the kernel of the matrix A
double* find_initial_value(double* A, int nrows, int ncols)
{
	double* r = new double[nrows];
	double elem = 0.0;
	bool isnullvec = true; //used to compute multiple r until r is not in the kernel of A

	std::srand(std::time(nullptr)); //initialise randomization

	while (isnullvec) {

		//fill r with values between -10 and 10
		for(int i=0; i < nrows; i++)
			r[i] = (std::rand()/ ((double) RAND_MAX) - 0.5) * 10;

		//calculate values of Ar, the while loop ends 
		//if one value is not zero (one could then also break out of the for loop, immediately)
		for(int i=0; i < nrows; i++)
		{
			for(int j=0; j < ncols; j++)
			{
				elem += access(A, nrows, ncols, i, j) * r[j];
			}

			if(elem != 0.0)
				isnullvec = false;

			elem = 0.0;
		}
	}

	return r;
}

//function to print the distance current distance between Ar and sigma*r
void test(double* A, double* r, double sigma, int nrows, int ncols)
{
	//auxiliary variables for Ar, the difference Ar-sigma*r and elements of Ar
	double* aTimesr = new double[nrows];
	double* diff = new double[ncols];
	double elem = 0.0;

	//calculate Ar
	for(int i=0; i < nrows; i++)
	{
		for(int j=0; j < ncols; j++)
		{
			elem += access(A, nrows, ncols, i, j) * r[j];
		}
		aTimesr[i] = elem;
		elem = 0.0;
	}

	//calculate the difference
	for(int i=0; i < ncols; i++)
		diff[i] = aTimesr[i] - sigma * r[i];

	std::cout << "The euklidean distance between Ar and sigma*r is given by: "
		<< norm(diff, nrows) << std::endl;

	//deallocate the created pointers
	delete[] aTimesr;
	delete[] diff;
}

//implements the power method algorithm for k iterations
//prints rayleigh coefficient and error in every step
void power_method(double* A, int k, int nrows, int ncols)
{
	//variables for r=r^(k-1) and rnew=r^(k)
	double* r = find_initial_value(A, nrows, ncols);
	double* rnew = new double[nrows];

	//auxiliary variables for 1/norm(), elements of Ar and the current rayleigh coefficient
	double factor = 0;
	double elem = 0;
	double sigma = 0.0;

	sigma = rayleigh_quotient(A, r, nrows, ncols);

	std::cout << "Rayleigh Quotient for the initial vector r" << ":" 
		<< sigma << std::endl;

	test(A, r, sigma, nrows, ncols);

	//do the iteration/algorithm k times
	for(int i=0; i < k; i++)
	{
		//calculates Ar^(k-1)
		for(int j=0; j < nrows; j++)
		{
			for(int l=0; l < ncols; l++)
			{
				elem += access(A, nrows, ncols, j, l) * r[l];
			}
			rnew[j] = elem;
			elem = 0.0;
		}

		factor = 1/norm(rnew, nrows);

		//finally builds r^(k)
		for(int j=0; j < nrows; j++)
			rnew[j] *= factor;

		sigma = rayleigh_quotient(A, rnew, nrows, ncols);

		std::cout << "Rayleigh Quotient at iteration step " << i+1 << ": " 
			<< sigma << std::endl;

		//copy value of rnew into r
		for(int j = 0; j < nrows; j++)
			r[j] = rnew[j];

		//prints the current error
		test(A, r, sigma, nrows, ncols);
	}
	
	//deallocates created pointers
	delete[] rnew;
	delete[] r;

}

int main() {
	//variables for number of cols/rows and iterations
	int ncols = 1, nrows = 1, k = 0;

	//get columns=rows of A
	std::cout << "Please enter the number of columns for 'A':" << std::endl;
	std::cin >> ncols;
	nrows = ncols;

	//allocate matrix A
	double* A = new double[ncols*ncols];

	//get values of A
	for (int i = 0; i < ncols; i++){
		for (int j = 0; j < nrows; j++) {
			std::cout << "Please enter the (" << i << "," << j << ")th entry of 'A'" << std::endl;
			std::cin >> access(A, ncols, ncols, i, j);
		}

		std::cout << std::endl;
	}

	//get number of iterations k
	std::cout << "Please enter the number of iterations: ";
	std::cin >> k;

	//start the algorithm with the acquired parameters
	power_method(A, k, nrows, ncols);
	
	//deallocate the matrix
	delete[] A;
}