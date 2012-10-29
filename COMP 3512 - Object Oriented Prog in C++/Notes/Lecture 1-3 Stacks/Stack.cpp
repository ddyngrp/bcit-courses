#include <iostream>
#include "Stack.h"

int main () {
	Stack<int> s1;
	
	for (int i=1; i < 20; i++) {
		s1.push(i);
	}
	
	Stack<int> s2(s1); // calls copy ctor
	
	while (!s1.empty()) {
		std::cout << s1.top() << std::endl;
		s1.pop();
	}
}