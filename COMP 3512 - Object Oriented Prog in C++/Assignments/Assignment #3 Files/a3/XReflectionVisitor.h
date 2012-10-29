#ifndef XREFLECTIONVISITOR_H
#define XREFLECTIONVISITOR_H

// Headers
#include "ShapeVisitor.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

class XReflectionVisitor: public ShapeVisitor {
	public:
		virtual ~XReflectionVisitor() {}  

		// provide implementation for the following in CPP file
		// implementation should reflect the shape about the x-axis
		virtual void visitCircle(Circle *s);
		virtual void visitRectangle(Rectangle *s);
		virtual void visitTriangle(Triangle *s);
};
#endif
