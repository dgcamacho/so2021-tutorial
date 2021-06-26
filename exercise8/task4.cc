#include <array>
#include <iostream>

#include "Polynomial.hh"

struct Square 
{
	double operator() (double const x) {
		return x * x;
	} 
};

int main () {
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

	std::array<double, 3> nodes{0.0, 0.5, 1.0};
	std::cout << "0.6^2 approximated: " << scprog::lagrange_interpolation (Square{}, nodes, 0.6) << std::endl;
}
