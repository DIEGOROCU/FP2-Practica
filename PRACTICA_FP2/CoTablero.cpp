// 1ºDG FP2 - Diego Rodriguez Cubero.

#include "CoTablero.h"

// Constructor por defecto del tablero
Tablero::Tablero() {
    filas = 0;
	columnas = 0;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			celdas[i][j] = NULA;
		}
	}
}

// Constructor con parámetros del tablero
Tablero::Tablero(const int& fils, const int& cols, Celda inicial){
	filas = fils;
	columnas = cols;

	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++) {
			celdas[i][j] = inicial;
		}
	}
}

// Devuelve el número de filas del tablero
int Tablero::num_filas() const {
	return filas;
}

// Devuelve el número de columnas del tablero
int Tablero::num_columnas() const {
	return columnas;
}

// Comprueba si una celda esta dentro del tablero
bool Tablero::correcta(int f, int c) const {
	return !(f < 0 || f >= filas || c < 0 || c >= columnas);
}

// Devuelve el valor de una celda (tipo Celda) del tablero
Celda Tablero::leer(int f, int c) const {
	return celdas[f][c];
}

// Fija el valor de una celda (tipo Celda) del tablero
void Tablero::escribir(int f, int c, Celda valor) {
	celdas[f][c] = valor;
}