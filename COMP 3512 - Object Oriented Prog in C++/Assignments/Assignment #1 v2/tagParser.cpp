/*
 *  tagParser.cpp
 *  Assignment #1
 *
 *  Created by Steffen L. Norgren on 27/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include "main.h"
#include "tagParser.h"
#include "ansiColours.h"

using namespace std;

TagParser::TagParser() {
}

/* 
 * We'll just strip all spaces and tabs from the input line and return
 * the stripped line as we have a set list of control tags.
 */
string TagParser::parseControlTag(const string& text) {
	string tmpText = text;
	string finalText;
	
	string::iterator it = tmpText.begin();
	while (it != tmpText.end()) {
		if (!isspace(*it) && *it != '\t') {
			finalText += *it;
		}
		*it++;
	}
	return finalText;
}

/*
 * Parse the tags from the config section.
 */
void TagParser::parseConfigTag(const string& text, string& tagStart, string& tagEnd, string& escapeCode) {
	string tmpText = text;
	bool isTagStart, isTagEnd, isEscapeCode;
	
	tagStart = tagEnd = escapeCode = "";
	isTagStart = isTagEnd = isEscapeCode = false;
	
	string::iterator it = tmpText.begin();
	while (it != tmpText.end()) {
		switch (*it) {
			case '<':
				if (!isTagStart && !isTagEnd && !isEscapeCode) {
					isTagStart = true;
				}
				else if (!isTagStart && !isTagEnd && isEscapeCode) {
					isTagEnd = true;
					isEscapeCode = false;
				}
				break;
			case '>':
				if (isTagStart) {
					isEscapeCode = true;
					isTagStart = false;
				}
				else if (isTagEnd) {
					isTagEnd = false;
				}
				break;
			case '/':
				/* Do nothing since we determined the beginning and end
				 * tags through a process of elimination
				 */
				break;
			default:
				if (isTagStart) {
					tagStart += *it;
				}
				else if (isEscapeCode) {
					escapeCode += *it;
				}
				else if (isTagEnd) {
					tagEnd += *it;
				}
				break;
		}
		*it++;
	}
	
	if (tagStart != tagEnd) {
		cerr << "Opening and closing tags do not match." << endl;
		exit(1);
	}
	
	if (!validTag(tagStart) || !validTag(tagEnd)) {
		cerr << "Malformed tag name." << endl; 
		exit(1);
	}

	if (DEBUG == 1 && tagStart.length() != 0) {
		changeColour(escapeCode);
		cout << tagStart << ANSI_NORMAL << endl;
	}
}

/*
 * Validate text section
 */
bool TagParser::validText(const string& text, Stack& tagStack, TagMap& tagMap) {
	string tagStart, tagEnd;
	string tmpText = text;
	bool isTagStart, isTagEnd;
	
	isTagStart = isTagEnd = false;
	
	string::iterator it = tmpText.begin();
	while (it != tmpText.end()) {
		switch (*it) {
			case '<':
				if (!isTagStart && !isTagEnd) {
					isTagStart = true;
				}
				else if (!isTagStart && !isTagEnd) {
					isTagEnd = true;
				}
				break;
			case '>':
				if (isTagStart) {
					isTagStart = false;
					// Make sure the tag was defined in our config section
					if (tagMap.exists(tagStart)) {
						tagStack.push(tagStart);
					}
					else {
						return false;
					}
					tagStart = "";
				}
				else if (isTagEnd) {
					isTagEnd = false;
					if (tagStack.top() == tagEnd) {
						tagStack.pop();
						tagStart = "";
						tagEnd = "";
					}
					else {
						return false;
					}
				}
				break;
			case '/':
				isTagStart = false;
				isTagEnd = true;
				break;
			default:
				if (isTagStart) {
					tagStart += *it;
				}
				else if (isTagEnd) {
					tagEnd += *it;
				}
				break;
		}
		*it++;
	}
	
	return true;
}

/*
 * Process and output text section
 */
void TagParser::parseText(const string& text, Stack& tagStack, TagMap& tagMap) {
	string tagStart, tagEnd, output;
	string tmpText = text;
	bool isTagStart, isTagEnd;
	
	isTagStart = isTagEnd = false;
	
	string::iterator it = tmpText.begin();
	while (it != tmpText.end()) {
		switch (*it) {
			case '<':
				if (!isTagStart && !isTagEnd) {
					isTagStart = true;
				}
				else if (!isTagStart && !isTagEnd) {
					isTagEnd = true;
				}
				break;
			case '>':
				if (isTagStart) {
					isTagStart = false;
					tagStack.push(tagStart);
					changeColour(tagMap.getValue(tagStart));
					tagStart = "";
				}
				else if (isTagEnd) {
					isTagEnd = false;
					tagStack.pop();
					if (!tagStack.empty()) {
						changeColour(tagMap.getValue(tagStack.top()));
					}
					tagStart = "";
					tagEnd = "";
				}
				break;
			case '/':
				isTagStart = false;
				isTagEnd = true;
				break;
			case '&': // handle &lt; and &gt;
				if (*(it + 1) == 'l' && *(it + 2) == 't' && *(it + 3) == ';') {
					cout << '<';
					*(it += 3);
				}
				else if (*(it + 1) == 'g' && *(it + 2) == 't' && *(it + 3) == ';') {
					cout << '>';
					*(it += 3);
				}
				else {
					cout << '&';
					*it++;
				}
				break;
			default:
				if (isTagStart) {
					tagStart += *it;
				}
				else if (isTagEnd) {
					tagEnd += *it;
				}
				else { // output character by character
					if (!tagStack.empty()) { // don't output anything before the <text> tag
						cout << *it;
					}
				}
				break;
		}
		*it++;
	}
}

/*
 * Verify that the tag is valid.
 */
bool TagParser::validTag(const string& tag) {
	string tmpTag = tag;
	
	string::iterator it = tmpTag.begin();
	while (it != tmpTag.end()) {
		if (!isalnum(*it)) {
			return false;
		}
		*it++;
	}
	
	return true;
}

/* 
 * Making sure that our escape codes follow the following format: \e[0;33m
 * or is of the format: \033[0;33m
 * or is a blank format
 */
bool TagParser::validEscape(const string& text) {
	int k;
	
	if (text.length() != 8 || text.length() != 10 || text.length() != 0) {
		return false;
	}
		
	for (string::size_type i = 0; i < text.length(); i++) {
		k = i;
		
		if (text.length() == 10 && i >= 4)  {
			k = i - 2;
			if (i > 0 && i < 4) {
				if (!isdigit(text.at(i))) {
					return false;
				}
			}
		}
		
		switch (k) {
			case 0:
				if (text.at(i) != '\\') {
					return false;
				}
				break;
			case 1:
				if (text.at(i) != 'e') {
					return false;
				}
				break;
			case 2:
				if (text.at(i) != '[') {
					return false;
				}
				break;
			case 3:
				if (!isdigit(text.at(i))) {
					return false;
				}
				break;
			case 4:
				if (text.at(i) != ';') {
					return false;
				}
				break;
			case 5:
				if (isdigit(text.at(i))) {
					return false;
				}
				break;
			case 6:
				if (isdigit(text.at(i))) {
					return false;
				}
				break;
			case 7:
				if (text.at(i) != 'm') {
					return false;
				}
				break;
			default:
				return false; // this shouldn't happen
				break;
		}
		
	}
	return true;
}

/*
 * Change the output colour.
 */
void TagParser::changeColour(const string& escapeCode) {
	string tempCode;
	int startPosition;
	
	if (escapeCode.length() == 8) {
		startPosition = 2;
	}
	else {
		startPosition = 4;
	}
	
	for (int i = startPosition; i < (int)escapeCode.length(); i++) {
		tempCode += escapeCode[i];
	}
	
	cout << '\033' << tempCode;
}

