#include <iostream>
#include "name.h"
#include "student.h"

using namespace std;

int main (int argc, char * const argv[]) {
	Name name;
	Student student;
	
	cin >> student;
	
	student.display(cout);
	
    return 0;
}
