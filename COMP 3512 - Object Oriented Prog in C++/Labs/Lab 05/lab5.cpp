/*
 *  lab5.cpp
 *  Lab 05
 *
 *  Created by Steffen L. Norgren on 07/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include "lab5.h"

Lab5::Lab5() { // empty default constructor
}

bool Lab5::is_valid_tag(const string& s) {

	if (s.length() == 0) {
		return false;
	}
	
	for (string::size_type i = 0; i < s.length(); i++) {
		if (!isalnum(s.at(i))) {
			return false;
		}
	}
	
	return true;
}

bool Lab5::is_valid_ecode(const string& c) {

	for (string::size_type i = 0; i < c.length(); i++) {
		if (isspace(c.at(i))) {
			return false;
		}
	}

	return true;
}

string & Lab5::replace_all(string& s, const string& os, const string& ns) {
	size_t found;
	
	while (true) {
		found = s.find(os, found);
		if (found == string::npos) {
			break;
		}
		s.replace(found, os.length(), ns);
		found+=ns.length();
	}
	return s;
}

bool Lab5::add(const string& key, const string& value, TagMap& map) {

	if (map.find(key) == map.end()) {
		return false;
	}
	else {
		map.insert(pair<string,string>(key,value));
	}
	
	return true;
}
