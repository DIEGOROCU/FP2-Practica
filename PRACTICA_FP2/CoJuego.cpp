// 1ºDG FP2 - Diego Rodriguez Cubero.

#include "CoJuego.h"

using namespace std;

// Constructor por defecto de la clase Juego
Juego::Juego(): tablero(), f_meta(0), c_meta(0), estado_int(BLOQUEO){
}

// Constructor para juego aleatorio
Juego::Juego(int pasos, int f, int c) {

	// Creamos el tablero con las filas y columnas leidas (estando vacio)
	tablero = Tablero(f, c, NULA);

	// Colocamos aleatoriamente la meta
	f_meta = rand() % f;
	c_meta = rand() % c;

	// Anadimos la meta al tablero
	tablero.escribir(f_meta, c_meta, FICHA);
	std::vector<tFicha> fichas = { {f_meta, c_meta} };
	numFichas = 1;

	// Establecemos el estado del juego como JUGANDO, excepto si no hay pasos y por tanto el tablero ya esta creado con una posicion ganadora
	if (pasos == 0) {
		estado_int = GANADOR;
	}
	else {
		estado_int = JUGANDO;
	}

	// Bucle que ejecuta los pasos de creación
	while (pasos > 0 && hay_movimientosAleatorio()) {

		// Escogemos una ficha aleatoria
		int numFicha = rand() % fichas.size();

		// Comprobamos sus posibles movimientos
		Movimiento mov(fichas[numFicha].f, fichas[numFicha].c);
		posibles_movimientosAleatorio(mov);

		// Variable auxiliar para comprobar si hay fichas con movimientos posibles
		int aux = numFicha;

		// Si no hay movimientos posibles, cambiamos de ficha (pasando a la siguiente para evitar bucles infinitos o muy largos)
		while (mov.num_dirs() == 0) {

			numFicha++;

			// Si hemos llegado al final del vector de fichas, volvemos al principio
			if (numFicha == fichas.size()) {
				numFicha = 0;
			}

			// Comprobamos los posibles movimientos de la ficha seleccionada
			mov = Movimiento(fichas[numFicha].f, fichas[numFicha].c);
			posibles_movimientosAleatorio(mov);

		}

		// Fijamos la dirección aleatoriamente
		int numDir = rand() % mov.num_dirs();
		mov.fijar_dir_activa(mov.direccion(numDir));

		// Anadimos la ficha al vector de fichas
		ejecuta_movimientoAleatorio(mov, fichas);

		// Quitamos un paso
		pasos--;

	}
}

// Carga el tablero con toda su información
bool Juego::cargar(std::istream& entrada) {

	// Variables para cargar el tablero
	int filas, columnas;
	Celda inicial;

	// Leemos las filas y columnas del tablero (comprobando que sean validas)
	entrada >> filas >> columnas;
	if (filas < 1 || filas > MAXDIM || columnas < 1 || columnas > MAXDIM) {
		return false;
	}

	// Creamos el tablero (vacio) con las filas y columnas leidas
	tablero = Tablero(filas, columnas, NULA);

	// Variables auxiliares para cargar el tablero
	Celda aux;
	int numAux;

	// Leemos el tablero pasando de numero a tipo Celda
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			entrada >> numAux;
			
			if (numAux == 0) {
				aux = NULA;
			}
			else if (numAux == 1) {
				aux = VACIA;
			}
			else if (numAux == 2) {
				numFichas++;
				aux = FICHA;
			}
			else {
				return false;
			}

			tablero.escribir(i, j, aux); // Escribimos la celda en el tablero
		}
	}

	// Leemos la fila y columna de la meta (comprobando que sean validas)
	entrada >> f_meta >> c_meta;
	if (f_meta < 0 || f_meta >= filas || c_meta < 0 || c_meta >= columnas) {
		return false;
	}
	
	// Establecemos el estado del juego como JUGANDO
	estado_int = JUGANDO;
	return true;
}

// Comprueba si una posición esta dentro del tablero
bool Juego::posicion_valida(int f, int c) const {
	return tablero.correcta(f, c) && tablero.leer(f, c) == FICHA;
}

// Devuelve los posibles movimientos que puede hacer una ficha dentro de la lista de movimientos, comprobando todas las direcciones
void Juego::posibles_movimientos(Movimiento& mov) const {
	

	for (int i = 0; i < NUMDIR; i++) {
		if (tablero.correcta(mov.fila() + dirs[i].first, mov.columna() + dirs[i].second) && tablero.leer(mov.fila() + dirs[i].first, mov.columna() + dirs[i].second) == FICHA &&
			tablero.correcta(mov.fila() + 2 * dirs[i].first, mov.columna() + 2 * dirs[i].second) && tablero.leer(mov.fila() + 2 * dirs[i].first, mov.columna() + 2 * dirs[i].second) == VACIA) {

			mov.insertar_dir(Direccion(i));
		}
	}

}

// Devuelve el estado del juego
Estado Juego::estado() const {
	return estado_int;
}

// Funcion para jugar
void Juego::jugar(Movimiento const& mov) {
	ejecuta_movimiento(mov);
	nuevo_estado();
}

// Usando Colores.h muestra el tablero
void Juego::mostrar(bool borrar) const {

	if (borrar) {
	     system("cls"); // borrar consola
	}
	 
	std::cout << RESET;

	// borde superior
	pinta_cabecera(tablero);
	pinta_linea(char(218), char(194), char(191), tablero);
	// para cada fila
	for (int fil = 0; fil < tablero.num_filas(); fil++) {
		// primera línea
		pinta_borde_celda(fil, tablero);
		// segunda línea, con la meta posiblemente
		pinta_centro_celda(fil, tablero, f_meta, c_meta);
		// tercera línea
		pinta_borde_celda(fil, tablero);
		// separación entre filas
		if (fil < tablero.num_filas() - 1) {
			pinta_linea(char(195), char(197), char(180), tablero);
		}
		else {
			pinta_linea(char(192), char(193), char(217), tablero);
		}
	}

}

// Funcion para guardar el tablero en un archivo
bool Juego::salvar(std::ostream&/*ent/sal*/ salida) {
	
	// Guardamos las filas y columnas del tablero
	salida << tablero.num_filas() << ' ' << tablero.num_columnas() << std::endl;

	// Guardamos el tablero
	for (int i = 0; i < tablero.num_filas(); i++) {
		for (int j = 0; j < tablero.num_columnas(); j++) {
			salida << int(tablero.leer(i, j)) << ' ';
		}
		salida << std::endl;
	}

	// Guardamos la fila y columna de la meta
	salida << f_meta << ' ' << c_meta << std::endl;

	return true;

}

// Ejecuta un movimiento segun la dirección
void Juego::ejecuta_movimiento(Movimiento const& mov) {

	tablero.escribir(mov.fila(), mov.columna(), VACIA);

	tablero.escribir(mov.fila() + dirs[mov.dir_activa()].first, mov.columna() + dirs[mov.dir_activa()].second, VACIA);
	tablero.escribir(mov.fila() + 2 * dirs[mov.dir_activa()].first, mov.columna() + 2 * dirs[mov.dir_activa()].second, FICHA);

	numFichas--;

}

// Cambia el estado del juego
void Juego::nuevo_estado() {
	if (hay_ganador()) {
		estado_int = GANADOR;
	}
	else if (hay_movimientos()) {
		estado_int = JUGANDO;
	}
	else {
		estado_int = BLOQUEO;
	}
}

// Comprueba si en la casilla de la meta hay una ficha
bool Juego::hay_ganador() const {
	return tablero.leer(f_meta, c_meta) == FICHA && numFichas == 1;
}

// Comprueba si hay movimientos posibles, revisando todas las fichas con sus posibles movimientos
bool Juego::hay_movimientos() const {
	for (int i = 0; i < tablero.num_filas(); i++) {
		for (int j = 0; j < tablero.num_columnas(); j++) {
			Movimiento mov(i, j);
			if (tablero.leer(i, j) == FICHA) {
				posibles_movimientos(mov);
				if (mov.num_dirs() > 0) {
					return true;
				}
			}
		}
	}
	return false;
}

// Funcion que devuelve los posibles movimientos inversos que puede hacer una ficha
void Juego::posibles_movimientosAleatorio(Movimiento& mov) const {

	for (int i = 0; i < NUMDIR; i++) {
		if (tablero.correcta(mov.fila() + dirs[i].first, mov.columna() + dirs[i].second) && tablero.leer(mov.fila() + dirs[i].first, mov.columna() + dirs[i].second) != FICHA &&
			tablero.correcta(mov.fila() + 2 * dirs[i].first, mov.columna() + 2 * dirs[i].second) && tablero.leer(mov.fila() + 2 * dirs[i].first, mov.columna() + 2 * dirs[i].second) != FICHA) {

			mov.insertar_dir(Direccion(i));
		}
	}

}

// Comprueba si hay movimientos inversos posibles revisando todas las fichas
bool Juego::hay_movimientosAleatorio() {
	bool devolver = false;
	for (int i = 0; i < tablero.num_filas(); i++) {
		for (int j = 0; j < tablero.num_columnas(); j++) {
			if (tablero.leer(i, j) == FICHA) {
				Movimiento mov(i, j);
				posibles_movimientosAleatorio(mov);
				if (mov.num_dirs() > 0) {
					devolver = true;
				}
			}
		}
	}
	return devolver;
}

// Ejecuta un movimiento inverso
void Juego::ejecuta_movimientoAleatorio(Movimiento const& mov, std::vector<tFicha>& fichas) {

	// Eliminamos la ficha, y aumentamos el tamaño del vector de fichas
	tablero.escribir(mov.fila(), mov.columna(), VACIA);
	fichas.resize(fichas.size() + 1);

	int i = buscarFicha(mov.fila(), mov.columna(), fichas);

	tablero.escribir(mov.fila() + dirs[mov.dir_activa()].first, mov.columna() + dirs[mov.dir_activa()].second, FICHA);
	tablero.escribir(mov.fila() + 2 * dirs[mov.dir_activa()].first, mov.columna() + 2 * dirs[mov.dir_activa()].second, FICHA);
	fichas[i] = { mov.fila() + dirs[mov.dir_activa()].first, mov.columna() + dirs[mov.dir_activa()].second };
	fichas[fichas.size() - 1] = { mov.fila() + 2 * dirs[mov.dir_activa()].first, mov.columna() + 2 * dirs[mov.dir_activa()].second };

	numFichas++;
	
}

int Juego::buscarFicha(int f, int c, std::vector<tFicha>& fichas) {
	for (int i = 0; i < fichas.size(); i++) {
		if (fichas[i].f == f && fichas[i].c == c) {
			return i;
		}
	}
	return -1;
}

int Juego::aleatorio(int max) const {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, max - 1);

	//return dis(gen);
	return 0;
}