#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <string>

double dot(std::vector<double> x, std::vector<double> y) 
{
	assert(x.size() == y.size());
	double d = 0.0;
	for (int i=0; i < x.size(); i++) {
		d += x[i]*y[i];
	}
	return d;
}

double two_norm(std::vector<double> x) 
{
	return std::sqrt(dot(x,x));
}

// multiplication of constant alpha with vector r
std::vector<double> mulAlphar(double alpha, std::vector<double> r)
{
	int n=r.size();
	std::vector<double> result = std::vector<double>(n,0.0);
	for (int i=0; i<n; ++i) 
	{
		result[i]=alpha*r[i];
	}
	return result;
}

// multiplication of matrix A (dimension nxn) 
// with vector r of size n (delivers vector of size n)
std::vector<double> mulAr(std::vector<double> A, std::vector<double> r)
{
	int n=r.size();
	std::vector<double> result = std::vector<double>(n,0.0);
	for (int i=0; i<n; ++i) 
	{
		double d=0.0;
		for (int j=0; j<n; ++j)
		{
			d += A[i*n+j]*r[j];
		}
		result[i]=d;
	}
	return result;
}

std::vector<double> sub(std::vector<double> r, std::vector<double> s)
{
	assert(r.size() == s.size());
	int n=r.size();
	std::vector<double> result(n,0.0);
	for (int i=0; i<n; i++)
	{
		result[i]=r[i]-s[i];
	}		
	return result;
}

bool equals(double x, double y, double eps)
{
	return std::abs(x-y) <= eps;
}

// checks whether vector r is equal to the vector containing zeros
bool isZero(std::vector<double> r) 
{
	for (int i=0; i< r.size(); i++) 
	{
		if (! equals(r[i],0.0,1e-10)) return false;
	}
	return true;
}

void printVector(std::vector<double> r, std::string message) 
{
	std::cout << message << std::endl;
	for(int i=0; i<r.size(); i++) 
	{
		std::cout << r[i] << std::endl;		
	}	
}


double rayleigh_quotient(std::vector<double> A,std::vector<double> r)
{
	return dot(r, mulAr(A,r)) / dot(r,r);
}

std::vector<double> find_initial_value(std::vector<double> A)
{
	int n= std::sqrt(A.size()); // A has size n*n
	std::srand(1);
	std::vector<double> r(n, 0.0);
	do 
	{
		for (int i=0; i<n; i++)
		{
			r[i]=std::rand();
		}
	} while (isZero(mulAr(A,r))); //r0 must not lay in the kernel of A
	return r;
}

std::vector<double> power_method(std::vector<double> A, int k)
{
	std::vector<double> r = find_initial_value(A);
	for (int i=1; i<=k-1; i++) 
	{
		std::vector<double> temp = mulAr(A,r);
		r = mulAlphar(1/two_norm(temp),temp); // delivers r^(i)
		std::cout << "eigenvalue for i=" << i << "\n" 
		          << rayleigh_quotient(A,r) << std::endl;
	}
	return r; // returns final approximation r^(k)
}

void test(std::vector<double> A, std::vector<double> r, double sigma)
{
	std::vector<double> error = sub(mulAr(A,r), mulAlphar(sigma,r));
	printVector(error, "Computed error:");
}

// function to test essential functions of the program
void test()
{
	std::vector<double> A{
		1.0, 2.0, 3.0, 
		4.0, 5.0, 6.0, 
		7.0, 8.0, 9.0};
	printVector(A, "Vector A");
	std::vector<double> r{1.0, 2.0, 0.0};
	
	// test multiplication of matrix A with vector r
	std::vector<double> result = mulAr(A,r);
	printVector(result, "Mult A * r");
	 
	// test dot product
	std::vector<double> a{1.0,4.0,5.0};
	std::cout << dot(a,r) << std::endl;
	
	// test subtraction of vectors
	result = sub(a,r);
	printVector(result, "Subtraction test:");
	
	// test multiplication of scalar and vector
	result = mulAlphar(2,a);
	printVector(result, "Mult alpha*vector test:");
	
	// test isZero
	std::vector<double> zero(3,1.0);
	std::cout << "is Zero: " << isZero(zero) << std::endl;
	
	// test find_initial_Value(A)
	result = find_initial_value(A);
	printVector(result, "find initial Value test");
	
	// test rayleigh-quotient with A and r
	double quotient = rayleigh_quotient(A,r);
	std::cout << "R-Quotient test: " << quotient << std::endl;
	
}

int main() 
{
	int k=21; // number of iterations
	std::vector<double> B{
		3.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0};   // matrix B
	std::vector<double> C{
		4.0, -1.0, -1.0,
		0.5, 2.0, -1.0,
		0.0, 0.0, 1.0};   // matrix C
	
	std::cout << "Results for B" << std::endl;
	std::vector<double> r = power_method(B,k);
	test(B,r,rayleigh_quotient(B,r));

	std::cout << "Results for C" << std::endl;
	r = power_method(C,k);
	test(C,r,rayleigh_quotient(C,r));	
	
}
