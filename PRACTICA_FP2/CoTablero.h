// 1ºDG FP2 - Diego Rodriguez Cubero.

#pragma once

#include <iostream>
#include <fstream>

// Enumerado de las celdas del tablero
enum Celda { NULA, VACIA, FICHA, DEFAULT };

const int MAXDIM = 10;
class Tablero {
public:

	// Funciones del tablero
	Tablero();
	Tablero(const int& fils, const int& cols, Celda inicial);
	int num_filas() const;
	int num_columnas() const;
	bool correcta(int f, int c) const;
	Celda leer(int f, int c) const;
	void escribir(int f, int c, Celda valor);

private:

	// Variables del tablero
	int filas, columnas;
	Celda celdas[MAXDIM][MAXDIM];
};
