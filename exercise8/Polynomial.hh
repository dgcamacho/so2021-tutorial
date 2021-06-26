#pragma once

#include <algorithm> // std::max, std::min
#include <array> // std::array
#include <cmath> // std::pow

//notes: being more consistent with use of T or value_type

namespace scprog
{
	template <typename T, int N>
	class Polynomial 
	{
	public:
		using value_type = T;

		Polynomial () : coeff_{0} {}
		
		Polynomial (std::array<value_type, N+1> const coeff) : coeff_(coeff) {}

		value_type& operator[] (int const& index);

		value_type const& operator[] (int const& index) const;

		value_type operator() (value_type const& x);

		Polynomial<value_type, N>& operator*= (value_type const& alpha);

		std::array<value_type, N+1> get();
	
	private:
		// polynomial coefficients in increasing order (start with constant, then first degree, so on)
		std::array<value_type, N+1> coeff_;
	};

	template <typename T, int N>
	Polynomial<T,N-1> derivative (Polynomial<T, N>& poly);

	template <typename T, int M, int N>
	Polynomial<T, std::max(M, N)> operator+ (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2);

	template <typename T, int M, int N>
	Polynomial<T, std::max(M, N)> operator- (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2);

	template <typename T, int M, int N>
	Polynomial<T, M+N> operator* (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2);

	template <std::size_t N>
	std::array<double, N> lagrange_basis (std::array<double, N> const& nodes, double const x);

	template <std::size_t N, class F>
	double lagrange_interpolation (F fun, std::array<double, N> const& nodes, double const x);

	#include "Polynomial.impl.hh"

} // end namespace

