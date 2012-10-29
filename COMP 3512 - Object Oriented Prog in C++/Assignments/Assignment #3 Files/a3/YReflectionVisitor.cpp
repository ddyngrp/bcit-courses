/*
 * YReflectionVisitor.cpp
 * 
 * Assignment #3
 *
 * Created by Steffen L. Norgren on 2008-12-01
 * Copyright 2008 Esurient Systems Inc. All rights reserved.
 *
 */

#include "YReflectionVisitor.h"

void YReflectionVisitor::visitCircle(Circle *s) {
	int newCentre;

	Point oldCentre = s->getCentre();
	newCentre = oldCentre.getX() * -1;
	oldCentre.setX(newCentre);

	s->setCentre(oldCentre);
}

void YReflectionVisitor::visitRectangle(Rectangle *s) {
	int x0, x1;
	
	Point oldP0 = s->getVertex(0);
	Point oldP1 = s->getVertex(1);

	x0 = oldP0.getX() * -1;
	x1 = oldP1.getX() * -1;

	oldP0.setX(x0);
	oldP1.setX(x1);

	s->setVertex(0, oldP0);
	s->setVertex(1, oldP1);
}

void YReflectionVisitor::visitTriangle(Triangle *s) {
	int x0, x1, x2;
	
	Point oldP0 = s->getVertex(0);
	Point oldP1 = s->getVertex(1);
	Point oldP2 = s->getVertex(2);

	x0 = oldP0.getX() * -1;
	x1 = oldP1.getX() * -1;
	x2 = oldP2.getX() * -1;

	oldP0.setX(x0);
	oldP1.setX(x1);
	oldP2.setX(x2);

	s->setVertex(0, oldP0);
	s->setVertex(1, oldP1);
	s->setVertex(2, oldP2);
}
