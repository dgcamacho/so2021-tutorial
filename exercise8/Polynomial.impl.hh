template <typename T, int N>
T& Polynomial<T, N>::operator[] (int const& index) {
	return coeff_[index];
}

template <typename T, int N>
T const& Polynomial<T, N>::operator[] (int const& index) const {
	return coeff_[index];
}

template <typename T, int N>
T Polynomial<T, N>::operator() (value_type const& x) {
	value_type res{ coeff_[0] };
	for (int i{1}; i < N+1; ++i) {
		res += coeff_[i] * std::pow(x, i);
	}
	return res;
}

template <typename T, int N>
Polynomial<T, N>& Polynomial<T, N>::operator*= (value_type const& alpha) {
	for (int i{0}; i < N+1; ++i) {
		coeff_[i] *= alpha;
	}
	return *this;
}

template <typename T, int N>
Polynomial<T, N-1> derivative (Polynomial<T, N>& poly) {
	Polynomial<T, N-1> deriv{};
	for (int i{0}; i < N; ++i) {
		deriv[i] = poly[i+1] * (i + 1);
	}
	return deriv;
}

// possibly has zero entry as highest order coefficients
template <typename T, int M, int N>
Polynomial<T, std::max(M, N)> operator+ (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2) {
	Polynomial<T, std::max(M, N)> res{};
	// until degree of smaller polynomial, add both coefficients
	for (int i{0}; i <= std::min(M, N); ++i) {
		res[i] = poly1[i] + poly2[i];
	}
	// if one polynomial has higher degree, just copy it's coefficients for the higher orders
	if (M > N) {
		for (int i{N+1}; i <= M; ++i) {
			res[i] = poly1[i];
		}
	} else if (M < N) {
		for (int i{M+1}; i <= N; ++i) {
			res[i] = poly2[i];
		}
	}
	return res;
}

// possibly has zero entry as highest order coefficients
template <typename T, int M, int N>
Polynomial<T, std::max(M, N)> operator- (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2) {
	Polynomial<T, std::max(M, N)> res{};
	// until degree of smaller polynomial, subtract both coefficients
	for (int i{0}; i <= std::min(M, N); ++i) {
		res[i] = poly1[i] - poly2[i];
	}
	// if one polynomial has higher degree, just copy it's (negated) coefficients for the higher orders
	if (M > N) {
		for (int i{N+1}; i <= M; ++i) {
			res[i] = poly1[i];
		}
	} else if (M < N) {
		for (int i{M+1}; i <= N; ++i) {
			res[i] = -poly2[i];
		}
	}
	return res;
}

// no check for zero polynom, so result is possibly just many zeroes
template <typename T, int M, int N>
Polynomial<T, M+N> operator* (Polynomial<T, M>& poly1, Polynomial<T, N>& poly2) {
	Polynomial<T, M+N> result{};
	for (int i{0}; i < M+N+1; ++i) {
		for (int j{ std::max(0, i-N) }; j <= std::min(i, M); ++j) {
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
