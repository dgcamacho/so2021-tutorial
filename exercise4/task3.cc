#include <cassert>
#include <iostream>

#include "DenseMatrix.hh"
#include "LU.hh"
#include "Vector.hh"

int main() {
	std::size_t cols{3}, rows{3}, input{};

	std::cout << "Do you want to test the program with your own A and b? Enter 0 or 1." << std::endl;

	std::cin >> input;

	if (input == 1) {
		DenseMatrix A{rows, cols};

		std::cout << "Enter the number of cols and rows" << std::endl;

		std::cin >> cols; std::cin >> rows;

		std::cout << "Enter the entries of A" << std::endl;

		for (int i=0; i < rows; i++)
			for (int j=0; j < cols; j++)
				std::cin >> A(i,j);

		//these will be the entries of the constant Vector b
		Vector bval{rows};

		std::cout << "Enter the " << rows << " entries of b" << std::endl;

		for (int i=0; i < rows; i++)
			std::cin >> bval[i];

		Vector const b = bval;

		LU calc{rows, cols};

		//compute the LU decomposition of A
		calc.compute(A);

		Vector x{3};

		//solve the linear system
		calc.apply(b, x);

		//print the result
		std::cout << "The solution of Ax=b is given by:" << std::endl;
		for (int i=0; i < x.size(); i++) {
			std::cout << x[i];
			std::cout << std::endl;
		}

	}
	else {
		Vector const b{{1, 1, 1}};

		DenseMatrix A{rows, cols, {2, -1, 0, -1, 2, -1, 0, -1, 2}};

		LU calc{rows, cols};

		//compute the LU decomposition of A
		calc.compute(A);

		Vector x{3};

		//solve the linear system
		calc.apply(b, x);

		//print the result
		std::cout << "The solution of Ax=b is given by:" << std::endl;
		for (int i=0; i < x.size(); i++) {
			std::cout << x[i];
			std::cout << std::endl;
		}
	}
}