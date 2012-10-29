#include <stdio.h>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	string inputSpecification, inputLine, base, floatExp;
	char checkDecimal;
	int intIO, formatWidth, floatPrecision;
	float floatIO;
	int isInt;
	
	while (getline(cin, inputLine)) {
		isInt = 0;
		istringstream intInputStream(inputLine);
		if (intInputStream >> inputSpecification >> intIO) {
			istringstream intInputStreamSpec(inputSpecification);
			if (intInputStreamSpec >> formatWidth >> base) {
				if(base == "d") {
					cout << dec << right << setw(formatWidth) << intIO << endl;
					isInt = 1;
				}
				if(base == "x") {
					cout << hex << right << setw(formatWidth) << intIO << endl;
					isInt = 1;
				}
				if(base == "o") {
					cout << oct << right << setw(formatWidth) << intIO << endl;
					isInt = 1;
				}
			}
		}
		
		if (!isInt) {
			istringstream floatInputStream(inputLine);
			if (floatInputStream >> inputSpecification >> floatIO) {
				istringstream floatInputStreamSpec(inputSpecification);
				if(floatInputStreamSpec >> formatWidth >> checkDecimal >> floatPrecision >> floatExp)
					if(checkDecimal == '.') {
						if(floatExp == "e") {
							cout << scientific << setprecision(floatPrecision)
							<< right << setw(formatWidth) << floatIO << endl;
						}
						if(floatExp == "f") {
							cout << fixed << setprecision(floatPrecision)
							<< right << setw(formatWidth) << floatIO << endl;
						}
					}
			}
		}
	}
	return 0;
}
