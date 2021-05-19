#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

// struct representing dual numbers a + b * eps
struct DualNumber {
	double a;
	double b;
};

using DualNumber_t = struct DualNumber;

// simple console output routine
void writeDualNumber(DualNumber_t const& x){
	std::cout << x.a << " + " << x.b << "eps" << std::endl;
}

///////////////////////////////////////////////////////////////////////////

// basic arithmetic of dual numbers - always: 
// input: two dual numbers
// output: dual number

DualNumber_t add(DualNumber_t const& x, DualNumber_t const& y){
	return {x.a + y.a, x.b + y.b};
}

DualNumber_t sub(DualNumber_t const& x, DualNumber_t const& y){
	return {x.a - y.a, x.b - y.b};
}

DualNumber_t mul(DualNumber_t const& x, DualNumber_t const& y){
	return {x.a * y.a, x.a * y.b + x.b * y.a};
}

DualNumber_t div(DualNumber_t const& x, DualNumber_t const& y){
	if (y.a != 0) {
		return {x.a / y.a, (x.b * y.a - x.a - y.b) / (y.a * y.a)};
	} else if (y.b == 0 || x.a != 0){
		std::cout << "no division possible" << std::endl;
		return {std::nan(""), std::nan("")}; // i am not sure if this is a good way 
	} else {
		// "imaginary" part is arbitrary, here: set to 0
		return {x.a / y.a, 0.0}; 
	};
}

///////////////////////////////////////////////////////////////////////////

// functions as operators
DualNumber_t operator+(DualNumber_t const& x, DualNumber_t const& y){
	return {x.a + y.a, x.b + y.b};
}

DualNumber_t operator-(DualNumber_t const& x, DualNumber_t const& y){
	return {x.a - y.a, x.b - y.b};
}

DualNumber_t operator*(DualNumber_t const& x, DualNumber_t const& y){
	return {x.a * y.a, x.a * y.b + x.b * y.a};
}

DualNumber_t operator/(DualNumber_t const& x, DualNumber_t const& y){
	if (y.a != 0) {
		return {x.a / y.a, (x.b * y.a - x.a - y.b) / (y.a * y.a)};
	} else if (y.b == 0 || x.a != 0){
		std::cout << "no division possible" << std::endl;
		return {std::nan(""), std::nan("")}; // i am not sure if this is a good way 
	} else {
		return {x.a / y.a, 0.0};
	};
}

bool operator==(DualNumber_t const& x, DualNumber_t const& y){
	return x.a == y.a && x.b == y.b;
}

///////////////////////////////////////////////////////////////////////////

// additional power function (needs * operator)
DualNumber_t pow(DualNumber_t const& x, int n){
	DualNumber_t result = x;
	for(int i = 1; i < n; ++i){
		result = result * x;
	}
	return result;
}

// evaluate polynomial f(x) = 5x^4 - 2x^2 + 7 at x
DualNumber_t f(DualNumber_t const& x){
	DualNumber_t const five {5.0, 0.0};
	DualNumber_t const two {2.0, 0.0};
	DualNumber_t const seven {7.0, 0.0};

	return five * pow(x, 4) - two * pow(x, 2) + seven;
}

// evalute polynomial's derivative f'(x) = 5*4*x^3 - 2*2*x at x
DualNumber_t f_prime(DualNumber_t const& x){
	DualNumber_t const two {2.0, 0.0};
	DualNumber_t const four {4.0, 0.0};
	DualNumber_t const five {5.0, 0.0};

	return five * four * pow(x, 3) - two * two * x;
}

///////////////////////////////////////////////////////////////////////////

int main() {
	DualNumber_t const zero {0.0, 0.0};
	DualNumber_t const one {1.0, 0.0};
	DualNumber_t const eps {0.0, 1.0};
	
	std::cout << "one = ";
	writeDualNumber(one);
	std::cout << "eps = ";
	writeDualNumber(eps);
	
	// test assertions
	// some of them follow from others but since it does not seem to waste memory/time here, I checked everything
	assert(one * eps == eps * one);
	assert(eps * one == eps);

	assert(one * (one * eps) == eps);
	assert(one * eps == eps);
	assert((one * one) * eps == eps);

	assert(one * (eps * eps) == zero);
	assert(one * zero == zero);
	assert(eps * eps == zero);
	assert((one * eps) * eps == zero);
	
	std::cout << "\nall tests passed.\n" << std::endl;

	// some examples using functions and operators
	DualNumber_t x = add(one, eps);
	std::cout << "one + eps = ";
	writeDualNumber(x);

	DualNumber_t y = one * eps;
	std::cout << "one * eps = ";
	writeDualNumber(y);

	std::cout << "\n";

	// evaluate polynomial f(x) = 5x^4 - 2x^2 + 7 at x = 3 + 1eps
	// f(x) = "Re"(x)
	DualNumber_t const my_number {3.0, 1.0};
	DualNumber_t z = f(my_number);
	std::cout << "f(3 + 1eps) = ";
	writeDualNumber(z); 

	// evaluate polynomial f'(x) = 5**4*x^3 - 4x at x = 3 + 0eps
	// f'(x) = "Im"(x)
	DualNumber_t const my_number_a {3.0, 0.0};
	std::cout << "f(3) = ";
	writeDualNumber(f(my_number_a));
	std::cout << "f'(3) = ";
	writeDualNumber(f_prime(my_number_a));
}