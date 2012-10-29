/*
 * Triangle.cpp
 * 
 * Assignment #3
 *
 * Created by Steffen L. Norgren on 2008-12-01
 * Copyright 2008 Esurient Systems Inc. All rights reserved.
 *
 */

#include "Triangle.h"

using namespace std;

Triangle::Triangle(istream& is) {
	if (!(is >> p0_ >> p1_ >> p2_)) {
		throw 42;
	}
}

void Triangle::draw() const {
	cout << "[T: " << p0_ << ", "<< p1_ << ", " << p2_ << "]" << endl;
}

void Triangle::save(ostream& os) const {
	os << "triangle" << endl;
	os << p0_ << endl;
	os << p1_ << endl;
	os << p2_ << endl;
} 

void Triangle::accept(ShapeVisitor& v) {
	v.visitTriangle(this);
}
