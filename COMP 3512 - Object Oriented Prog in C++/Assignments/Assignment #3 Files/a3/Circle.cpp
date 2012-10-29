/*
 * Circle.cpp
 * Assignment #3
 *
 * Created by Steffen L. Norgren on 2008-12-01
 * Copyright 2008 Esurient Systems Inc. All rights reserved.
 *
 */

#include "Circle.h"

using namespace std;

Circle::Circle(istream& is) {
	if (!(is >> centre_ >> radius_)) {
		throw 42;
	}
}

void Circle::draw() const {
	cout << "[C: " << centre_ << ", " << radius_ << "]" << endl;
}

void Circle::save(ostream& os) const {
	os << "circle" << endl;
	os << centre_ << endl;
	os << radius_ << endl;
} 

void Circle::accept(ShapeVisitor& v) {
	v.visitCircle(this);
}
