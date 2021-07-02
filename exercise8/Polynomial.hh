#pragma once

#include <algorithm> // std::max, std::min
#include <array> // std::array
#include <cmath> // std::pow

// notes: being more consistent with use of T or value_type
// possibly introduce size_type

namespace scprog
{
	template <typename T, int N>
	class Polynomial 
	{
	public:
		using value_type = T;

		Polynomial () : coeff_{0} {}
		
		Polynomial (std::array<value_type, N+1> const coeff) : coeff_(coeff) {}

		// mutable access to coefficient of order index
		value_type& operator[] (int const& index);

		// non-mutable access to coefficient of order index
		value_type const& operator[] (int const& index) const;

		// evaluate polynomial at x
		value_type operator() (value_type const& x);

		// scale polynomial by scalar alpha
		Polynomial<value_type, N>& operator*= (value_type const& alpha);
	
	private:
		// polynomial coefficients in increasing order (start with constant, then first degree, second degree, so on)
		std::array<value_type, N+1> coeff_;
	};

	// derivative of polynomial
	template <typename T, int N>
	Polynomial<T, N-1> derivative (Polynomial<T, N>& poly);

	// adds two polynomials of any degree
	template <typename T, int M, int N>
	Polynomial<T, std::max(M, N)> operator+ (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2);

	// subtracts two polynomials of any degree
	template <typename T, int M, int N>
	Polynomial<T, std::max(M, N)> operator- (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2);

	// multiplies two polynomials of any degree
	template <typename T, int M, int N>
	Polynomial<T, M+N> operator* (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2);

	// computes and evaluates Lagrange basis polynomials over the grid nodes at position x,
	// returns the evaluated polynomials as std::array
	template <std::size_t N>
	std::array<double, N> lagrange_basis (std::array<double, N> const& nodes, double const x);

	// computes and evaluates the Lagrange interpolation for function f over the grid nodes at position x
	template <std::size_t N, class F>
	double lagrange_interpolation (F fun, std::array<double, N> const& nodes, double const x);

	#include "Polynomial.impl.hh"

} // end namespace

