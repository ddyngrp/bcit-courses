/*
 *  tagMap.h
 *  Assignment #1
 *
 *  Created by Steffen L. Norgren on 27/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#ifndef __TAGMAP_H__
#define __TAGMAP_H__

#include <map>

class TagMap {
private:
	typedef std::map<std::string, std::string> TagMap_;
	TagMap_ tagMap;
public:
	TagMap();
	~TagMap();
	bool add(const std::string& key, const std::string& value);
	bool exists(const std::string& key);
	std::string getValue(const std::string& key);
};

#endif