// Stack.h

#define SIZE 10

template <typename T> class Stack {
private:
	int top_;
	T stackArray[SIZE];
	
public:
	Stack() { // default constructor
		top_ = -1;
	}
	
	void push (T n) {
		stackArray[top_+1] = n;
		top_++;
	}
	
	void pop() {
		top_--;
	}
	
	bool empty() const {
		return top_ == -1;
	}
	
	bool full() const {
		return top_ == SIZE - 1;
	}
	
	/* precontition: !empty() */
	T top() const {
		return stackArray[top_];
	}
	
	void printPopStack() const {
		std::cout << "\nThe contents of the stack are:" << std::endl;
		if(!empty()) {
			while (!empty()) {
				std::cout << top() << std::endl;
				pop();
			}
		}
		else {
			std::cout << "NULL" << std::endl;
		}
	}
	
	Stack& operator = (const Stack& src) {
		Stack temp(src);
		return *this;
	}	
};