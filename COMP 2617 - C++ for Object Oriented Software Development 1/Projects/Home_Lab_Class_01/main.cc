// Steffen L. Norgren, A00683006
//
// Home Lab Class 01 - Question 2.19: main.cc
// ---------------------------------------------------------------------
// | A program that inputs three integers from the keyboard and prints |
// | the sum, average, product, smallest and largest of these numbers. |
// ---------------------------------------------------------------------

#include <iostream>	// Include that allows input/output
#include <cmath>	// Include the math library

using std::cout;	// Program uses cout
using std::cin;		// Program uses cin
using std::endl;	// Program uses endln

// Let the program begin!
int main()
{
	int number1; // First integer to input
	int number2; // Second integer to input
	int number3; // Third integer to input
	
	// Initializing variables for the results
	int result_sum;
	double result_average; // double since we can have values like 1.333
	int result_product;
	int result_smallest;
	int result_largest;
	
	// getting 3 integers from user
	cout << "Input three different integers:" ;
	cin >> number1 >> number2 >> number3;
	
	
	// Summing the input variables
	result_sum = number1 + number2 + number3;
	
	// Averaging the input variables and converting to a double
	// in order to retain decimal percision.
	result_average = static_cast< double >(result_sum) / 3;
	
	// Multiplying the input variables
	result_product = number1 * number2 * number3;
	
	// Determining minimum value
	result_smallest = number1; // assume as smallest to start
	
	if ( number2 < result_smallest )
		result_smallest = number2;
	
	if ( number3 < result_smallest )
		result_smallest = number3;

	// Determining maximum value
	result_largest = number1; // assume as largest to start
	
	if ( number2 > result_largest )
		result_largest = number2;
	
	if ( number3 > result_largest )
		result_largest = number3;

	
	// Formatting output
	cout << "Sum is " << result_sum << endl;
	cout << "Average is " << result_average << endl;
	cout << "Product is " << result_product << endl;
	cout << "Smallest is " << result_smallest << endl;
	cout << "Largest is " << result_largest << endl;
	
	return 0;
}
