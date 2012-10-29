/*
 * Rectangle.cpp
 * Assignment #3
 *
 * Created by Steffen L. Norgren on 2008-12-01
 * Copyright 2008 Esurient Systems Inc. All rights reserved.
 *
 */

#include "Rectangle.h"

using namespace std;

Rectangle::Rectangle(istream& is) {
	if (!(is >> p0_ >> p1_)) {
		throw 42;
	}
}

void Rectangle::draw() const {
	cout << "[R: " << p0_ << ", " << p1_ << "]" << endl;
}

void Rectangle::save(ostream& os) const {
	os << "rectangle" << endl;
	os << p0_ << endl;
	os << p1_ << endl;
} 

void Rectangle::accept(ShapeVisitor& v) {
	v.visitRectangle(this);
}
