#include <iostream>
#include "Stack.h"

int main () {
	Stack<int> s1;
	
	for (int i=1; i < SIZE + 4; i++) {
		if(!s1.full()) {
			s1.push(i);
			std::cout << i << " has been pushed into the stack." << std::endl;
		}
		else {
			std::cout << "Sadly the stack is full..." << std::endl;
		}
	}
	
	Stack<int> s2(s1); // calls copy ctor
	
	s1.printPopStack();
	s2.printPopStack();
}