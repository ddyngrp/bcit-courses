/*
 *  Grade.h
 *  Assignment #2
 *
 *  Created by Steffen L. Norgren on 14/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#ifndef __GRADE_H__
#define __GRADE_H__

#include <istream>

class Grade { 
public: 
	// ctor(s) & additional functions if necessary
	std::string getCourse();
	int Grade::getGrade();
	
	// Friend declarations
	friend std::ostream& operator<<(std::ostream& os, const Grade& g); 
	friend std::istream& operator>>(std::istream& is, Grade& g); 
private: 
	std::string lowerCase(std::string s);
	std::string course_;	// e.g. comp3512
	int score_;				// e.g. 90
};

#endif