// Stack.h

template <typename T> class Stack {
private:
	struct Node_ {
		T data;
		Node_ *next;
		Node_(T d):data(d),next(0){};
	};
	Node_ *top_;
	
	void destroy() {
		Node_ *p, *q;
		for (p = top_; p != 0; p = q) {
			q = p->next;
			delete p;
		}
	}
	
	void prepend(Node_ *top) {
		if (top != 0) {
			prepend(top->next);
			push(top->data);
		}
	}
	
public:
	Stack():top_(0){} //initializes top_ to 0 (null pointer), default constructor
	void push (T n) {
		Node_ *p = new Node_(n);
		p->next = top_;
		top_ = p;
	}
	
	void pop() {
		Node_ *p = top_;
		top_ = p->next;
		delete p;
	}
	
	bool empty() const { // const means method doesn’t change the object (the stack)
		return top_ == 0;
	}
	
	/* precontition: !empty() */
	T top() const {
		return top_->data;
	}
	
	/* copy constructor - called when copy is made */
	Stack(const Stack& src):top_(0) {
		prepend(src.top_);
	}
	
	Stack& operator = (const Stack& src) {
		Stack temp(src);
		std::swap(top_, temp.top_);
		return *this;
	}
	
	~Stack() { // destructor
		destroy();
	}
};