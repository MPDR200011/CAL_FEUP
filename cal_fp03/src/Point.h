/*
 * Point.h
 */

#ifndef POINT_H_
#define POINT_H_

#include <iostream>
#include <vector>

using namespace std;

class Point {
public:
	double x;
	double y;

	Point();
	Point(double x, double y);
	Point(int x, int y);
	double distance(Point &p);
	double distSquare(Point &p); // distance squared
	virtual ~Point();
	bool operator==(const Point &p) const;
};
ostream& operator<<(ostream& os, Point &p);


#endif /* POINT_H_ */
