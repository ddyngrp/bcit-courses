// Assignment 8: Complex.h
// Declaration of class Complex.
// Member functions are defined in Complex.cpp.
// Author: Steffen L. Norgren
// Date: March 22nd, 2007

#ifndef Complex_incl
#define Complex_incl

class Complex
{
public:
	Complex( double = 1, double = 0 ); // Second constructor with default arguments
	Complex & minusEq ( Complex & RHS ); // Subtracts RHS to the Complex object invoked with this method
	Complex & plusEq ( Complex & RHS ); // Adds RHS to the Complex object invoked with this method
	double getRealNum( void ); // Returns the real number
	double getImagineNum( void ); // Returns the imaginary number
	void display( void ); // Outputs to standard output stream the Complex object
	                    // in the format: (a, b) where a is the real part and
						// b is the imaginary part.
private:
	double realNum, // Represents the real part in the Complex Object
		imagineNum; // Represents the imaginary part in the Complex Object
};

#endif