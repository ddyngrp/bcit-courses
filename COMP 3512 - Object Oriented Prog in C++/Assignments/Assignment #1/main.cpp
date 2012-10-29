/*
 *  main.cpp
 *  Assignment #1
 *
 *  Created by Steffen L. Norgren on 26/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include "ansiColours.h"
#include "main.h"
#include "tagMap.h"
#include "tagParser.h"
#include "tagStack.h"

using namespace std;

int main() {
	string inputLine, tagStart, tagEnd, escapeCode;
	bool inML, inConfig, inText; // some control settings to tell us what section we're dealing with
	TagParser tp;
	TagMap tm;
	Stack tagStack;

	inML = inConfig = inText = false;
	
	while (getline(cin, inputLine)) {
		// Use the appropriate processing method
		if (inML && inConfig && tp.parseControlTag(inputLine) != CONFIG_END) { // process config tags
			tp.parseConfigTag(inputLine, tagStart, tagEnd, escapeCode);
			// If the escape code was blank, we'll use ASCII_NORMAL
			if (escapeCode.length() == 0) {
				tm.add(tagStart, ANSI_NORMAL);
			}
			else {
				tm.add(tagStart, escapeCode);
			}
		}
		if (inML && inText && tp.parseControlTag(inputLine) != TEXT_END) { // process text
			if (tp.validText(inputLine, tagStack, tm)) {
				if (DEBUG == 0) {
					tp.parseText(inputLine, tagStack, tm);
					cout << endl;
				}
			}
			else {
				cerr << "Improperly nested tags or missing tags." << endl;
				exit(1);
			}
		}
		
		// Set the current parsing mode
		if (tp.parseControlTag(inputLine) == ML_START) {
			inML = true;
		}
		else if (tp.parseControlTag(inputLine) == ML_END) {
			inML = false;
		}
		else if (tp.parseControlTag(inputLine) == CONFIG_START) {
			inConfig = true;
		}
		else if (tp.parseControlTag(inputLine) == CONFIG_END) {
			inConfig = false;
		}
		else if (tp.parseControlTag(inputLine) == TEXT_START && !inConfig) {
			inText = true;
		}
		else if (tp.parseControlTag(inputLine) == TEXT_END && !inConfig) {
			inText = false;
		}
	}

	return 0;
}