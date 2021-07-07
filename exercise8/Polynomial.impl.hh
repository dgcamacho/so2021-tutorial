template <typename T, std::size_t N>
T& Polynomial<T, N>::operator[] (size_type const& index) {
	return coeff_[index];
}

template <typename T, std::size_t N>
T const& Polynomial<T, N>::operator[] (size_type const& index) const {
	return coeff_[index];
}

template <typename T, std::size_t N>
T Polynomial<T, N>::operator() (value_type const& x) {
	value_type res{ coeff_[0] };
	for (size_type i{1}; i < N + 1; ++i) {
		res += coeff_[i] * std::pow(x, i);
	}
	return res;
}

template <typename T, std::size_t N>
Polynomial<T, N>& Polynomial<T, N>::operator*= (value_type const& alpha) {
	for (size_type i{0}; i < N + 1; ++i) {
		coeff_[i] *= alpha;
	}
	return *this;
}

template <typename T, std::size_t N>
Polynomial<T, N-1> derivative (Polynomial<T, N>& poly) {
	Polynomial<T, N-1> deriv{};
	for (std::size_t i{0}; i < N; ++i) {
		deriv[i] = poly[i+1] * (i + 1);
	}
	return deriv;
}

// possibly has zero entry as highest order coefficients
template <typename T, std::size_t M, std::size_t N>
Polynomial<T, std::max(M, N)> operator+ (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2) {
	Polynomial<T, std::max(M, N)> res{};
	// until degree of smaller polynomial, add both coefficients
	for (std::size_t i{0}; i <= std::min(M, N); ++i) {
		res[i] = poly1[i] + poly2[i];
	}
	// if one polynomial has higher degree, just copy it's coefficients for the higher orders
	if (M > N) {
		for (std::size_t i{N+1}; i <= M; ++i) {
			res[i] = poly1[i];
		}
	} else if (M < N) {
		for (std::size_t i{M+1}; i <= N; ++i) {
			res[i] = poly2[i];
		}
	}
	return res;
}

// possibly has zero entry as highest order coefficients
template <typename T, std::size_t M, std::size_t N>
Polynomial<T, std::max(M, N)> operator- (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2) {
	Polynomial<T, std::max(M, N)> res{};
	// until degree of smaller polynomial, subtract both coefficients
	for (std::size_t i{0}; i <= std::min(M, N); ++i) {
		res[i] = poly1[i] - poly2[i];
	}
	// if one polynomial has higher degree, just copy it's (negated) coefficients for the higher orders
	if (M > N) {
		for (std::size_t i{N+1}; i <= M; ++i) {
			res[i] = poly1[i];
		}
	} else if (M < N) {
		for (std::size_t i{M+1}; i <= N; ++i) {
			res[i] = -poly2[i];
		}
	}
	return res;
}

// no check for zero polynom, so result is possibly just many zeroes
template <typename T, std::size_t M, std::size_t N>
Polynomial<T, M + N> operator* (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2) {
	Polynomial<T, M + N> result{};
	// need variable with value zero but of type std::size_t, because otherwise there is a no-matching-function error
	// for the "std::max(0, i-N)" expression, because 0 and i-N have different types
	std::size_t zero{};
	for (std::size_t i{0}; i < M + N + 1; ++i) {
		for (std::size_t j{ std::max(zero, i-N) }; j <= std::min(i, M); ++j) {
			result[i] += poly1[j] * poly2[i-j];
		}
	}
	return result;
}

// both lagrange_basis and lagrange_interpolation don't use the Polynomial class,
// so maybe there is a better implementation
template <std::size_t N>
std::array<double, N> lagrange_basis (std::array<double, N> const& nodes, double const x) {
	std::array<double, N> res{};
	for (std::size_t i{0}; i < N; ++i) {
		res[i] = 1.0;
		// both for-loops do the same, but they skip j = i
		for (std::size_t j{0}; j < i; ++j) {
			res[i] *= (x - nodes[j]) / (nodes[i] - nodes[j]);
		}
		for (std::size_t j{i+1}; j < N; ++j) {
			res[i] *= (x - nodes[j]) / (nodes[i] - nodes[j]);
		}
	}
	return res;
}

template <std::size_t N, class F>
double lagrange_interpolation (F fun, std::array<double, N> const& nodes, double const x) {
	std::array<double, N> lagr_basis = lagrange_basis (nodes, x);
	double res{0.0};
	for (std::size_t i{0}; i < N; ++i) {
		res += lagr_basis[i] * fun( nodes[i] );
	}
	return res;
}
