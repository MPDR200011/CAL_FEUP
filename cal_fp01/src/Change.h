/*
 * Change.h
 */

#ifndef CHANGE_H_
#define CHANGE_H_

#include "Defs.h"

/* Calcula o troco num determinado montante m, utilizando um número mínimo
 * de moedas de valores unitários indicados (coinValues).
 * O array coinValues deve estar ordenado por ordem crescente.
 * O parâmetro numCoins indica o tamanho do array.
 * Devolve:
 * Uma string com a sequência de valores das moedas por valores decrescente.
 * Por exemplo: calcChange(9, 3, {1, 2, 5}) = "5;2;2;"
 * */
string calcChange(int m, int numCoins, int *coinValues);

#endif /* CHANGE_H_ */
