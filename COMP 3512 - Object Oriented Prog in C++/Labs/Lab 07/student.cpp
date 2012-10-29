/*
 *  student.cpp
 *  Lab 07
 *
 *  Created by Steffen L. Norgren on 04/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include <iostream>
#include "student.h"
#include "name.h"

using namespace std;

void Student::display(ostream& os) const {
	os << id_ << " " << name_ << endl;
}

istream& operator>>(std::istream& is, Student& s) {
	is >> s.id_ >> s.name_;
	return is;
}