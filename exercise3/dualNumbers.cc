#include <cassert>
#include <cmath>
#include <string>
#include <iostream>

struct DualNumber {
	double a,b;
};

DualNumber add(DualNumber x, DualNumber y)
{
	return {x.a+y.a, y.b+y.b};
}

DualNumber sub(DualNumber x, DualNumber y)
{
	return {x.a-y.a, x.b-y.b};
}

DualNumber mul(DualNumber x, DualNumber y)
{
	return {x.a*y.a, x.a*y.b + x.b*y.a};
}

DualNumber div(DualNumber x, DualNumber y)
{
	return {x.a / y.a, (x.b*y.a - x.a*y.b)/((y.a)*(y.a))};
}

bool equalsDouble(double x, double y, double epsilon)
{
	return (std::abs(x-y) < epsilon);
}

bool equals(DualNumber x, DualNumber y)
{
	return (equalsDouble(x.a,y.a, 1e-14) && equalsDouble(x.b,y.b, 1e-14));
}

void print(DualNumber x, std::string message)
{
	std::cout << message << "\n" << x.a << "," << x.b << std::endl;
}

DualNumber f(DualNumber x)
{
	DualNumber five{5,0};
	DualNumber two{2,0};
	DualNumber seven{7,0};
	return add(sub(mul(five, mul(x,mul(x,mul(x,x)))), mul(two,mul(x,x))),seven);
}

DualNumber fPrime(DualNumber x)
{
	// f'(x)=20x^3-4x
	DualNumber four{4,0};
	DualNumber twenty{20,0};
	return sub(mul(twenty,mul(x,mul(x,x))),mul(four,x));
}

int main()
{
	DualNumber one{1,0};
	DualNumber zero{0,0};
	DualNumber eps{0,1};
	
	// test equals
	assert(equals(one,one));
	assert(! equals(one,eps));
	
	// required tests	
	assert(equals(mul(one,eps),mul(eps,one)));
	assert(equals(mul(one,eps),eps));
	assert(equals(eps,mul(eps,one)));
	
	assert(equals(mul(one,mul(one,eps)),mul(one,eps)));
	assert(equals(mul(one,eps),mul(mul(one,one),eps)));
	assert(equals(mul(mul(one,one),eps),eps));
	
	assert(equals(mul(one,mul(one,eps)),mul(mul(one,one),eps)));
	assert(equals(mul(one,mul(one,eps)), eps));
	
	assert(equals(mul(one,mul(eps,eps)), mul(one,zero)));
	assert(equals(mul(one,zero),zero));
	assert(equals(zero, mul(eps,eps)));
	assert(equals(mul(eps,eps),mul(mul(one,eps),eps)));
	
	assert(equals(mul(one,mul(eps,eps)), zero));
	assert(equals(mul(one,mul(eps,eps)), mul(eps,eps)));
		
	DualNumber x{3,1};
	print(f(x),"f(x)=");
	print(fPrime(x),"f'(x)=");
	
}

/*
 * liefert bei Ausführung folgendes Resultat:
 * f(x)=394,0
 * f'(x)=528,536
 */ 

