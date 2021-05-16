#include <cassert>
#include <cmath>
#include <string>
#include <iostream>

struct DualNumber {
	double a,b;
	
	DualNumber operator+(DualNumber that) const
	{
		return {this->a + that.a, this->b + that.b}; 
	}
	
	DualNumber operator-(DualNumber that) const
	{
		return {this->a-that.a, this->b-that.b};		
	}
	
	DualNumber operator*(DualNumber that) const
	{
		return {this->a*that.a, this->a*that.b + this->b*that.a};		
	}
	
	DualNumber operator/(DualNumber that) const
	{
		return {this->a / that.a, 
			(this->b*that.a - this->a*that.b)/((that.a)*(that.a))};
	}
};

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
	return five*x*x*x*x-two*x*x+seven;
}

DualNumber fPrime(DualNumber x)
{
	// f'(x)=20x^3-4x
	DualNumber four{4,0};
	DualNumber twenty{20,0};
	return twenty*x*x*x-four*x;
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
	assert(equals(one*eps,eps*one));
	assert(equals(one*eps,eps));
	assert(equals(eps,eps*one));
	
	assert(equals(one*(one*eps),one*eps));
	assert(equals(one*eps,(one*one)*eps));
	assert(equals((one*one)*eps,eps));
	
	assert(equals(one*(one*eps),(one*one)*eps));
	assert(equals(one*(one*eps), eps));
	
	assert(equals(one*(eps*eps), one*zero));
	assert(equals(one*zero,zero));
	assert(equals(zero, eps*eps));
	assert(equals(eps*eps,(one*eps)*eps));
	
	assert(equals(one*(eps*eps), zero));
	assert(equals(one*(eps*eps), eps*eps));
		
	DualNumber x{3,1};
	print(f(x),"f(x)=");
	print(fPrime(x),"f'(x)=");
	
}

/*
 * liefert bei Ausführung folgendes Resultat:
 * f(x)=394,528
 * f'(x)=528,536
 */ 
