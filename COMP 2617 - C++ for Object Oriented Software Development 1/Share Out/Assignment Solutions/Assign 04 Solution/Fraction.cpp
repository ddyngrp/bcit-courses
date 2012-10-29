// Assignment 5 Solution: Fraction.cpp
// Member-function definitions for class Fraction.
// Author: Bob Langelaan 
// Date: Feb. 18th, 2006

#include "Fraction.h"
#include "GCD.h" // template function for calculating greatest common divisor

#include <iostream>
using std::cout;

//default ctor
Fraction::Fraction (void)
{
	numerator = 0;
	denominator = 1;
}

//ctor - requires 2 paramaters
Fraction::Fraction ( long long num, long long denom )
{
	numerator = num;
	denominator =  denom;
	simplify();
}

// Implementation of plusEq() member function
// This implementation is more sophisticated than I am 
//      expecting from my students
//Performs similar operation as the -= operator on the built-in types
Fraction & Fraction::plusEq (Fraction & op )
{
	if (denominator != op.denominator )
	{
		long long common_divisor = gcd(denominator,op.denominator);
		numerator *= (op.denominator / common_divisor);
		numerator += op.numerator * (denominator / common_divisor);
		denominator *= (op.denominator / common_divisor);
	}
	else 
	{
		numerator += op.numerator;
	}

	simplify();

	return (*this);
}

// Implementation of the minusEq() member function
// This implementation is more sophisticated than I am 
//      expecting from my students
//Performs similar operation as the -= operator on the built-in types
Fraction & Fraction::minusEq (Fraction & op )
{
	if (denominator != op.denominator )
	{
		long long common_divisor = gcd(denominator,op.denominator);
		numerator *= (op.denominator / common_divisor);
		numerator -= op.numerator * ( denominator / common_divisor);
		denominator *= (op.denominator / common_divisor);
	}
	else
	{
		numerator -= op.numerator;
	}

	simplify();

	return (*this);
}

//Implementation of the timesEq() member function
//Performs similar operation as the *= operator on the built-in types
Fraction & Fraction::timesEq (Fraction & op)
{
	numerator *= op.numerator;
	denominator *= op.denominator;

	simplify();  // will make sure that denominator is positive and
	             //   will invoke gcd() function to reduce fraction
	             //   as much as possible

	return (*this); // returns the object which invoked the method
}

//Implementation of the divideEq() member function
//Performs similar operation as the /= operator on the built-in types
Fraction & Fraction::divideEq (Fraction & op )
{
	numerator *= op.denominator;
	denominator *= op.numerator;

	simplify();

	return (*this);
}

//Implementation of the negate() member function
//Performs similar operation as the unary - operator on the built-in types
Fraction Fraction::negate ( void )
{
	return (Fraction(-(numerator), (denominator)));
}

//This member function ensures that the denominator is not negative
//   and uses the gcd template function to reduce the fraction as much as 
//   possible
void Fraction::simplify(void)
{
	if (denominator < 0 ) //correct sign if necessay
	{
		numerator = - numerator;
		denominator = - denominator;
	}

	if (numerator == 0 )
	{
		denominator = 1;
	}

	// Reduce by dividing by gcd, if gcd > 1

	else
	{
		long long  gcd_val =  gcd (numerator, denominator);
		if (gcd_val > 1)
		{
			numerator /= gcd_val;
			denominator /= gcd_val;
		}
	}
}

// returns the numerator of the Fraction object
long long Fraction::getNum(void)
{
	return numerator;
}

// returns the denominator of the Fraction object
long long Fraction::getDenom(void)
{
	return denominator;
}

// displays the fraction object
void Fraction::display (void)
{
	cout << numerator << '/' << denominator;
}


