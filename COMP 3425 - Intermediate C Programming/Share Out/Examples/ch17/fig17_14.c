// Fig 17.14: fig17_14.c
// Using complex numbers in C99
#include <stdio.h>
#include <complex.h> // for complex type and math functions

int main()
{
    double complex a = 32.123 + 24.456 * I; // a is 32.123 + 24.456i
    double complex b = 23.789 + 42.987 * I; // b is 23.789 + 42.987i
    double complex c = 3 + 2 * I;
    
    double complex sum = a + b; // perform complex addition
    double complex pwr = cpow( a, c ); // perform complex exponentiation
    
    printf( "a is %f + %fi\n", creal( a ), cimag( a ));
    printf( "b is %f + %fi\n", creal( b ), cimag( b ));
    printf( "a + b is: %f + %fi\n", creal( sum ), cimag( sum ));
    printf( "a - b is: %f + %fi\n", creal( a - b ), cimag( a - b ));
    printf( "a * b is: %f + %fi\n", creal( a * b ), cimag( a * b ));
    printf( "a / b is: %f + %fi\n", creal( a / b ), cimag( a / b ));
    printf( "a ^ b is: %f + %fi\n", creal( pwr ), cimag( pwr ));

    return 0; // indicates successful termination
} // end main


 /*************************************************************************
 * (C) Copyright 1992-2007 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/

