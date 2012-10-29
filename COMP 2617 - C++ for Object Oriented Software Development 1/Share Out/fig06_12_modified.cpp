// Fig. 6.12: fig06_12.cpp
// A scoping example.

// Modified by Bob Langelaan to show similarity between a built-in
//    type and an user defined class type

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

void useLocal( void ); // function prototype
void useStaticLocal( void ); // function prototype
void useGlobal( void ); // function prototype

class Example{
public:  //members should normally be private, NOT public, but for this example
	     //  I am making the members public so that they can be accessed
	     //  from the non member functions.
	string location;  // to track where object was created
	int value;  // similar to x in original program
public:
	Example(string where, int init_val) // constructor
	{
		location = where;
		value = init_val;

		cout << "\n\nObject has been created at location: " << location << "\n";
	}

	~Example(void) // destructor
	{
		cout << "\n\nThe object created at location \"" << location << "\" has been destroyed\n";
	}
};

Example x("BEFORE START OF MAIN",1); // global variable

int main()
{
   Example x("OUTER BLOCK IN MAIN", 5); // local variable to main

   cout << "local x in main's outer scope is " << x.value << endl;

   { // start new scope
      Example x("INNER BLOCK IN MAIN",7); // hides x in outer scope

      cout << "local x in main's inner scope is " << x.value << endl;
   } // end new scope

   cout << "local x in main's outer scope is " << x.value << endl;

   useLocal(); // useLocal has local x
   useStaticLocal(); // useStaticLocal has static local x
   useGlobal(); // useGlobal uses global x
   useLocal(); // useLocal reinitializes its local x
   useStaticLocal(); // static local x retains its prior value
   useGlobal(); // global x also retains its value

   // See what happens if you change "x.value" below to "::x.value"
   cout << "\nlocal x in main is " << x.value << endl;

   return 0; // indicates successful termination
} // end main

// useLocal reinitializes local variable x during each call
void useLocal( void )
{
   Example x("IN useLocal FUNCTION",25); // initialized each time useLocal is called

   cout << "\nlocal x is " << x.value << " on entering useLocal" << endl;
   x.value++;
   cout << "local x is " << x.value << " on exiting useLocal" << endl;
} // end function useLocal

// useStaticLocal initializes static local variable x only the
// first time the function is called; value of x is saved
// between calls to this function
void useStaticLocal( void )
{
   static Example x("IN useStaticLocal FUNCTION",50); // initialized first time useStaticLocal is called 

   cout << "\nlocal static x is " << x.value << " on entering useStaticLocal" 
      << endl;
   x.value++; 
   cout << "local static x is " << x.value << " on exiting useStaticLocal" 
      << endl;
} // end function useStaticLocal

// useGlobal modifies global variable x during each call
void useGlobal( void )
{
   cout << "\nglobal x is " << x.value << " on entering useGlobal" << endl;
   x.value *= 10;
   cout << "global x is " << x.value << " on exiting useGlobal" << endl;
} // end function useGlobal




/**************************************************************************
 * (C) Copyright 1992-2005 by Deitel & Associates, Inc. and               *
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
 **************************************************************************/
