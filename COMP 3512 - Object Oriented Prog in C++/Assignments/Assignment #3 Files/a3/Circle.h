#ifndef CIRCLE_H
#define CIRCLE_H

// Headers
#include <iostream>
#include "Shape.h"
#include "ShapeVisitor.h"
#include "Point.h"

class Circle: public Shape {
	public:
		// read data for circle from 'is'; used by ShapeFactory objects
		// should read in data members saved by 'save' (except for the type name)
		// should perform some error-checking (see README)
		explicit Circle(std::istream& is);

		int   getRadius() const { return radius_; }
		Point getCentre() const { return centre_; }

		void  setRadius(int radius) { radius_ = radius; }
		void  setCentre(const Point& centre) { centre_ = centre; }

		// write to standard output
		// example output:  [C: (1,-2), 3]
		virtual void draw() const; 

		/* example output:
		   circle
		   (1,-2)
		   3
		   */
		virtual void save(std::ostream& os = std::cout) const; 

		// accept a visitor
		virtual void accept(ShapeVisitor& v);

	private:
		Point  centre_;
		int    radius_;
};

// implement functions in CPP file
#endif
