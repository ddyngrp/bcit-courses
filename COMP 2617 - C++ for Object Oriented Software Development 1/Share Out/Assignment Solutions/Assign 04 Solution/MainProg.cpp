// Assign 5 Main Program - used to "test drive" the Fraction class
// File Name: MainProg.cpp
// Author: Bob Langelaan
// Date: Feb. 18th, 2006

#include <iostream>
using std::cout;
using std::endl;

#include "Fraction.h" // include definition of class Fraction from Fraction.h
#include "GCD.h"      // include definition of gcd template function

int main()
{
	// Test constructors

	Fraction A; // create a Fraction object with default ctor
	cout << "The default object is: ";
	A.display();

	Fraction B(1,1024); // create a Fraction object with the non-default ctor
	cout << "\n\nThe non-default object is: ";
	B.display();

	Fraction C(8,-1024); // test to see if the simplify method is invoked from 
	                                //   the non-default ctor
	cout << "\n\n8/-1024 simplified is: ";
	C.display();

	// Test template gcd() function

	// implicitly invoke template function

	int intX = 1024;
	int intY = 32;

	int intAns = gcd(intX,intY); // implicit invocation
	cout << "\n\nThe greatest common divisor of 1024 and 32 is: " << intAns;

	// explicitly invoke template function

	long longX = 1024;
	long longY = 1048576;

	long longAns = gcd<long>(longX, longY); // explicit invocation
	cout << "\n\nThe greatest common divisor of 1024 and 1048576 is: " << longAns;

	// Test timesEq()
	cout << "\n\n- Test timesEq()";
	A = Fraction(2,3); //Assign new values to Fraction objects
	B = Fraction(3,5);

	// NOTE: Equivalent to:  C = A *= B;
	C = A.timesEq(B);

	cout << "\nA = ";
	A.display();
	cout << "\nB = ";
	B.display();
	cout << "\nC = ";
	C.display();

	// Test divideEq()
	cout << "\n\n- Test divideEq()";
	A = Fraction(2,3);  //Assign new values to Fraction objects
	B = Fraction(-7,3);

	// NOTE: Equivalent to:  C = A /= B;
	C = A.divideEq(B);

	cout << "\nA = ";
	A.display();
	cout << "\nB = ";
	B.display();
	cout << "\nC = ";
	C.display();

	// Test plusEq()
	cout << "\n\n- Test plusEq()";
	A = Fraction(-2,-3);  //Assign new values to Fraction objects
	B = Fraction(8,9);

	// NOTE: Equivalent to:  C = A += B;
	C = A.plusEq(B);

	cout << "\nA = ";
	A.display();
	cout << "\nB = ";
	B.display();
	cout << "\nC = ";
	C.display();

	// Test minusEq()
	cout << "\n\n- Test minusEq()";
	A = Fraction(2,3);  //Assign new values to Fraction objects
	B = Fraction(8,9);

	// NOTE: Equivalent to:  C = A -= B;
	C = A.minusEq(B);

	cout << "\nA = ";
	A.display();
	cout << "\nB = ";
	B.display();
	cout << "\nC = ";
	C.display();

	// Test negate()
	cout << "\n\n- Test negateEq()";
	A = Fraction(-2,3);  //Assign new values to Fraction objects
	B = Fraction(8,9);

	// NOTE: Equivalent to:  C = -A;
	C = A.negate();

	cout << "\nA = ";
	A.display();
	cout << "\nC = ";
	C.display();

	// NOTE: Equivalent to:  C = -B;
	C = B.negate();

	cout << "\nB = ";
	B.display();
	cout << "\nC = ";
	C.display();

	// More fun with references

	cout << "\n\n- More fun with references";
	A = Fraction(2,3); //Assign new values to Fraction objects
	B = Fraction(3,5);

	Fraction & fractionRef = A.timesEq(B);

	// note that fractionRef is a reference for fractionObjA, since
	//   timesEq returns a reference to the object that invoked it,
	//   which in the line of code above, is fractionObjA

	cout << "\nA = ";
	A.display();
	cout << "\nfractionRef = ";
	fractionRef.display();

	// if we now modify fractionObjA, we also modify fractionRef

	A = Fraction(75); //Assign a new value to fractionObjA

	cout << "\nA = ";
	A.display();
	cout << "\nfractionRef = ";
	fractionRef.display();

	cout << '\n' << endl;

	return 0;

} // end main

