/*
 * Sudoku.cpp
 *
 */

#include "Sudoku.h"

/** Inicia um Sudoku vazio.
 */
Sudoku::Sudoku() {
    this->initialize();
}

/**
 * Inicia um Sudoku com um conteúdo inicial.
 * Lança excepção IllegalArgumentException se os valores
 * estiverem fora da gama de 1 a 9 ou se existirem números repetidos
 * por linha, coluna ou bloc 3x3.
 *
 * @param nums matriz com os valores iniciais (0 significa por preencher)
 */
Sudoku::Sudoku(int nums[9][9]) {
    this->initialize();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (nums[i][j] != 0) {
                int n = nums[i][j];
                numbers[i][j] = n;
                lineHasNumber[i][n] = true;
                columnHasNumber[j][n] = true;
                block3x3HasNumber[i / 3][j / 3][n] = true;
                countFilled++;
            }
        }
    }
}

void Sudoku::initialize() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int n = 0; n < 10; n++) {
                numbers[i][j] = 0;
                lineHasNumber[i][n] = false;
                columnHasNumber[j][n] = false;
                block3x3HasNumber[i / 3][j / 3][n] = false;
            }
        }
    }

    this->countFilled = 0;
}

/**
 * Obtem o conteúdo actual (só para leitura!).
 */
int** Sudoku::getNumbers() {
    int** ret = new int*[9];

    for (int i = 0; i < 9; i++) {
        ret[i] = new int[9];

        for (int a = 0; a < 9; a++)
            ret[i][a] = numbers[i][a];
    }

    return ret;
}

/**
 * Verifica se o Sudoku já está completamente resolvido
 */
bool Sudoku::isComplete() {
    return countFilled == 9 * 9;
}

Cell Sudoku::getCellWithLessCandidates() {
    // cout << "Getting cell" << endl;
    Cell minCell;
    minCell.numCand = 10;
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            if (numbers[y][x] == 0) {
                auto cand = getCandidates(x, y);
                if (cand.size() < minCell.numCand) {
                    minCell.x = x;
                    minCell.y = y;
                    minCell.numCand = cand.size();
                    minCell.candidates = cand;
                }
            }
        }
    }
    if (minCell.numCand == 10) {
        minCell.y = -1;
    }
    return minCell;
}

set<int> Sudoku::getCandidates(int x, int y) {
    // cout << "Getting candidates" << endl;
    set<int> candidates;

    bool available[10];
    std::fill_n(available, 10, true);
    for (int n = 1; n < 10; n++) {
        if (columnHasNumber[x][n]) {
            available[n] = false;
        }
        if (lineHasNumber[y][n]) {
            available[n] = false;
        }
        if (block3x3HasNumber[y / 3][x / 3][n]) {
            available[n] = false;
        }
    }

    for (int n = 1; n < 10; n++) {
        if (available[n]) {
            candidates.insert(n);
        }
    }

    return candidates;
}

/**
 * Resolve o Sudoku.
 * Retorna indicação de sucesso ou insucesso (sudoku impossível).
 */
bool Sudoku::solve() {
    if (isComplete()) {
        return true;
    }

    Cell cell = getCellWithLessCandidates();

    // cout << "Got cell: " << y << " " << x << endl;
    for (int n : cell.candidates) {
        numbers[cell.y][cell.x] = n;
        countFilled++;
        columnHasNumber[cell.x][n] = true;
        lineHasNumber[cell.y][n] = true;
        block3x3HasNumber[cell.y / 3][cell.x / 3][n] = true;
        if (solve()) {
            return true;
        }
        numbers[cell.y][cell.x] = 0;
        countFilled--;
        columnHasNumber[cell.x][n] = false;
        lineHasNumber[cell.y][n] = false;
        block3x3HasNumber[cell.y / 3][cell.x / 3][n] = false;
    }

    return false;
}

/**
 * Imprime o Sudoku.
 */
void Sudoku::print() {
    for (int i = 0; i < 9; i++) {
        for (int a = 0; a < 9; a++) {
            cout << this->numbers[i][a] << " ";
        }
        cout << endl;
    }
}
