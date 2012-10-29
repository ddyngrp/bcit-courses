/*
 *  tagParser.h
 *  Assignment #1
 *
 *  Created by Steffen L. Norgren on 27/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#ifndef __TAGPARSER_H__
#define __TAGPARSER_H__

#include "tagStack.h"
#include "tagMap.h"

class TagParser {
private:
	bool validEscape(const std::string& text);
	bool validTag(const std::string& tag);
public:
	TagParser();
	std::string parseControlTag(const std::string& text);
	void parseConfigTag(const std::string& text, std::string& tagStart,
						std::string& tagEnd, std::string& escapeCode);
	bool validText(const std::string& text, Stack& tagStack, TagMap& tagMap);
	void parseText(const std::string& text, Stack& tagStack, TagMap& tagMap);
	void changeColour(const std::string& escapeCode);
};

#endif