#include <array>
#include <cassert>
#include <iostream>

#include "Polynomial.hh"

struct Square 
{
	double operator() (double const x) {
		return x * x;
	} 
};

struct Third_Degree_Poly 
{
	double operator() (double const x) {
		return x * x * x - 2 * x * x + 3 * x + 1;
	} 
};

int main () {
	/*
	// some output to check whether the Polynomial functions work, can be uncommented
	std::array<int, 3> a{1, 2, 3};
	scprog::Polynomial<int, 2> poly{a};
	std::cout << "Polynom p: " << poly[0] << " " << poly[1] << " " << poly[2] << std::endl;
	std::cout << "p(2): " << poly(2) << std::endl;
	
	scprog::Polynomial<int, 2> poly2{a};
	poly2 *= 2;
	std::cout << "Polynom 2*p: " << poly2[0] << " " << poly2[1] << " " << poly2[2] << std::endl;
	std::cout << "2*p(2): " << poly2(2) << std::endl;
	
	scprog::Polynomial<int, 1> poly_deriv = scprog::derivative(poly);
	std::cout << "p': " << poly_deriv[0] << " " << poly_deriv[1] << std::endl;

	scprog::Polynomial<int, 2> sum = poly + poly_deriv;
	std::cout << "p + p': " << sum[0] << " " << sum[1] << " " << sum[2] << std::endl;

	scprog::Polynomial<int, 2> diff = poly - poly_deriv;
	std::cout << "p - p': " << diff[0] << " " << diff[1] << " " << diff[2] << std::endl;

	scprog::Polynomial<int, 3> prod = poly * poly_deriv;
	std::cout << "p * p': " << prod[0] << " " << prod[1] << " " << prod[2] << " " << prod[3] << std::endl;
	*/

	// Grid of 3 nodes should be able to approximate polynomials of degree 2, but not degree 3:
	std::array<double, 3> const nodes{0.0, 0.5, 1.0};
	//"0.2^2 approximated should be exactly 0.04 
	assert ( std::abs (scprog::lagrange_interpolation (Square{}, nodes, 0.2) - 0.04) < 10 * std::numeric_limits<double>::epsilon() );
	// 0.2^3 - 2*0.2^2 + 3*0.2 + 1 approximated should be 1.48
	// I compare with 10*eps instead of eps, because the errors seems to be around 2*eps but that's good enough for me
	assert ( std::abs (scprog::lagrange_interpolation (Third_Degree_Poly{}, nodes, 0.2) - 1.48) < 10 * std::numeric_limits<double>::epsilon() );
}
