/*
 *  tagStack.h
 *  Assignment #1
 *
 *  Created by Steffen L. Norgren on 28/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#ifndef __STACK_H__
#define __STACK_H__

class Stack {
private:
	struct node_ {
		std::string data;
		node_ *next;
		node_(std::string d): data(d), next(0){}
	};
	node_ *top_;
public:
	Stack();
	void push(std::string s);
	void pop();
	bool empty() const;
	std::string top() const;
};

#endif

