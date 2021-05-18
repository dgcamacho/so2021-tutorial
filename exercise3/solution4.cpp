#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <cassert>
#include <limits>

template <typename T>
struct DualNumber {
	T r; //real part
	T c; //"complex" part
	
	DualNumber() : r(0), c(0) {}
	DualNumber(T real) : r(real), c(0) {}
	DualNumber(T real, T complex) : r(real), c(complex) {}
	DualNumber(DualNumber const& other) : r(other.r), c(other.c) {}
	
	friend
	DualNumber operator+(DualNumber num, T const other) {
		return num += other;
	}
	friend
	DualNumber operator+(DualNumber tmp, DualNumber const& other) {
		return tmp += other;
	}
	
	friend
	DualNumber operator*(DualNumber num, T const other){
		return num *= other;
	}
	friend
	DualNumber operator*(DualNumber tmp, DualNumber const& other) {
		return tmp *= other;
	}
	
	friend
	DualNumber operator-(DualNumber num, T const other) {
		return num -= other;
	}
	friend
	DualNumber operator-(DualNumber tmp, DualNumber const& other) {
		return tmp -= other;
	}
	
	friend
	DualNumber operator/(DualNumber num, T const other) {
		return num /= other;
	}
	friend
	DualNumber operator/(DualNumber const tmp, DualNumber const& other) {
		return tmp /= other;
	}
	
	DualNumber& operator=(DualNumber const& other) {
		this->r = other.r;
		this->c = other.c;
		
		return *this;
	}
	
	DualNumber& operator+=(T const other) {
		this->r += other;
		
		return *this;
	}
	DualNumber& operator+=(DualNumber const& other) {
		this->r += other.r;
		this->c += other.c;
		
		return *this;
	}
	
	DualNumber& operator-=(T const other) {
		this->r -= other;
		
		return *this;
	}
	DualNumber& operator-=(DualNumber const& other) {
		this->r -= other.r;
		this->c -= other.c;
		
		return *this;
	}
	
	DualNumber& operator*=(T const other) {
		this->r += other;
		
		return *this;
	}
	DualNumber& operator*=(DualNumber const& other) {
		this->c = this->r * other.c + other.r * this->c;
		this->r *= other.r;
		
		return *this;
	}
	
	DualNumber& operator/=(T const other) {
		assert( other != 0 );
		
		this->r /= other;
		this->c /= other;
		
		return *this;
	}
	DualNumber& operator/=(DualNumber const& other) {
		assert( other.r != 0 );
		
		this->c = (this->c * other.r - this->r * other.c) / (other.r * other.r);
		this->r /= other.c;
		
		return *this;
	}
	
	bool operator==(DualNumber const& other) const {
		return std::abs(this->r - other.r) < std::numeric_limits<T>::epsilon() && std::abs(this->c - other.c) < std::numeric_limits<T>::epsilon();
	}
	
	friend
	std::ostream& operator<<(std::ostream& out, DualNumber const& other) {
		out << other.r << " " << (other.c >= 0 ? "+" : "-") << " " << (other.c >= 0 ? other.c : -other.c) << "*eps";
		return out;
	}
	
	DualNumber pow(unsigned int const n) const {
		auto tmp{*this};
		for( auto i = n; i > 1; i-- ) {
			tmp*= *this;
		}
		
		return tmp;
	}


};

template <typename T>
DualNumber<T> add(DualNumber<T> const& a, DualNumber<T> const& b) {
	return a + b;
}
template <typename T>
DualNumber<T> sub(DualNumber<T> const& a, DualNumber<T> const& b) {
	return a - b;
}
template <typename T>
DualNumber<T> mul(DualNumber<T> const& a, DualNumber<T> const& b) {
	return a * b;
}
template <typename T>
DualNumber<T> div(DualNumber<T> const& a, DualNumber<T> const& b) {
	return a / b;
}

template <typename T>
constexpr
DualNumber<T> f(DualNumber<T> const x) {
	return 5 * x.pow(4) - 2 * x.pow(2) + 7;
}
template <typename T>
constexpr
DualNumber<T> fPrime(DualNumber<T> const x) {
	return 5 * 4 * x.pow(3) - 2 * 2 * x;
}

int main() {
	DualNumber<double> const one(1);
	DualNumber<double> const eps(0,1);
	DualNumber<double> const zero;
	
	std::cout 	<< "Testing" << std::endl
				<< '\t' << "1*eps = eps * 1 = eps: " << ((one * eps == eps * one) && (eps * one== eps)) << std::endl
				<< '\t' << "1*(1*eps) = 1*eps = (1*1)*eps = eps: " << (one * (one * eps) == one * eps && one * eps == (one * one) * eps && one * eps == eps) << std::endl
				<< '\t' << "1 * (eps * eps) = 1 * 0 = 0 = eps * eps = (1 * eps) * eps: " << (one * (eps * eps) == one * zero && one * zero == zero * zero && zero == eps * eps && zero == (one * eps) * eps) << std::endl
				<< std::endl;

	std::cout 	<< "a = 3, b = 1" << std::endl
				<< "f(a + eps*b) = " << f(DualNumber<unsigned int>(3,1)) << std::endl
				<< "f(a) = " << f(DualNumber<unsigned int>(3)) << std::endl
				<< "f'(a) = " << fPrime(DualNumber<unsigned int>(3)) << std::endl;
				
	return EXIT_SUCCESS;
}
