/*
 *  student.h
 *  Lab 07
 *
 *  Created by Steffen L. Norgren on 04/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <istream>
#include "name.h"

class Student {
public:
	// ctor(s) & additional functions if necessary
	void display(std::ostream& os) const;
	friend std::istream& operator>>(std::istream& is, Student& s);
	//additional friend declarations if necessary
private:
	std::string	id_;	// e.g. a11111111
	Name		name_;
};

// Function Object...
struct NameIs {
public:
	// ctor
	bool operator()(const Student& s) const;
private:
	std::string first_, last_;
};

#endif