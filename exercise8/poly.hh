#include <array>

template<typename T, int n>
struct Polynomial {
	std::array<T, n+1> pol_;

	Polynomial(std::array<T, n+1>&& pol);
	T operator() (T x);
	Polynomial operator*= (T const& alpha);
};

template<typename T, int n, int m>
Polynomial<T, std::max(n,m)> operator+ (Polynomial<T, n> p, Polynomial<T, m> q);

template<typename T, int n, int m>
Polynomial<T, std::max(n,m)> operator- (Polynomial<T, n> p, Polynomial<T, m> q);

template<typename T, int n, int m>
Polynomial<T, n+m> operator* (Polynomial<T, n> p, Polynomial<T, m> q);