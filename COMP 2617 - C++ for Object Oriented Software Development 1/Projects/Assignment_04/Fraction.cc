// Steffen L. Norgren, A00683006
//
// Assignment 04 - Fraction.cc
// ---------------------------------------------------------------------

#include "Fraction.h"
#include "GCD.h" // template function for calculating greatest common divisor

#include <iostream>
using std::cout;

Fraction::Fraction( void )
{
	numerator = 0;
	denominator = 1;
}

Fraction::Fraction( long long num, long long denom )
{
	numerator = num;
	denominator = denom;
	
	simplify();
}

// Implementation of the timesEq method
// Performs similar operation as the *= operator on the buit-in types
Fraction & Fraction::timesEq( Fraction & op )
{
	numerator *= op.numerator;
	denominator *= op.denominator;

	simplify();  // will make sure that denominator is positive and
	             // will invoke gcd() function to reduce fraction
	             // as much as possible

	return (*this); // returns the object which invoked the method
}

Fraction & Fraction::divideEq( Fraction & op )
{
	numerator *= op.denominator;
	denominator *= op.numerator;

	simplify();
	
	return (*this); // returns the object which invoked the method
}


Fraction & Fraction::plusEq( Fraction & op )
{
	// Fraction Addition: a/b + c/d = (a*d + b*c) / (b*d)
	
	numerator = (numerator * op.denominator) + (op.numerator * denominator);
	denominator = denominator * op.denominator;
	
	simplify();
	
	return (*this); // returns the object which invoked the method
}

Fraction & Fraction::minusEq( Fraction & op )
{
	// Subtraction: a/b - c/d = (a*d - b*c) / (b*d)
	numerator = (numerator * op.denominator) - (op.numerator * denominator);
	denominator = denominator * op.denominator;
	
	simplify();
	
	return (*this); // returns the object which invoked the method
}

Fraction Fraction::negate()
{
	simplify();
	
	numerator *= -1;
	
	return (*this);
}

long long Fraction::getNum()
{
	return numerator;
}

long long Fraction::getDenom()
{
	return denominator;
}

void Fraction::display()
{
	cout << getNum() << "/" << getDenom();
}

// Simple simplification of fractions by calling
// the GCD template. Deliciousness ensues.
void Fraction::simplify()
{
	int divisor = gcd(numerator, denominator);
	
	numerator = numerator / divisor;
	denominator = denominator / divisor;
	
	// If the denominator is negative, do a flip of the negatives.
	if ( denominator < 0 )
	{
		denominator *= -1;
		numerator *= -1;
	}
}
