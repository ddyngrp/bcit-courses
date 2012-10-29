/*
 *  lab5.h
 *  Lab 05
 *
 *  Created by Steffen L. Norgren on 07/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include <map>
#include <iostream>
#include <cstring>

using namespace std;

class Lab5 {
private:
public:
	Lab5();
	bool is_valid_tag(const string& s);
	bool is_valid_ecode(const string& c);
	string & replace_all(string& s, const string& os, const string& ns);
	
	typedef map<string, string>	TagMap;
	bool add(const string& key, const string& value, TagMap& map);
};