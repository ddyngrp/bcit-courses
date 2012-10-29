#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H

// Headers
#include <iostream>
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

class ShapeFactory {
	public:
		explicit ShapeFactory(std::istream& in): in_(in) {}

		// refer to lecture; see writeup for brief description
		Shape* create();

	private:
		std::istream&  in_;
};
#endif
