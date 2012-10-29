/*
 *  tagStack.cpp
 *  Assignment #1
 *
 *  Created by Steffen L. Norgren on 28/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

#include "main.h"
#include "tagStack.h"

using namespace std;

Stack::Stack():top_(0) {
}

void Stack::push(string s) {
    node_ *p = new node_(s);
    p->next = top_;
    top_ = p;
}

void Stack::pop() {
    node_ *p = top_;
    top_ = p->next;
    delete p;
}

bool Stack::empty() const {
    return top_ == 0;
}

string Stack::top() const {
    return top_->data;
}

