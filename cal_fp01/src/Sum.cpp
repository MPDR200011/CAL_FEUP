/*
 * Sum.cpp
 */

#include "Sum.h"
#include <chrono>
#include <sstream>
#include <climits>

string calcSum(int* sequence, int size) {

  unsigned int min[size + 1];
  std::fill_n(min, size+1, UINT_MAX);
  unsigned int ind[size + 1];

  for (int i = 0; i < size; i++) {
    for (int m = 1; m <= i+1; m++) {
      unsigned int sum = 0;
      for (int j = i; j > i-m; j--) {
	sum += sequence[j];
      }
      if (sum < min[m]) {
	min[m] = sum;
	ind[m] = i-m+1;
      }
    }
  }

  stringstream ss;

  for (int m = 1; m <= size; m++) {
    ss << min[m] << "," << ind[m] << ";";
  }

  return ss.str();
}

