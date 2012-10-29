#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "Student.h"

#define MIN_STUDENT_LEN 13

using namespace std;

int main (int argc, char * const argv[]) {
	string inputFile, inputCommand; // Our input string buffers
	string cmd;						// Command buffer string
	string studentRecord = "";		// String to concatinate 2 lines into 1
	int courses = 0;				// Number of courses per record read in
	vector<string> commands;		// Create vector to hold our commands
	vector<Student*> students;		// Container for all our student records
	Student *stuPtr;				// Pointer to our student object
	Grade *grdPtr;					// Pointer to our grade object
	
	// Check if the proper arguments exist
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " [input file]" << endl;
		exit(1);
	}
	
	// Check if the file exists
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << endl;
		exit(1);
	}

	// Process the file contents
	while (getline(in, inputFile)) {
		// Process our input data
		istringstream ss(inputFile);
		
		if (ss >> courses) {
			// Do Nothing
		}
		else {
			// Process courses section
			if (courses) {
				//cerr << inputFile << endl;
				istringstream is;	// Temporary stream
				grdPtr = new Grade;	// Temporary grade object
				
				is.str(inputFile);
				is >> *grdPtr;
				
				stuPtr->addGrade(grdPtr->getCourse(), *grdPtr);
				
				--courses;
			}
			else { // Process student section
				studentRecord += inputFile + " ";
				if (studentRecord.length() > MIN_STUDENT_LEN) {
					istringstream is;		// Temporary stream
					stuPtr = new Student;	// Temporary student object
					
					is.str(studentRecord);
					is >> *stuPtr;
					
					students.push_back(stuPtr);
					studentRecord = "";
				}	
			}
		}
	}
	
	// Initiate our command prompt
	cerr << endl << "Welcome to Assignment #3.\n"
					"input command > ";
	
	// Cycle through an input loop to process commands
	while (getline(cin, inputCommand)) {
		// If the user types exit, quit the program
		if (inputCommand == "exit" || inputCommand == "quit") {
			exit(0);
		}
		else {
			istringstream ss(inputCommand);
			
			// Add the commands to our vector list
			while (ss >> cmd) {
				commands.push_back(cmd);
			}
		}
		
		vector<string>::iterator vi;
		
		// Iterate through our commands
		for (vi = commands.begin(); vi != commands.end(); ++vi) {
			switch (commands.size()) {
				case 1:
					// Process showall command
					if (*vi == "showall") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->display(cout);
						}
						
					} // Process showid command
					else if (*vi == "showid") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->displayAllID(cout);
						}
					}
					break;
				case 3:
					// Process showall id <id> command
					if (*vi == "showall" && *(vi + 1) == "id") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->displayID(cout, *(vi + 2));
						}						
					}
					break;
				case 4:
					// Process showall name <first> <last> command
					if (*vi == "showall" && *(vi + 1) == "name") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->displayName(cout, *(vi + 2), *(vi + 3));
						}						
					} // Process showid name <first> <last> command
					else if (*vi == "showid" && *(vi + 1) == "name") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->displayNameID(cout, *(vi + 2), *(vi + 3));
						}						
					}
					// Process showall grade <course> <grade>
					else if (*vi == "showall" && *(vi + 1) == "grade") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->displayByGrade(cout, *(vi + 2), *(vi + 3), false);
						}						
					} // Process showid grade <course> <grade>
					else if (*vi == "showid" && *(vi + 1) == "grade") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->displayByGrade(cout, *(vi + 2), *(vi + 3), true);
						}						
					}
					break;
				case 5:
					// Process showall grade <course> <lowGrade> <highGrade>
					if (*vi == "showall" && *(vi + 1) == "grade") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->displayByGradeRange(cout, *(vi + 2), *(vi + 3), *(vi + 4), false);
						}						
					} // Process showid grade <course> <lowGrade> <highGrade>
					else if (*vi == "showid" && *(vi + 1) == "grade") {
						// Iterate through our student records
						vector<Student*>::iterator vs;
						
						for (vs = students.begin(); vs != students.end(); ++vs) {
							Student *tmpPtr = *vs;
							tmpPtr->displayByGradeRange(cout, *(vi + 2), *(vi + 3), *(vi + 4), true);
						}						
					}
					break;
				default:
					break;
			}
		}
		
		cerr << "input command > ";
		commands.clear(); // clear our vector list for the next line of input
	}
    
	return 0;
}