// Steffen L. Norgren, A00683006
//
// Home Lab Class 02 - Question 3.14: Employee.hh
// ---------------------------------------------------------------------



#include <string> // Using the C++ Standard string class
using std::string;


// Employee class definition
class Employee
{
	public:
		Employee( string, string, int ); // initialize object
		void setFirstName( string );
		void setLastName( string );
		void setSalary( int );
		string getFirstName();
		string getLastName();
		int getSalary();
	private:
		string FirstName;
		string LastName;
		int Salary;
};
