// Fig. 10.11: Date.cpp
// Member-function definitions for class Date.
#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
//using namespace std;

#include "Date.h" // include Date class definition

// Initialize to current date
Date::Date()
{
	time_t t;
	
	time(&t); //get current date and time
	
	struct tm *pt = localtime(&t); //convert time_t to a structure

	year = pt->tm_year + 1900;
	day = pt->tm_mday;
	month = pt->tm_mon + 1;
}

// Initialize to the ddd, yyyy format
Date::Date( int dys, int yr )
{
	year = yr;
	setMMDDFromDDD( dys );
}

Date::Date( string mn, int dy, int yr )
{
	setMMFromMonth( mn );
	day = checkDay( dy );
	year = yr;
	
}

Date::Date( int mn, int dy, int yr )
{
	if ( mn > 0 && mn <= 12 ) // validate the month
		month = mn;
	else 
	{                     
		month = 1; // invalid month set to 1
		cout << "Invalid month (" << mn << ") set to 1.\n";
	} // end else
	
	setYYYYFromYY( yr );
	day = checkDay( dy ); // validate the day
	
	// output Date object to show when its constructor is called
	cout << "Date object constructor for date ";
	print();                   
	cout << endl;
} // end Date constructor

// print Date object in form month/day/year
void Date::print() const
{
	cout << month << '/' << day << '/' << year << '\n';
} // end function print

void Date::printDDDYYYY() const
{
	cout << convertDDToDDD() << ' ' << year << '\n';
}

void Date::printMMDDYY() const
{
	if ( month < 10 )
		cout << "0" << month;
	else
		cout << month;
		
	cout << "/";
		
	if ( day < 10 )
		cout << "0" << day;
	else
		cout << day;
		
	cout << "/";
	
	if ( year < 100 )
		cout << year;
	else
	{
		if ( year == 2000 )
			cout << "00";
		
		if ( year > 2000 && year < 2010 )
			cout << "0" << year - 2000;
		
		if ( year >= 2010 )
			cout << year - 2000;
			
		if ( year < 2000 )
			cout << year - 1900;
	}
	
	cout << '\n';
}

void Date::printMonthDDYYYY() const
{
	static const string months[ 13 ] = { "", "January", "February", "March", "April",
										"May", "June", "July", "August", "September",
										"October", "November", "December" };

	cout << months[ month ] << " " << day << ", " << year << '\n';
}

// output Date object to show when its destructor is called
Date::~Date()
{ 
	cout << "Date object destructor for date ";
	print();
	cout << endl;
} // end ~Date destructor

// utility function to confirm proper day value based on 
// month and year; handles leap years, too
int Date::checkDay( int testDay ) const
{
	static const int daysPerMonth[ 13 ] = 
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	// determine whether testDay is valid for specified month
	if ( testDay > 0 && testDay <= daysPerMonth[ month ] )
		return testDay;
	
	// February 29 check for leap year 
	if ( month == 2 && testDay == 29 && ( year % 400 == 0 || 
										  ( year % 4 == 0 && year % 100 != 0 ) ) )
		return testDay;
	
	cout << "Invalid day (" << testDay << ") set to 1.\n";
	return 1; // leave object in consistent state if bad value
} // end function checkDay

void Date::setYYYYFromYY( int yr )
{
	year = yr + 2000;
}

void Date::setMMFromMonth( string mn )
{
	static const string months[ 13 ] = { "", "January", "February", "March", "April",
										"May", "June", "July", "August", "September",
										"October", "November", "December" };

	for ( int i = 1; i <= 12; i++ )
	{
		if ( mn == months[ i ] )
			month = i;
	}
}

void Date::setMMDDFromDDD( int dys )
{
	int daycount = 0;
	
	static const int daysPerMonth[ 13 ] = 
		{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	for ( int i = 1; i <= 12; i++ )
	{
		if ( daycount < dys )
		{
			daycount += daysPerMonth[ i ];
			month = i;
			day = daysPerMonth[ i ] - (daycount - dys);
		}
	}
}

int Date::convertDDToDDD() const
{
	int dys = 0;
	
	static const int daysPerMonth[ 13 ] = 
		{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		
	for ( int i = 1; i < month; i++ )
	{
		dys += daysPerMonth[ i ];
	}
	
	// Check for leap year
	if ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) )
		dys += 1;

	return ( dys + day );
}