#include "cute/cute.h"
#include "cute/cute_runner.h"
#include "cute/ide_listener.h"
#include "cute/xml_listener.h"

#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>
#include <fstream>
#include <random>
#include "NearestPoints.h"
#include "Point.h"
using namespace std;

/**
 * Auxiliary function to read points from file to vector.
 */
void readPoints(string in, vector<Point>& vp) {
    ifstream is(in.c_str());
    vp.clear();
    if (!is)
        return;
    while (!is.eof()) {
        double x, y;
        is >> x >> y;
        Point p(x, y);
        vp.push_back(p);
    }
}

/**
 * Auxiliary functions to generate random sets of points.
 */

void shuffle(vector<Point>& vp, int left, int right) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, right - left + 1);
    for (int i = left; i < right; i++) {
        int k = i + dis(gen) % (right - i + 1);
        Point tmp = vp[i];
        vp[i] = vp[k];
        vp[k] = tmp;
    }
}

void shuffleY(vector<Point>& vp, int left, int right) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, right - left + 1);
    for (int i = left; i < right; i++) {
        int k = i + dis(gen) % (right - i + 1);
        double tmp = vp[i].y;
        vp[i].y = vp[k].y;
        vp[k].y = tmp;
    }
}

// Generates a vector of n distinct points with minimum distance 1.
void generateRandom(int n, vector<Point>& vp) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n - 1);

    vp.clear();
    // reference value for reference points (r, r), (r, r+1)
    int r = dis(gen);
    vp.push_back(Point(r, r));
    vp.push_back(Point(r, r + 1));
    for (int i = 2; i < n; i++)
        if (i < r)
            vp.push_back(Point(i, i));
        else
            vp.push_back(Point(i + 1, i + 2));
    shuffleY(vp, 2, n - 1);
    shuffle(vp, 0, n - 1);
}

// Similar, but with constant X.
void generateRandomConstX(int n, vector<Point>& vp) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, n - 1);

    vp.clear();
    // reference value for min dist
    int r = dis(gen);
    int y = 0;
    for (int i = 0; i < n; i++) {
        vp.push_back(Point(0, y));
        if (i == r)
            y++;
        else
            y += 1 + dis(gen) % 100;
    }
    shuffleY(vp, 0, n - 1);
}

/**
 * Auxiliary functions to obtain current time and time elapsed
 * in milliseconds.
 * Something like GetTickCount but portable.
 * It rolls over every ~ 12.1 days (0x100000/24/60/60)
 * Use GetMilliSpan to correct for rollover
 */

int GetMilliCount() {
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
    return nCount;
}

int GetMilliSpan(int nTimeStart) {
    int nSpan = GetMilliCount() - nTimeStart;
    if (nSpan < 0)
        nSpan += 0x100000 * 1000;
    return nSpan;
}

int testNP(string name,
           vector<Point>& pontos,
           double dmin,
           NP_FUNC func,
           string alg) {
    int nTimeStart = GetMilliCount();
    Result res = (func)(pontos);
    int nTimeElapsed = GetMilliSpan(nTimeStart);
    cout << alg << "; " << name << "; " << nTimeElapsed << "; ";
    cout.precision(17);
    cout << res.dmin << "; " << res.p1 << "; " << res.p2 << endl;
    ASSERT_EQUAL_DELTA(dmin, res.dmin, 0.01);
    return nTimeElapsed;
}

/**
 * Runs the given algorithm (func) for an input file (in)
 * and checks the expected result (res).
 * Prints result and performance information.
 */
int testNPFile(string in, double dmin, NP_FUNC func, string alg) {
    vector<Point> pontos;
    readPoints(in, pontos);
    return testNP(in, pontos, dmin, func, alg);
}

int testNPRand(int size, string name, double dmin, NP_FUNC func, string alg) {
    vector<Point> pontos;
    generateRandom(size, pontos);
    return testNP(name, pontos, dmin, func, alg);
}

int testNPRandConstX(int size,
                     string name,
                     double dmin,
                     NP_FUNC func,
                     string alg) {
    vector<Point> pontos;
    generateRandomConstX(size, pontos);
    return testNP(name, pontos, dmin, func, alg);
}

/**
 * Runs the given algorithm for the existent data files.
 */

void testNearestPoints(NP_FUNC func, string alg) {
    cout << "algorithm; data set; time elapsed (ms); distance; point1; point2"
         << endl;
    int maxTime = 10000;
    if (testNPFile("Pontos8", 11841.3, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos64", 556.066, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos1k", 100.603, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos16k", 13.0384, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos32k", 1.0, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos64k", 1.0, func, alg) > maxTime)
        return;
    if (testNPFile("Pontos128k", 0.0, func, alg) > maxTime)
        return;
    if (testNPRand(0x40000, "Pontos256k", 1.0, func, alg) > maxTime)
        return;
    if (testNPRand(0x80000, "Pontos512k", 1.0, func, alg) > maxTime)
        return;
    if (testNPRand(0x100000, "Pontos1M", 1.0, func, alg) > maxTime)
        return;
    if (testNPRand(0x200000, "Pontos2M", 1.0, func, alg) > maxTime)
        return;
    if (testNPRandConstX(0x8000, "Pontos32kConstX", 1.0, func, alg) > maxTime)
        return;
    if (testNPRandConstX(0x10000, "Pontos64kConstX", 1.0, func, alg) > maxTime)
        return;
    if (testNPRandConstX(0x20000, "Pontos128kConstX", 1.0, func, alg) > maxTime)
        return;
    if (testNPRandConstX(0x40000, "Pontos256kConstX", 1.0, func, alg) > maxTime)
        return;
    if (testNPRandConstX(0x80000, "Pontos512kConstX", 1.0, func, alg) > maxTime)
        return;
    if (testNPRandConstX(0x100000, "Pontos1MConstX", 1.0, func, alg) > maxTime)
        return;
    if (testNPRandConstX(0x200000, "Pontos2MConstX", 1.0, func, alg) > maxTime)
        return;
}

void testNP_BF() {
    testNearestPoints(nearestPoints_BF, "Brute force");
}

void testNP_BF_SortedX() {
    testNearestPoints(nearestPoints_BF_SortByX, "Brute force, sorted by x");
}

void testNP_DC() {
    testNearestPoints(nearestPoints_DC, "Divide and conquer");
}

void testNP_DC_2Threads() {
    setNumThreads(2);
    testNearestPoints(nearestPoints_DC_MT, "Divide and conquer with 2 threads");
}

void testNP_DC_4Threads() {
    setNumThreads(4);
    testNearestPoints(nearestPoints_DC_MT, "Divide and conquer with 4 threads");
}

void testNP_DC_8Threads() {
    setNumThreads(8);
    testNearestPoints(nearestPoints_DC_MT, "Divide and conquer with 8 threads");
}

bool runAllTests(int argc, char const* argv[]) {
    cute::suite s{};
    // s.push_back(CUTE(testNP_BF));
    s.push_back(CUTE(testNP_DC));
    s.push_back(CUTE(testNP_DC_2Threads));
    s.push_back(CUTE(testNP_DC_4Threads));
    s.push_back(CUTE(testNP_DC_8Threads));
    s.push_back(CUTE(testNP_BF_SortedX));
    cute::xml_file_opener xmlfile(argc, argv);
    cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
    auto runner = cute::makeRunner(lis, argc, argv);
    bool success = runner(s, "AllTests");
    return success;
}

int main(int argc, char const* argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
