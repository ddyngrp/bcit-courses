#ifndef TRIANGLE_H
#define TRIANGLE_H

// Headers
#include <iostream>
#include "Shape.h"
#include "ShapeVisitor.h"
#include "Point.h"

class Triangle: public Shape {
	public:
		// read data for Triangle from 'is'; used by factory
		// should read in data members saved by 'save' (except for the type name)
		// should perform some error-checking (see README)
		explicit Triangle(std::istream& is); 

		// a Triangle consists of 3 vertices
		// 'i' should be 0, 1, or 2; if not, throw an exception
		Point getVertex(int i) const;

		// 'i' should be 0, 1, or 2; if not, throw an exception
		void setVertex(int i, const Point& p); 

		// write to standard output
		// example output:  [T: (5,-6), (7,-8), (2,1)]
		virtual void draw() const; 

		/* example output:
		   triangle
		   (5,-6)
		   (7,-8)
		   (2,1)
		   */
		virtual void save(std::ostream& os = std::cout) const; 

		// accept a visitor
		virtual void accept(ShapeVisitor& v);

	private:
		// provide suitable data structure
		Point p0_;
		Point p1_;
		Point p2_;
};

// provide inline implementation of getVertex & setVertex here
inline Point Triangle::getVertex(int i) const {
		if (i == 0) {
			return p0_;
		}
		else if (i == 1) {
			return p1_;
		}
		else if (i == 2) {
			return p2_;
		}
		else {
			throw 42;
		}
}

inline void Triangle::setVertex(int i, const Point& p) {
		if (i == 0) {
			p0_.setX(p.getX());
			p0_.setY(p.getY());
		}
		else if (i == 1) {
			p1_.setX(p.getX());
			p1_.setY(p.getY());
		}
		else if (i == 2) {
			p2_.setX(p.getX());
			p2_.setY(p.getY());
		}
		else {
			throw 42;
		}
}

// implement the other functions in the CPP file
#endif
