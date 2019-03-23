/*
 * Point.cpp
 *
 *  Created on: 4 de Mar de 2011
 *      Author: ap
 */

#include "Point.h"

#include <cmath>

Point::Point() {
	// TODO Auto-generated constructor stub
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

Point::Point(double x, double y) {
	this->x = x;
	this->y = y;
}

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

double Point::distance(Point &p) {
	return sqrt((x-p.x) * (x-p.x)  + (y-p.y) * (y-p.y));
}

double Point::distSquare(Point &p) {
	return (x-p.x) * (x-p.x)  + (y-p.y) * (y-p.y);
}

bool Point::operator==(const Point &p) const {
	return (x == p.x && y == p.y);
}

ostream& operator<<(ostream& os, Point &p) {
	os << "(" << p.x << "," << p.y << ")";
	return os;
}

