/*
 * XReflectionVisitor.cpp
 * 
 * Assignment #3
 *
 * Created by Steffen L. Norgren on 2008-12-01
 * Copyright 2008 Esurient Systems Inc. All rights reserved.
 *
 */

#include "XReflectionVisitor.h"

void XReflectionVisitor::visitCircle(Circle *s) {
	int newCentre;

	Point oldCentre = s->getCentre();
	newCentre = oldCentre.getY() * -1;
	oldCentre.setY(newCentre);

	s->setCentre(oldCentre);
}

void XReflectionVisitor::visitRectangle(Rectangle *s) {
	int y0, y1;
	
	Point oldP0 = s->getVertex(0);
	Point oldP1 = s->getVertex(1);

	y0 = oldP0.getY() * -1;
	y1 = oldP1.getY() * -1;

	oldP0.setY(y0);
	oldP1.setY(y1);

	s->setVertex(0, oldP0);
	s->setVertex(1, oldP1);
}

void XReflectionVisitor::visitTriangle(Triangle *s) {
	int y0, y1, y2;
	
	Point oldP0 = s->getVertex(0);
	Point oldP1 = s->getVertex(1);
	Point oldP2 = s->getVertex(2);

	y0 = oldP0.getY() * -1;
	y1 = oldP1.getY() * -1;
	y2 = oldP2.getY() * -1;

	oldP0.setY(y0);
	oldP1.setY(y1);
	oldP2.setY(y2);

	s->setVertex(0, oldP0);
	s->setVertex(1, oldP1);
	s->setVertex(2, oldP2);
}
