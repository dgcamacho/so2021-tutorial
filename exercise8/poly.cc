#include "poly.hh"
#include <iostream>

template<typename T, int N>
T dot_product(std::array<T, N> a, std::array<T, N> b) {
	double res{};

	for (int i=0; i < N; i++)
		res += a[i] * b[i];

	return res;
}

template<typename T>
T power(int n, T x) {
	T res{1};

	for (int i=1; i <= n; i++) {
		res *= x;
	}

	return res;
}

template<typename T, int n>
Polynomial<T, n-1> derivative(Polynomial<T, n> pol){
	//initialise a polynomial of degree n-1
	std::array<T, n> zero{};
	Polynomial<T, n-1> res{std::move(zero)};

	//differentiate
	for(int i=0; i <= n-1; i++)
		res.pol_[i] = pol.pol_[i+1] * (i+1);

	return res;
}

template<int N>
std::array<double, N> lagrangeBasis(std::array<double, N> nodes, double x) {
	//initialise result array
	std::array<double, N> res{};

	//computation using barycentric form (cf. Wikipedia)
	for (int j=0; j < N; j++) {
		//create the constant polynomial 1
		std::array<double, N+1> one{};
		one[0] = 1;
		Polynomial<double, N> l{std::move(one)}; 

		//computes (x-x_0)*...*(x-x_n)/(x-x_j)
		for(int i=0; i < N; i++) {
			if (i != j) {
				//multiply the linear polynomials with the current product,
				//so we always get a polynomial of degree N+1
				//(if we wouldn't know this at compile time,
				// we could not create an array/polynomial)
				Polynomial<double, 1> lin{{-nodes[i], 1}};
				Polynomial<double, N+1> hilf{(l*lin).pol_};

				//As we know that we get a polynomial of degree at most n, we shift back into l
				//then we will again get a polynomial of degree n+1 in the multiplication above
				std::copy(hilf.pol_.begin(), hilf.pol_.end() - 1, l.pol_.begin());
			}
		}

		//implement the rest of the formula for l_j cf. Wikipedia
		Polynomial<double, 1> lin{{-nodes[j], 1}};
		l *= (1.0f / derivative(l*lin)(x));

		//save l_j(x) to the result vector
		res[j] = l(x);
	}

	return res;
}

template<typename T, int n>
Polynomial<T,n>::Polynomial(std::array<T, n+1>&& pol) {
	//steal the data of the given polynomial
	swap(this->pol_, pol);
}

template<typename T, int n>
T Polynomial<T,n>::operator() (T x) {
	T res{};

	for (int i=0; i <= n; i++)
		res += pol_[i] * power(i,x);

	return res;
}

template<typename T, int n>
Polynomial<T,n> Polynomial<T,n>::operator*= (T const& alpha) {
	for (int i=0; i <= n; i++)
		pol_[i] *= alpha;

	return *this;
}

template<typename T, int n, int m>
Polynomial<T, std::max(n,m)> operator+ (Polynomial<T, n> p, Polynomial<T, m> q) {
	//initialise result polynomial
	std::array<T, std::max(n,m)+1> zero{};
	Polynomial<T, std::max(n,m)> res{std::move(zero)};

	for (int i=0; i <= n; i++)
		res.pol_[i] = p.pol_[i] + q.pol_[i];

	return res;
}

template<typename T, int n, int m>
Polynomial<T, std::max(n,m)> operator- (Polynomial<T, n> p, Polynomial<T, m> q) {
	std::array<T, std::max(n,m)+1> zero{};
	Polynomial<T, std::max(n,m)> res{std::move(zero)};

	for (int i=0; i <= n; i++)
		res.pol_[i] = p.pol_[i] - q.pol_[i];

	return res;
}

template<typename T, int n, int m>
Polynomial<T, n+m> operator* (Polynomial<T, n> p, Polynomial<T, m> q) {
	std::array<T, n+m+1> zero{};
	Polynomial<T, n+m> res{std::move(zero)};
	Polynomial<T, n+m> p_add{std::move(zero)};
	Polynomial<T, n+m> q_add{std::move(zero)};

	//transform p and q to polynomials of the same degree
	//=> don't have to deal with zeros when out of bound
	p_add = p + res;
	q_add = q + res;

	for (int i=0; i <= m+n; i++)
		for (int j=0; j<=i; j++)
			res.pol_[i] += p_add.pol_[j]*q_add.pol_[i-j];

	return res;
}