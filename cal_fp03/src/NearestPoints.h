
#ifndef UTIL_H_
#define UTIL_H_

#include "Point.h"

/*
 * Auxiliary class to store a solution.
 */
class Result {
public:
	double dmin; // distance between selected points
	Point p1, p2; // selected points
	Result(double dmin2, Point p1, Point p2);
	Result();
};

// Functions using different algorithms
Result nearestPoints_BF(vector<Point> &vp);
Result nearestPoints_BF_SortByX(vector<Point> &vp);
Result nearestPoints_DC(vector<Point> &vp);
Result nearestPoints_DC_MT(vector<Point> &vp);
void setNumThreads(int num);

// Pointer to function that computes nearest points
typedef Result (*NP_FUNC)(vector<Point> &vp);



#endif
