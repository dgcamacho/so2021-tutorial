#include <cassert>
#include <iostream>

struct DualNumber
{
	double one;
	double eps;
};

//implementation of the operators
//I added two more to multiply with double and to compare two dual numbers (equality)
DualNumber operator+ (DualNumber const a, DualNumber const b)
{
	return DualNumber{a.one + b.one, a.eps + b.eps};
}

DualNumber operator- (DualNumber const a, DualNumber const b)
{
	return DualNumber{a.one - b.one, a.eps - b.eps};
}

DualNumber operator* (DualNumber const a, DualNumber const b)
{
	return DualNumber{a.one * b.one, a.one * b.eps + b.one * a.eps};
}

DualNumber operator* (double const a, DualNumber const b)
{
	return DualNumber{a * b.one, a * b.eps};
}

DualNumber operator/ (DualNumber const a, DualNumber const b)
{
	assert(b.one != 0);
	return DualNumber{a.one / b.one, (a.eps * b.one - a.one * b.eps) / (b.one * b.one)};
}

bool operator== (DualNumber const a, DualNumber const b)
{
	double const tol = 1.e-10;

	return (a.one - b.one < tol) && (a.eps - b.eps < tol);
}

int main()
{
	//constants for 1, epsilon and zero
	DualNumber const one{1, 0};
	DualNumber const eps{0, 1};
	DualNumber const zero{0, 0};

	//test whether the equalities hold
	//was it meant to look like this or should it be done differently?
	if ((one * eps == eps * one) && (eps * one == eps))
		std::cout << "The equation 1*\u03B5=\u03B5*1=\u03B5 holds" 
			<< std::endl;
	else
		std::cout << "The equation 1*\u03B5=\u03B5*1=\u03B5 does not hold." 
			<< std::endl;


	if ((one * (one * eps) == one * eps) && (one * eps == (one * one) * eps) && ((one * one) * eps == eps))
		std::cout << "The equation 1*(1*\u03B5)=1*\u03B5=(1*1)*\u03B5=\u03B5 holds" 
			<< std::endl;
	else
		std::cout << "The equation 1*(1*\u03B5)=1*\u03B5=(1*1)*\u03B5=\u03B5 does not hold." 
			<< std::endl;


	if ((one * (eps * eps) == one * zero) && (one * zero == zero) 
			&& (zero == eps * eps) && (eps * eps == (one * eps) * eps))
		std::cout << "The equation 1*(\u03B5*\u03B5)=1*0=0=\u03B5*\u03B5=(1*\u03B5)*\u03B5 holds" 
			<< std::endl;
	else
		std::cout << "The equation 1*(\u03B5*\u03B5)=1*0=0=\u03B5*\u03B5=(1*\u03B5)*\u03B5 does not hold." 
			<< std::endl;

	//the user is now able to compute the value
	//of the polynomial at a chosen dual number
	DualNumber x;

	std::cout << "Please enter real and imaginary part of the dual number x for which f(x)=5x^4-2x^2+7 and f'(Re(x)) should be evaluated:" 
		<< std::endl;
	std::cin >> x.one;
	std::cin >> x.eps;

	std::cout << std::endl;

	//value of the polynomial at the dual number
	DualNumber fx = 5 * x * x * x * x - 2 * x * x + 7 * one;

	std::cout << "Result: f(x) = " << fx.one << " + " << fx.eps << "\u03B5" << std::endl;

	//values of the polynomial + its first derivative at the real part
	double fa = 5 * x.one * x.one * x.one * x.one - 2 * x.one * x.one + 7 * x.one;
	double dfdx_a = 20 * x.one * x.one * x.one - 4 * x.one;

	std::cout << "f(Re(x)) = " << fa << std::endl;
	std::cout << "f'(Re(x)) = " << dfdx_a << std::endl;

	//the following will actually be true for Im(x)=1
	if (fx.eps == dfdx_a)
		std::cout << "Surprisingly, f'(Re(x)) and Im(f(x)) coincide." << std::endl;
}
