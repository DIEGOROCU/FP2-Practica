// 1ºDG FP2 - Diego Rodriguez Cubero.

#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <cctype>

#include "GestorPartidas.h"

// Lee el proximo movimiento
Movimiento leer_movimiento(Juego& solitario);

// Funcion para preguntar el archivo a cargar para el gestor de partidas
void preguntaParacargar(std::ifstream& archivo, GestorPartidas& gestor);

// Funcio para salvar el gestor de partidas en un archivo
void salvarGestor(std::ofstream& archivo, GestorPartidas& gestor);

// Funcion para jugar una partida
void jugar(Juego& solitario);

// Funcion para jugar una partida con el gestor de partidas
void jugarGestor(GestorPartidas& gestor);

// Mensaje inicial del programa
void mensajeInicial();

// Funcion para preguntar la informacion de un tablero aleatorio
void preguntarInfoAleatorio(int& pasos, int& filas, int& columnas);

// Funcion para pedir el usuario
bool pedirUsuario(GestorPartidas& gestor);