/*
 *  Grade.cpp
 *  Assignment #2
 *
 *  Created by Steffen L. Norgren on 14/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include "Grade.h"

using namespace std;

string Grade::getCourse() {
	return course_;
}

int Grade::getGrade() {
	return score_;
}

istream& operator>>(istream& is, Grade& g) {
	is >> g.course_ >> g.score_;
	return is;
}

ostream& operator<<(ostream& os, const Grade& g) {
	os << g.course_ << " " << g.score_ << endl;
	return os;
}

string Grade::lowerCase(string s) {
	
	for (int i = 0; i < (int)s.length(); ++i) {
		s[i] = tolower(s[i]);
	}
	
	return s;
}

