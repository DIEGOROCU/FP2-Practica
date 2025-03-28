// 1ºDG FP2 - Diego Rodriguez Cubero.

#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>

#include "CoColores.h"

struct tFicha {
	int f;
	int c;
};

enum Estado { JUGANDO, GANADOR, BLOQUEO};

class Juego {
public:
	// Constructores
	Juego();
	Juego(int pasos, int f, int c);

	// Funciones del juego
	bool cargar(std::istream&/*ent/sal*/ entrada);
	bool posicion_valida(int f, int c) const;
	void posibles_movimientos(Movimiento&/*ent/sal*/ mov) const;
	Estado estado() const;
	void jugar(Movimiento const& mov);
	void mostrar(bool borrar) const;
	bool salvar(std::ostream&/*ent/sal*/ salida);

private:
	// Datos del juego
	Tablero tablero;
	int f_meta, c_meta;
	Estado estado_int;
	int numFichas = 0;

	// Funciones privadas para el juego
	void ejecuta_movimiento(Movimiento const& mov);
	void nuevo_estado();
	bool hay_ganador() const;
	bool hay_movimientos() const;

	// Funciones privadas para crear el juego aleatorio
	void posibles_movimientosAleatorio(Movimiento&/*ent/sal*/ mov) const;
	bool hay_movimientosAleatorio();
	void ejecuta_movimientoAleatorio(Movimiento const& mov, std::vector<tFicha>& fichas);
	int posiblesFichasAleatorio = 0;

	// Buscador de fichas
	int buscarFicha(int f, int c, std::vector<tFicha>& fichas);

	// Numeros aleatorios
	int aleatorio(int max) const;
};