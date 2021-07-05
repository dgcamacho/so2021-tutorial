#include "poly.cc"
#include <iostream>
#include <math.h>

int main() {
	int const n = 3; //number of nodes for approximation
	double const eps = 1e-9; //tolerance
	std::array<double, n> arr = {1, 2, 3}, //arrays for nodes
		y{}; //and the function values at these x-values

	auto f = [] (double x) { //lambda expression to implement the exact function (here a polynomial)
		Polynomial<double, n-1> p{{5, 6, 7}};
		return p(x);
		//return std::sin(x);
	};

	for (int i=0; i < n; i++) {
		y[i] = f(arr[i]);
	}

	//lambda expression for convenience
	auto lagrange = [arr, n] (double x) {return lagrangeBasis<n>(arr, x);};

	for (int i=0; i < n; i++) {
		//compare exact function values with those of the lagrange interpolation
		double diff = dot_product<double, n>(y, lagrange(arr[i])) - f(arr[i]);

		if (std::abs(diff) < eps)
			std::cout << "The approximation at x=" << arr[i] << " is nearly exact!" << std::endl;
		else
			std::cout << "Error at x=" << arr[i] << ": " << diff << std::endl;
	}
}