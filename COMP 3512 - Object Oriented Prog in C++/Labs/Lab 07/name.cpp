/*
 *  name.cpp
 *  Lab 07
 *
 *  Created by Steffen L. Norgren on 04/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include <istream>
#include "name.h"
#include "student.h"

using namespace std;

istream& operator>>(std::istream& is, Name& n) {
	is >> n.first_ >> n.last_;
	return is;
}

ostream& operator<<(ostream& os, const Name& n) {
	os << n.first_ << " " << n.last_;
	return os;
}