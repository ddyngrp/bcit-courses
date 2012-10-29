// Steffen L. Norgren, A00683006
//
// Assignment 04 - GCD.h
// ---------------------------------------------------------------------


template < class T >
T gcd( T num, T denom )
{
	int greatest = 1; // current greatest common divisor, 1 is minimum
	
	if ( num < 0 )
		num *= -1;
	
	if ( denom < 0 )
		denom *= -1;

	// loop from 2 to smaller of x and y
	for ( int i = 2; i <= ( ( num < denom ) ? num: denom ); i++ )
	{
		// if current i divides both x and y
		if ( num % i == 0 && denom % i == 0 )
		greatest = i; // update greatest common divisor
	} // end for

	return greatest; // return greatest common divisor found
}
