/*
 *  Student.cpp
 *  Assignment #2
 *
 *  Created by Steffen L. Norgren on 14/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include <iostream>
#include <sstream>
#include "Student.h"

using namespace std;

void Student::display(ostream& os) {
	os << id_ << endl << name_ << endl;
	
	// Iterate through the courses and add to the ostream
	map<string, Grade>::iterator it;
	
	for (it = grade_.begin(); it != grade_.end(); ++it) {
		os << it->second;
	}
}

void Student::displayAllID(ostream& os) {
	os << id_ << endl;
}

void Student::displayID(ostream& os, string sID) {
	if (lowerCase(id_) == lowerCase(sID)) {
		os << id_ << endl << name_ << endl;
		
		// Iterate through the courses and add to the ostream
		map<string, Grade>::iterator it;
		
		for (it = grade_.begin(); it != grade_.end(); ++it) {
			os << it->second;
		}
	}
}

void Student::displayName(ostream& os, string fName, string lName) {
	if (name_.extists(fName, lName)) {
		os << id_ << endl << name_ << endl;
		
		// Iterate through the courses and add to the ostream
		map<string, Grade>::iterator it;
		
		for (it = grade_.begin(); it != grade_.end(); ++it) {
			os << it->second;
		}
	}
}

void Student::displayNameID(ostream& os, string fName, string lName) {
	if (name_.extists(fName, lName)) {
		os << id_ << endl;
	}
}

void Student::displayByGrade(ostream& os, string course, string grade, bool idOnly) {
	istringstream gr(grade);
	int iGrade;

	if (gr >> iGrade) {
		if (iGrade == grade_[lowerCase(course)].getGrade()) {
			if (!idOnly) {
				os << id_ << endl << name_ << endl;
			}
			else {
				os << id_ << endl;
			}
		}
	}
}

void Student::displayByGradeRange(ostream& os, string course, string lowGrade, string highGrade, bool idOnly) {
	istringstream lG(lowGrade);
	istringstream hG(highGrade);
	int iLG, iHG;
	
	if (lG >> iLG && hG >> iHG) {
		if (iLG <= grade_[lowerCase(course)].getGrade() && iHG >= grade_[lowerCase(course)].getGrade()) {
			if (!idOnly) {
				os << id_ << endl << name_ << endl;
			}
			else {
				os << id_ << endl;
			}
		}
	}
}

void Student::addGrade(string course, Grade& g) {
	grade_.insert(map<string, Grade>::value_type(lowerCase(course), g));
}

istream& operator>>(istream& is, Student& s) {
	is >> s.id_ >> s.name_;
	return is;
}

string Student::lowerCase(string s) {
	
	for (int i = 0; i < (int)s.length(); ++i) {
		s[i] = tolower(s[i]);
	}
	
	return s;
}

