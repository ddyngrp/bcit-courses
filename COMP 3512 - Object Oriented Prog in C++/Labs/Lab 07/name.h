/*
 *  name.h
 *  Lab 07
 *
 *  Created by Steffen L. Norgren on 04/11/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#ifndef __NAME_H__
#define __NAME_H__

#include <istream>

class Name {
public:
	// ctor(s) & additional function sif neccessary
	friend std::ostream& operator<<(std::ostream& os, const Name& n); // sample output: homer simpson
	friend std::istream& operator>>(std::istream& is, Name& n);
	// additional friend declarations if necessary
private:
	std::string first_;	// e.g. Homer
	std::string last_;	// e.g. Simpson
};

#endif