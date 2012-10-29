#ifndef TRANSLATIONVISITOR_H
#define TRANSLATIONVISITOR_H

// Headers
#include "ShapeVisitor.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

class TranslationVisitor: public ShapeVisitor {
	public:
		explicit TranslationVisitor(const Point& d = Point(0,0)): d_(d) {}
		virtual ~TranslationVisitor() {}  

		Point getDisplacement() const { return d_; }
		void  setDisplacement(const Point& d) { d_ = d; }

		// provide implementation for the following in CPP file
		// implementation should translate the shape by the displacement d_
		virtual void visitCircle(Circle *s);
		virtual void visitRectangle(Rectangle *s);
		virtual void visitTriangle(Triangle *s);
	private:
		Point  d_;  // the displacement
};
#endif
