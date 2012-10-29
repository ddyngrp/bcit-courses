/*
 * TranslationVisitor.cpp
 * Assignment #3
 *
 * Created by Steffen L. Norgren on 2008-12-01
 * Copyright 2008 Esurient Systems Inc. All rights reserved.
 *
 */

#include "TranslationVisitor.h"

void TranslationVisitor::visitCircle(Circle *s) {
	Point newCentre = s->getCentre();

	newCentre += d_;

	s->setCentre(newCentre);
}

void TranslationVisitor::visitRectangle(Rectangle *s) {
	Point p0 = s->getVertex(0);
	Point p1 = s->getVertex(1);

	p0 += d_;
	p1 += d_;

	s->setVertex(0, p0);
	s->setVertex(1, p1);
}

void TranslationVisitor::visitTriangle(Triangle *s) {
	Point p0 = s->getVertex(0);
	Point p1 = s->getVertex(1);
	Point p2 = s->getVertex(2);

	p0 += d_;
	p1 += d_;
	p2 += d_;

	s->setVertex(0, p0);
	s->setVertex(1, p1);
	s->setVertex(2, p2);
}
