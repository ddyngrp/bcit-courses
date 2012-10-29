/*
 *  tagMap.cpp
 *  Assignment #1
 *
 *  Created by Steffen L. Norgren on 27/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include "main.h"
#include "tagMap.h"

using namespace std;

TagMap::TagMap() {
}

TagMap::~TagMap() {
	tagMap.clear();
}

bool TagMap::add(const string& key, const string& value) {
	if (exists(key)) {
		return false;
	}
	else {
		tagMap.insert(pair<string, string>(key, value));
	}
	
	return true;
}

bool TagMap::exists(const string& key) {
	if (tagMap.find(key) == tagMap.end()) {
		return false;
	}
	
	return true;
}

string TagMap::getValue(const string& key) {
	if (exists(key)) {
		return tagMap[key];
	}
	
	return NULL;
}

