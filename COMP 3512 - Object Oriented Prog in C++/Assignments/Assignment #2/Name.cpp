/*
 *  Name.cpp
 *  Assignment #2
 *
 *  Created by Steffen L. Norgren on 14/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include <cctype>
#include "Name.h"
#include "Student.h"

using namespace std;

bool Name::extists(string fName, string lName) {

	if (lowerCase(fName) == lowerCase(first_) && lowerCase(lName) == lowerCase(last_)) {
		return true;
	}
	
	if (lowerCase(fName) == "*" && lowerCase(lName) == lowerCase(last_)) {
		return true;
	}
	
	if (lowerCase(fName) == lowerCase(first_) && lowerCase(lName) == "*") {
		return true;
	}
	
	if (lowerCase(fName) == "*" && lowerCase(lName) == "*") {
		return true;
	}
	
	return false;
}

istream& operator>>(istream& is, Name& n) {
	is >> n.first_ >> n.last_;
	return is;
}

ostream& operator<<(ostream& os, const Name& n) {
	os << n.first_ << " " << n.last_;
	return os;
}

string Name::lowerCase(string s) {
	
	for (int i = 0; i < s.length(); ++i) {
		s[i] = tolower(s[i]);
	}
	
	return s;
}