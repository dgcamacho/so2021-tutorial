//SCPROG summer 2021
//excercise 2 task 4 - dual numbers
//Margarete Ketelsen, 2021-05-12

#include <cassert>
#include <iostream>

//1. struct DualNumbers
struct DualNumber {
	double real, non_real;
};

//2. mathematical operators for DualNumbers

DualNumber operator+(DualNumber x, DualNumber y) {
	return DualNumber{x.real + y.real, x.non_real + y.non_real};
}

DualNumber operator*(DualNumber x, DualNumber y) {
	return DualNumber{x.real * y.real, x.real * y.non_real + x.non_real * y.real};
}

//double-DualNumber multiplication 
DualNumber operator*(double a, DualNumber x) {
	return DualNumber{a * x.real, a * x.non_real};
}

DualNumber operator-(DualNumber x, DualNumber y) {
	return DualNumber{x.real - y.real, x.non_real - y.non_real};
}

DualNumber operator/(DualNumber x, DualNumber y) {
	assert(y.real != 0);
	return DualNumber{x.real / y.real, (x.non_real * y.real - x.real * y.non_real)/(y.real * y.real)};
}

//the == operator needed in 3.
bool operator==(DualNumber x, DualNumber y) {
	return (x.real == y.real) && (x.non_real == y.non_real);
}

//Implementation of the evaluation of the polynomial given n 4.
//first if the argument is a DualNumber
DualNumber f(DualNumber x) {
	return 5.0*x*x*x*x - 2.0*x*x + DualNumber{7.0, 0.0};
}

//and if the argument is a double
double f(double x) {
	return 5.0*x*x*x*x - 2.0*x*x + 7.0;
}

//by easy differentiation rules we get the first derivative of f, 
//but we only need it for double arguments in this task
double f_prime(double x) {
	return 5.0*4.0*x*x*x - 2.0*2.0*x;
}

//output of a DualNumber
void print_DualNumber(DualNumber x) {
	std::cout << x.real << "+" << x.non_real << "*eps";
}

int main() {
	//constants
	DualNumber const one = DualNumber{1.0, 0.0}, eps = DualNumber{0.0, 1.0},
					zero = DualNumber{0.0, 0.0};

	//3. test identities
	std::cout << "The identity    1*eps = eps*1 = eps     " << 
		((one*eps == eps*one) && (eps*one == eps) ? 
			"holds." : "does not hold.") << "\n";
	std::cout << "The identity    1*(1*eps) = 1*eps = (1*1)*eps = eps     " << 
		((one*(one*eps) == one*eps) && (one*eps == (one*one)*eps) && ((one*one)*eps == eps) ? 
			"holds." : "does not hold.") << "\n";
	std::cout << "The identity    1*(eps*eps) = 1*0 = 0 = eps*eps = (1*eps)*eps     " << 
		((one*(eps*eps) == one*zero) && (one*zero == zero) && (zero == eps*eps) && (eps*eps == (one*eps)*eps) ? 
			"holds." : "does not hold.") << "\n";

	//compute polynomial expressions
	double a{3.0}, b{1.0}; 
	DualNumber x{a,b};
	std::cout << "\n\n" << "For the dual number   x=";
	print_DualNumber(x);
	std::cout << "  , we have   f(x)=";
	print_DualNumber(f(x));
	std::cout <<"\n\n";

	std::cout << "Further,   f(" << a << ")=" << f(a) << "   and   f'(" << a << ")=" << f_prime(a) << ".\n";
	
	std::cout << "\n\n\n" << "Remark:\n" << "In this case, we see   f(3+1*eps)=f(3)+f'(3)*eps  .\n" <<
		"In fact, Wikipedia says that in general   f(a+b*eps)=f(a)+b*f'(a)*eps  holds.\n";

	}