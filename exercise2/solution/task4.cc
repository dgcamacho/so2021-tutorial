//SCPROG summer 2021
//excercise 2 task 4 - power iteration
//Margarete Ketelsen, 2021-05-12

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>

// type aliases
using real_t = double;


//struct definitions

//Vector
struct Vector {
	std::size_t	size;
	real_t*		data;
};

//Matrix
struct Matrix {
	std::size_t	nrows, ncols;
	real_t*		data;
};

//Linear Algebra operations

//Matrix-multiplication
void mat_mat(Matrix const& A, Matrix const& B, Matrix& C)
{
	assert(A.ncols == B.nrows && A.nrows == C.nrows && B.ncols == C.ncols);

	const size_t N = A.nrows;
	const size_t M = B.ncols;

	for (size_t i = 0; i < N; ++i)
	{
		for (size_t j = 0; j < M; ++j)
		{
			C.data[i*M+j] = 0;
			for (size_t k = 0; k < A.ncols; ++k)
			{
				C.data[i*M+j] += A.data[i*A.ncols+k] * B.data[k*M+j];
			}
		}
	}
}

//Scalar-Vector-multiplication
void sca_vec(real_t const& a, Vector const& x, Vector& y)
{
	assert(y.size == x.size);

	const size_t N = x.size;

	for (size_t i = 0; i < N; ++i)
	{
		y.data[i] = a * x.data[i];
	}
}

//Matrix-Vector-multiplication
void mat_vec(Matrix const& A, Vector const& x, Vector& y)
{
	assert(A.ncols == x.size && A.nrows == y.size);

	const size_t N = A.nrows;
	const size_t M = A.ncols;

	for (size_t i = 0; i < N; ++i)
	{
		y.data[i] = 0;
		for (size_t k = 0; k < M; ++k)
		{
			y.data[i] += A.data[i*M+k] * x.data[k];
		}
	}
}

//dot-product
real_t dot(Vector const& x, Vector const& y)
{
	assert(x.size == y.size);

	const size_t N = x.size;
	real_t res = 0;

	for (size_t i = 0; i < N; ++i)
	{
		res += x.data[i] * y.data[i];
	}

	return res;
}

//Vector-norm
real_t norm(Vector const& x)
{
	return std::sqrt(dot(x,x));
}

//Distance between two vectors ||x-y|| in euclidean norm
real_t distance(Vector const& x, Vector const& y)
{
	assert(x.size == y.size);

	Vector z{x.size, new real_t[x.size]};

	for (size_t i = 0; i < x.size; ++i)
	{
		z.data[i] = x.data[i] - y.data[i];
	}
	real_t dist = norm(z);

	delete(z.data);

	return dist;
}


//in and out of Matrix and Vector

//output Vector
void writeVector(Vector const& x)
{
	size_t N = x.size;

	for (size_t i = 0; i < N; ++i)
	{
		std::cout << "\n" << x.data[i];
	}
	std::cout << "\n\n";
}

//output Matrix
void writeMatrix(Matrix const& A)
{
	size_t N = A.nrows;
	size_t M = A.ncols;

	for (size_t i = 0; i < N; ++i)
	{
		std::cout << "\n";
		for (size_t j = 0; j < M; ++j)
		{
			std::cout << ((A.data)[i*M+j]) << "\t";
		}
	}
	std::cout << "\n\n";
}

//input Vector
void readVector(Vector& x)
{
	size_t N = x.size;
	bool corr = 0;

	do{
		std::cout << "type in " << N << " numbers:\n";
		for (size_t i = 0; i < N; ++i)
		{
			std::cin >> x.data[i];
		}
		std::cout << "You entered this Vector:\n";
		writeVector(x);
		std::cout << "Type in '1' if this is correct or '0' if not ";
		std::cin >> corr;
	}while(not corr);
}

//input Matrix
void readMatrix(Matrix& A)
{
	size_t N = A.nrows, M = A.ncols;
	bool corr=0;

	std::cout << "Contents of the matrix:\n";
	do{
		for (size_t i = 0; i < N; ++i)
		{
			std::cout << "row " << i << " of " << N << "\ntype in " << M << " numbers:\n";
			for (size_t j = 0; j < M; ++j)
			{
				std::cin >> ((A.data)[i*M+j]);
			}
		}
		std::cout << "You entered this Matrix:\n";
		writeMatrix(A);
		std::cout << "Type in '1' if the Matrix is correct and '0' if not ";
		std::cin >> corr;
	}while(not corr);
}




//The excercises

// a) Rayleigh quotient
real_t rayleigh_quotient(Matrix const& A, Vector const& r)
{
	assert(A.ncols == r.size);

	Vector Ar{A.nrows, new real_t[A.nrows]};

	mat_vec(A, r, Ar);
	real_t rayleigh = dot(r, Ar)/dot(r, r);

	delete(Ar.data);

	return rayleigh;
}

// b) Find initial value r0 for given A such that A*r0 != 0
void find_initial_value(Matrix const& A, Vector& r0)
{
	assert(A.ncols == r0.size);

	size_t N = A.nrows;
	size_t M = A.ncols;
	Vector Ar0{N, new real_t[N]};
	bool not_in_kernel=0;
	
	do{
		std::srand(std::time(nullptr));
		for (size_t i = 0; i < M; ++i)
		{
			r0.data[i] = std::rand()/(RAND_MAX/20.0)-10.0;
		}
		mat_vec(A, r0, Ar0);
		not_in_kernel = norm(Ar0);
	}while(not not_in_kernel);
	
	delete(Ar0.data);
}

// c) Cool Power Iteration Power :-)
void power_method(Matrix const& A, size_t k, Vector& r)
{
	assert(A.nrows == A.ncols && r.size == A.nrows);
	
	find_initial_value(A, r);
	
	Vector Ar{A.nrows, new real_t[A.nrows]};
	
	for (size_t i = 0; i < k; ++i)
	{
		std::cout << "\nThe Rayleigh quotient in step " << i << " is: " << rayleigh_quotient(A,r) << "\n";
		mat_vec(A, r, Ar);
		sca_vec(1/norm(Ar), Ar, r);
	}
	
	delete(Ar.data);
}

real_t test(Matrix const& A, Vector const& r, real_t sigma)
{
	assert(A.nrows == A.ncols && A.nrows == r.size);
	
	Vector Ar{r.size, new real_t[r.size]}, sigmar{r.size, new real_t[r.size]};
	real_t err;
	
	mat_vec(A, r, Ar);
	sca_vec(sigma, r, sigmar);
	err = distance(Ar, sigmar);
	
	delete(Ar.data);
	delete(sigmar.data);
	
	std::cout << "\nThe approximation error (euclidean norm) is " << err << "\n";
	
	return err;
}

int main()
{
	//k, B and C definition
	real_t Bdata[9] = {3.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0}, Cdata[9] = {4.0, -1.0, -1.0, 0.5, 2.0, -1.0, 0.0, 0.0, 1.0};
	Matrix B{3, 3, Bdata}, C{3, 3, Cdata};
	size_t k = 20;

	Vector rB{3, new real_t[3]}, rC{3, new real_t[3]};

	power_method(B, k, rB);
	std::cout << "\n\nMatrix B: ";
	writeMatrix(B);
	std::cout << "with eigen vector: ";
	writeVector(rB);
	test(B, rB, rayleigh_quotient(B, rB));

	power_method(C, k, rC);
	std::cout << "\n\nMatrix C: ";
	writeMatrix(C);
	std::cout << "with eigen vector: ";
	writeVector(rC);
	test(C, rC, rayleigh_quotient(C, rC));

	return 0;
}