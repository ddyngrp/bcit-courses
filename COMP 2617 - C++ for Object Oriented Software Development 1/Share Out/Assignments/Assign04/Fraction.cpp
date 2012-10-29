// Assignment 4: Fraction.cpp
// Member-function definitions for class Fraction.
// Author:  
// Date: 

#include "Fraction.h"
#include "GCD.h" // template function for calculating greatest common divisor

#include <iostream>
using std::cout;

//Implementation of the timesEq method
//Performs similar operation as the *= operator on the buit-in types
Fraction & Fraction::timesEq (Fraction & op )
{
	numerator *= op.numerator;
	denominator *= op.denominator;

	simplify();  // will make sure that denominator is positive and
	             //   will invoke gcd() function to reduce fraction
	             //   as much as possible

	return (*this); // returns the object which invoked the method
}
