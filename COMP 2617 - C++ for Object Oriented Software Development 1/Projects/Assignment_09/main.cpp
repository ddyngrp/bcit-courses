// Assignment 9: main.cpp
// Author: Steffen L. Norgren
// Date: April 4, 2007

#include <iostream>
using namespace std; // using the entire std namespace

#include "TicTacToe.h" // include definiton of class TicTacToe

void waitOnInput(); // function definition for the new method of pausing

int main()
{
	TicTacToe g; // creates object g of class TicTacToe 
	g.makeMove(); // invokes function makeMove
//	system("pause"); // This does not work on linux or Mac OS X.
					 // It is also resource intensive and not recommended
					 // as you are making a call to an external program,
					 // pause.exe in this case.
	waitOnInput(); // pauses the program
	return 0;
} // end main

void waitOnInput()
{
	cin.clear(); // first get rid of any errors
	cin.ignore( cin.rdbuf()->in_avail() );
	cout << "\nPress Enter to continue...";
	cin.get(); // pause the program
} // end waitOnInput