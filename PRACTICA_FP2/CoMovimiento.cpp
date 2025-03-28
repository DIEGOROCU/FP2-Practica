// 1�DG FP2 - Diego Rodriguez Cubero.

#include "CoMovimiento.h"

// Devuelve un string con el nombre de la direcci�n
std::string to_string(Direccion d) {
	if (d == ARRIBA) {
		return "ARRIBA";
	}
	else if (d == ABAJO) {
		return "ABAJO";
	}
	else if (d == IZQUIERDA) {
		return "IZQUIERDA";
	}
	else if (d == DERECHA) {
		return "DERECHA";
	}
	else if (d == INDETERMINADA) {
		return "INDETERMINADA";
	}
}

// Constructor con par�metros de la clase Movimiento
Movimiento::Movimiento(int f, int c): fil(f), col(c), cont(0), activa(INDETERMINADA) {
	for (int i = 0; i < NUMDIR; i++) {
		direcciones[i] = INDETERMINADA;
	}
}

// Devuelve la fila del movimiento
int Movimiento::fila() const {
	return fil;
}

// Devuelve la columna del movimiento
int Movimiento::columna() const {
	return col;
}

// Devuelve la direcci�n activa del movimiento
Direccion Movimiento::dir_activa() const {
	return activa;
}

// Fija la direcci�n activa del movimiento
void Movimiento::fijar_dir_activa(Direccion d) {
	activa = d;
}

// Inserta una direcci�n en la lista de direcciones
void Movimiento::insertar_dir(Direccion d) {
	direcciones[cont] = d;
	cont++;
}

// Devuelve el n�mero de direcciones posibles
int Movimiento::num_dirs() const {
	return cont;
}

// Devuelve la direcci�n en la posici�n i de la lista de direcciones
Direccion Movimiento::direccion(int i) const {
	return direcciones[i];
}

