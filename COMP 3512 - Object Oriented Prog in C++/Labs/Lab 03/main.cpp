#include <iostream>
#include <sstream>

#include "Lab.h"

using namespace std;

int main () {
	string lastName;
	string firstName;
	string inputLine;
	int score;
	
	while (getline(cin, inputLine)) {
		istringstream iss(inputLine);

		cout << lastName << " " << firstName << " " << score << endl;
	}
	
    return 0;
}
