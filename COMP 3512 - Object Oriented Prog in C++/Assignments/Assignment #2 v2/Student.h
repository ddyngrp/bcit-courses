/*
 *  Student.h
 *  Assignment #2
 *
 *  Created by Steffen L. Norgren on 14/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <istream>
#include <map>
#include "Name.h"
#include "Grade.h"

class Student {
public:
	// ctor(s) & additional functions if necessary
	void display(std::ostream& os);							// displays all record information
	void displayAllID(std::ostream& os);					// displays all student IDs
	void displayID(std::ostream& os, std::string sID);		// display student with a specific ID
	void displayName(std::ostream& os, std::string fName, std::string lName);		// display all students with a particular name
	void displayNameID(std::ostream& os, std::string fName, std::string lName);		// display all student IDs for particular names
	// display all students with a particular grade in a course	
	void displayByGrade(std::ostream& os, std::string course, std::string grade, bool idOnly);
	// display all students with a particular grade range in a course
	void displayByGradeRange(std::ostream& os, std::string course, std::string lowGrade, std::string highGrade, bool idOnly);
	
	void addGrade(std::string course, Grade& g);	// add a grade object to our map

	// Friend declarations
	friend std::istream& operator>>(std::istream& is, Student& s);
private:
	std::string lowerCase(std::string s);
	std::string id_; // e.g. a11111111
	Name name_;
	// an STL container of Grade objects
	std::map<std::string, Grade> grade_;
};

#endif

