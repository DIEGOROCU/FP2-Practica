// 1ºDG FP2 - Diego Rodriguez Cubero.

#include "CoColores.h"
#include <iomanip>

using namespace std;

// Funcion que convierte un color a string (sin terminar)
std::string to_stringColor(std::string color) {

	if (color == "\x1B[30m") return "NEGRO";
	else if (color == "\x1B[38;2;255;0;0m") return "ROJO";
	else if (color == "\x1b[32m") return "VERDE";

}

// Funcion que pinta la cabecera del tablero
void pinta_cabecera(Tablero tablero) {
	cout << setw(2) << "    "; // margen inicial
	cout << setw(5) << 1;
	for (int i = 2; i <= tablero.num_columnas(); i++) {
		cout << setw(7) << i;
	}
	cout << endl;
}

// Funcion que pinta una linea del tablero
void pinta_linea(char esquinaIzda, char cruce, char esquinaDer, Tablero tablero) {
	cout << "    "; // margen inicial
	cout << esquinaIzda;
	for (int i = 0; i < tablero.num_columnas() - 1; i++) {
		cout << string(6, char(196)) << cruce;
	}
	cout << string(6, char(196)) << esquinaDer << endl;
}

// Funcion que pinta el borde de una celda del tablero
void pinta_borde_celda(int fila, Tablero tablero) {
	cout << "    "; // margen inicial
	for (int k = 0; k < tablero.num_columnas(); k++) { // cada columna
		cout << char(179);
		color_fondo(tablero.leer(fila, k));
		cout << "      ";
		color_fondo(DEFAULT);
	}
	cout << char(179) << endl; // lateral derecho
}

// Funcion que pinta el centro de una celda del tablero
void pinta_centro_celda(int fila, Tablero tablero, int f_meta, int c_meta) {
	cout << "  " << setw(2) << fila + 1; // margen inicial
	for (int k = 0; k < tablero.num_columnas(); k++) { // cada columna
		cout << char(179);
		// el color de fondo depende del contenido
		color_fondo(tablero.leer(fila, k));

		if (fila == f_meta && k == c_meta) { // meta
			cout << YELLOW;
			cout << "  " << char(219) << char(219) << "  ";
		}
		else {
			cout << "      ";
		}
		color_fondo(DEFAULT);
	}
	cout << char(179) << endl; // lateral derecho
}

// Funcion que pinta el color de fondo de una celda
void color_fondo(Celda color) {
	if (color == DEFAULT)
		cout << RESET;
	else if (color == NULA)
		cout << BG_BLACK;
	else if (color == FICHA)
		cout << BG_GREEN;
	else // color == VACIA
		cout << BG_GRAY;
}