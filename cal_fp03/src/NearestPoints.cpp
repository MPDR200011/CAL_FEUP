/*
 * NearestPoints.cpp
 */

#include "NearestPoints.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <thread>
#include "Point.h"

const double MAX_DOUBLE = std::numeric_limits<double>::max();

Result::Result(double dmin, Point p1, Point p2) {
    this->dmin = dmin;
    this->p1 = p1;
    this->p2 = p2;
}

Result::Result() {
    this->dmin = MAX_DOUBLE;
    this->p1 = Point(0, 0);
    this->p2 = Point(0, 0);
}

/**
 * Auxiliary functions to sort vector of points by X or Y axis.
 */
static void sortByX(vector<Point>& v, int left, int right) {
    std::sort(v.begin() + left, v.begin() + right + 1, [](Point p, Point q) {
        return p.x < q.x || (p.x == q.x && p.y < q.y);
    });
}

static void sortByY(vector<Point>& v, int left, int right) {
    std::sort(v.begin() + left, v.begin() + right + 1, [](Point p, Point q) {
        return p.y < q.y || (p.y == q.y && p.x < q.x);
    });
}

/**
 * Brute force algorithm O(N^2).
 */
Result nearestPoints_BF(vector<Point>& vp) {
    Result res;
    for (size_t i = 0; i < vp.size(); i++) {
        for (size_t j = i + 1; j < vp.size(); j++) {
            if (i == j) {
                continue;
            }
            double distance = vp[i].distance(vp[j]);
            if (distance < res.dmin) {
                res.dmin = distance;
                res.p1 = vp[i];
                res.p2 = vp[j];
            }
        }
    }
    return res;
}

/**
 * Improved brute force algorithm, that first sorts points by X axis.
 */
Result nearestPoints_BF_SortByX(vector<Point>& vp) {
    Result res;
    sortByX(vp, 0, vp.size() - 1);
    // TODO
    return res;
}

/**
 * Auxiliary function to find nearest points in strip, as indicated
 * in the assignment, with points sorted by Y coordinate.
 * The strip is the part of vp between indices left and right (inclusive).
 * "res" contains initially the best solution found so far.
 */
static void npByY(vector<Point>& vp, int left, int right, Result& res) {
    for (int i = left; i < right + 1; i++) {
        for (int j = i + 1; j < right + 1; j++) {
            double dist;
            if (abs(vp[i].y - vp[j].y) > res.dmin) {
                break;
            } else if ((dist = vp[i].distance(vp[j])) < res.dmin) {
                res.dmin = dist;
                res.p1 = vp[i];
                res.p2 = vp[j];
            }
        }
    }
}

/**
 * Recursive divide and conquer algorithm.
 * Finds the nearest points in "vp" between indices left and right (inclusive),
 * using at most numThreads.
 */
static Result np_DC(vector<Point>& vp, int left, int right, int numThreads) {
    // Base case of two points
    if (right - left == 1) {
        return Result(vp[left].distance(vp[right]), vp[left], vp[right]);
    }

    // Base case of a single point: no solution, so distance is MAX_DOUBLE
    if (right - left < 1) {
        return Result();
    }

    // Divide in halves (left and right) and solve them recursively,
    // possibly in parallel (in case numThreads > 1)
    int middle = (left + right) / 2;
    Result leftResult;
    Result rightResult;
    leftResult = np_DC(vp, left, middle, numThreads);
    rightResult = np_DC(vp, middle, right, numThreads);

    // Select the best solution from left and right
    Result best;
    if (leftResult.dmin < rightResult.dmin) {
        best = leftResult;
    } else {
        best = rightResult;
    }

    // Determine the strip area around middle point
    double stripLeft = vp[middle].x - best.dmin;
    double stripRigth = vp[middle].x + best.dmin;

    // Order points in strip area by Y coordinate
    int stripLeftIndex = 0;
    int stripRightIndex = vp.size() - 1;
    int i = 0;
    for (; i < vp.size(); i++) {
        if (vp[i].x >= stripLeft) {
            stripLeftIndex = i;
            break;
        }
    }
    for (; i < vp.size(); i++) {
        if (vp[i].x > stripRigth) {
            stripRightIndex = i - 1;
            break;
        }
    }
    sortByY(vp, stripLeftIndex, stripRightIndex);

    // Calculate nearest points in strip area (using npByY function)
    npByY(vp, stripLeftIndex, stripRightIndex, best);

    // Reorder points in strip area back by X coordinate
    sortByX(vp, stripLeftIndex, stripRightIndex);

    // return res;
    return best;
}

/**
 * Defines the number of threads to be used.
 */
static int numThreads = 1;
void setNumThreads(int num) {
    numThreads = num;
}

/*
 * Divide and conquer approach, single-threaded version.
 */
Result nearestPoints_DC(vector<Point>& vp) {
    sortByX(vp, 0, vp.size() - 1);
    return np_DC(vp, 0, vp.size() - 1, 1);
}

/*
 * Multi-threaded version, using the number of threads specified
 * by setNumThreads().
 */
Result nearestPoints_DC_MT(vector<Point>& vp) {
    sortByX(vp, 0, vp.size() - 1);
    return np_DC(vp, 0, vp.size() - 1, numThreads);
}
