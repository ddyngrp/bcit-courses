/* 

   This program was created by Bob Langelaan.
   This program was last modified Oct.5, 2005

   The purpose of the ctor_ex class and this main function that uses 
   the class, is to demonstrate:

   1) how to declare and implement a default ctor, conversion ctor and copy ctor
   2) various ways that ctors can be invoked
   3) an example of declaring and using a static member

*/

#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl; 
using std::cin; 

#include "Ctor_Examples.h"

int main()
{

// Initialize

   int i;                // used as arguement to some of the ctors
   int * iptr = &i;      // also used as an arguement to some of the ctors

// Invoke ctors a variety of ways

   cout << "\nObject 1 about to be created\n";
   ctor_ex obj1;

   cout << "\nObject 2 about to be created\n";
   ctor_ex obj2 = 1;
 
   cout << "\nObject 3 about to be created\n";
   ctor_ex obj3 = ctor_ex(1);

   cout << "\nObject 4 about to be created\n";
   ctor_ex obj4(i);

   cout << "\nObject 5 about to be created\n";
   ctor_ex obj5 = i;

   cout << "\nObject 6 about to be created\n";
   ctor_ex obj6 = iptr;

   cout << "\nObject 7 about to be created\n";
   ctor_ex(1);  // Note that this object's dtor is invoked immediately after the ctor, has finished
                //    because the object is not assigned a label, and can therefore not be referenced 
                //    after this line of code.

   cout << endl;
   system ("pause");  // to allow user to see output genererated so far

   cout << "\nObject 8 about to be created\n";
   ctor_ex obj8(obj1);

   cout << "\nObject 9 about to be created\n";
   ctor_ex obj9 = obj8;

/*
     The following two ctor invocations (for obj10 & obj11) produced compile 
     errors with MS VC++ 6 (at least with the default settings) but 
     do NOT produce compile errors with MS VC++ .NET (again with default settings).

     Therefore, if you compile this code with certain compilers (including MS VC++ 6)
     you may need to comment out the next 4 statemnts to get a clean compile.
*/

   cout << "\nObject 10 about to be created\n";
   ctor_ex obj10 = ctor_ex(i);

   cout << "\nObject 11 about to be created\n";
   ctor_ex obj11 = ctor_ex(iptr);

/* 
     The following program statements do not produce compile errors
     but will produce run time errors (because the destructor will
	 attempt to destroy the same object twice). The runtime
     errors occur because we have not overloaded the
     the assignment operator for our ctor_ex class. Can you see
	 why we need to overload the assignment operator?
     
   cout << "\nObject 12 about to be created\n";
   ctor_ex obj12;
   obj12 = ctor_ex(i);  // this statement will eventually cause a runtime error

   cout << "\nObject 13 about to be created\n";
   ctor_ex obj13;
   obj13 = ctor_ex(iptr); // this statement will eventually cause a runtime error

*/
   cout << "\n\n";
   return 0;
}

