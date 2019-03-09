/*
 * Change.cpp
 */

#include "Change.h"
#include <sstream>

string calcChange(int m, int numCoins, int* coinValues) {
    if (m < 1) {
        return "";
    }
    if (m < coinValues[0]) {
        return "-";
    }

    int minCoins[m + 1]={0};
    int lastCoin[m + 1]={0};

    for (int i = 0; i < numCoins; i++) {
        for (int k = coinValues[i]; k <= m; k++) {
            if ((minCoins[k - coinValues[i]] + 1) < minCoins[k] ||
                minCoins[k] == 0) {
                minCoins[k] = minCoins[k - coinValues[i]] + 1;
                lastCoin[k] = coinValues[i];
            }
        }
    }

    stringstream ss;

    int M = m;
    for (int j = 0; j < minCoins[m]; j++) {
        ss << lastCoin[M] << ";";
        M -= lastCoin[M];
    }

    return ss.str();
}

