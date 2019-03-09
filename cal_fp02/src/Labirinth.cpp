/*
 * labirinth.cpp
 */

#include "Labirinth.h"

#include <iostream>
using namespace std;

Labirinth::Labirinth(int values[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            labirinth[i][j] = values[i][j];
}

void Labirinth::initializeVisited() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            visited[i][j] = false;
}

void Labirinth::printLabirinth() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            cout << labirinth[i][j] << " ";

        cout << endl;
    }
}

bool Labirinth::findGoal(int x, int y) {
    if (x == 1 && y == 1) {
        initializeVisited();
    }

    if (visited[y][x]) {
        return false;
    }

    if (labirinth[y][x] == 2) {
        return true;
    }

    visited[y][x] = true;
    if (labirinth[y][x - 1] != 0 && !visited[y][x - 1]) {
        if (findGoal(x - 1, y)) {
            return true;
        }
    }
    if (labirinth[y][x + 1] != 0 && !visited[y][x + 1]) {
        if (findGoal(x + 1, y)) {
            return true;
        }
    }
    if (labirinth[y + 1][x] != 0 && !visited[y + 1][x]) {
        if (findGoal(x, y + 1)) {
            return true;
        }
    }
    if (labirinth[y - 1][x] != 0 && !visited[y - 1][x]) {
        if (findGoal(x, y - 1)) {
            return true;
        }
    }
    return false;
}

