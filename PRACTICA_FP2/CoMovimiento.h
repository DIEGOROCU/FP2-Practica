// 1�DG FP2 - Diego Rodriguez Cubero.

#pragma once

#include <string>

enum Direccion { ARRIBA, ABAJO, IZQUIERDA, DERECHA, INDETERMINADA };
std::string to_string(Direccion d);

// n�mero de direcciones a considerar
const int NUMDIR = 4;
// vectores de direcci�n: {dif. fila, dif. columna }
const std::pair<int, int> dirs[NUMDIR] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

class Movimiento {
public:
	// Funciones para los movimientos
	Movimiento(int f, int c);
	int fila() const;
	int columna() const;
	Direccion dir_activa() const;
	void fijar_dir_activa(Direccion d);
	void insertar_dir(Direccion d);
	int num_dirs() const;
	Direccion direccion(int i) const;
	
private:
	
	Direccion activa; // de todas las direcciones posibles, contiene la direcci�n
	// activa, i.e., la direcci�n que se va a ejecutar
	int cont; // n�mero de direcciones a las que se puede mover
	Direccion direcciones[NUMDIR]; // direcciones a las que se puede mover

	// Variables de la clase
	int fil;
	int col;

};
