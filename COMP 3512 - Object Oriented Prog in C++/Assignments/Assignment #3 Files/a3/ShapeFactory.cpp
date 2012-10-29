/*
 * ShapeFactory.cpp
 * Assignment #3
 *
 * Created by Steffen L. Norgren on 2008-12-01
 * Copyright 2008 Esurient Systems Inc. All rights reserved.
 *
 */

#include <string>
#include "ShapeFactory.h"

using namespace std;

Shape* ShapeFactory::create() {
	string type;

	try {
		if (!(in_>>type)) {
			return 0;
		}
		if (type == "circle") {
			return new Circle(in_);
		}
		if (type == "rectangle") {
			return new Rectangle(in_);
		}
		if (type == "triangle") {
			return new Triangle(in_);
		}
	}
	catch (int i) {
		return 0;
	}
	return 0;
}
