// Steffen L. Norgren, A00683006
//
// Assignment 04 - GCD.h
// ---------------------------------------------------------------------

template < class T >
T min( T value1, T value2 )
{
	if ( value2 > value1 )
		return value1;
	else
		return value2;
}
