/*
 *  Name.h
 *  Assignment #2
 *
 *  Created by Steffen L. Norgren on 14/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#ifndef __NAME_H__
#define __NAME_H__

#include <istream>

class Name { 
public: 
	// ctor(s) & additional functions if necessary
	bool extists(std::string fName, std::string lName);
	
	// Friend declarations
	friend std::ostream& operator<<(std::ostream& os, const Name& n); 
	friend std::istream& operator>>(std::istream& is, Name& n); 
private: 
	std::string lowerCase(std::string s);
	std::string first_; // e.g. homer 
	std::string last_; // e.g. simpson 
};

#endif

