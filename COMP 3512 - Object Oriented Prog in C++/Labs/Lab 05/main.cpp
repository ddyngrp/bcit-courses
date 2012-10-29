#include <iostream>
#include "lab5.h"

int main () {
	Lab5 lab;
	string testString = "abc";
	
	if (lab.is_valid_tag(testString)) {
		cout << "TRUE!!" << endl;
	}
	else {
		cout << "FALSE" << endl;
	}
	
	if (lab.is_valid_ecode(testString)) {
		cout << "TRUE!!" << endl;
	}
	else {
		cout << "FALSE" << endl;
	}
	
	string s1 = "replaceable replace";
	string s2 = "replace";
	string s3 = "change";
	
	cout << lab.replace_all(s1, s2, s3) << endl;
	
	return 0;
}
