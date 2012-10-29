// Assignment 8: Complex.cpp
// Member-function definitions for class Complex.
// Author: Steffen L. Norgren
// Date: March 22nd, 2007

#include "Complex.h"

#include <iostream>
using std::cout;
using std::fixed;

#include <iomanip>
using std::setprecision;

Complex::Complex( double a, double b )
{
	realNum = a;
	imagineNum = b;
}

Complex & Complex::plusEq ( Complex & op )
{
	realNum += op.realNum;
	imagineNum += op.imagineNum;

	return (*this);
}

Complex & Complex::minusEq ( Complex & op )
{
	realNum -= op.realNum;
	imagineNum -= op.imagineNum;

	return (*this);
}

double Complex::getRealNum( void )
{
	return realNum;
}

double Complex::getImagineNum( void )
{
	return imagineNum;
}

void Complex::display( void )
{
	cout << fixed << setprecision( 3 );
	cout << "( " << realNum << " , " << imagineNum << " )";
}

