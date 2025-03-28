// 1ºDG FP2 - Diego Rodriguez Cubero.

#include "MainFunciones.h"

// Lee el proximo movimiento
Movimiento leer_movimiento(Juego& solitario) {

	// Leemos la fila y columna de la ficha
	int f, c;
	std::cout << "Selecciona una FICHA (fila y columna, 0 0 para salir): ";
	std::cin >> f >> c;
	f--;
	c--;

	if (f == -1 && c == -1) {
		return Movimiento(f, c);
	}

	// Comprobamos que la ficha seleccionada sea valida
	while (!solitario.posicion_valida(f, c)) {
		std::cout << "Selecciona una FICHA VALIDA (fila y columna): ";
		std::cin >> f >> c;
		f--;
		c--;
	}

	// Comprobamos los posibles movimientos de la ficha seleccionada
	Movimiento mov(f, c);
	solitario.posibles_movimientos(mov);

	// Si no hay movimientos posibles, volvemos a leer la ficha
	if (mov.num_dirs() == 0) {
		std::cout << "No hay movimientos posibles para esta ficha\n";
		std::cout << std::endl;
		return leer_movimiento(solitario);
	}

	// Si solo hay un movimiento posible, lo ejecutamos
	if (mov.num_dirs() == 1) {
		mov.fijar_dir_activa(mov.direccion(0));
		return mov;
	}

	// Si hay mas de un movimiento posible, preguntamos al usuario cual quiere ejecutar
	std::cout << "Posibles direcciones: " << std::endl;

	for (int i = 0; i < mov.num_dirs(); i++) {
		std::cout << "     " << i + 1 << "." << to_string(mov.direccion(i)) << std::endl;
	}

	int dir;
	std::cout << "Seleccione la direccion posible (numero): ";
	std::cin >> dir;
	dir--;

	// Comprobamos que la direccion seleccionada sea valida
	while (dir < 0 || dir >= mov.num_dirs()) {
		std::cout << RED "Seleccione una direccion VALIDA (numero): " RESET;
		std::cin >> dir;
		dir--;
	}

	// Fijamos la direccion seleccionada
	mov.fijar_dir_activa(mov.direccion(dir));

	return mov;
}


// Pregunta al usuario si quiere cargar un archivo
void preguntaParacargar(std::ifstream& archivo, GestorPartidas& gestor) {

		std::string nombre;
		std::cout << "Introduce el nombre del archivo para cargar el gestor (sin .txt): ";
		std::cin >> nombre;
		archivo.open(nombre + ".txt");

		if (!gestor.cargar(archivo)) {
			std::cout << RED "No se ha podido cargar el archivo, vuelva a introducir el nombre (sin .txt): " RESET;
			preguntaParacargar(archivo, gestor);
		}

		archivo.close();

}

// Funcio para salvar el gestor de partidas en un archivo
void salvarGestor(std::ofstream& archivo, GestorPartidas& gestor) {

	std::string nombre;
	std::cout << "Introduce el nombre del archivo para salvar el gestor (sin .txt): ";
	std::cin >> nombre;
	archivo.open(nombre + ".txt");

	gestor.salvar(archivo);

}

// Funcion para jugar una partida
void jugar(Juego& solitario) {

	solitario.mostrar(true); // se muestra el estado inicial

	// Bucle de juego
	while (solitario.estado() == JUGANDO) { 				 // Mientras se este jugando 
		Movimiento movimiento = leer_movimiento(solitario);  // Leemos el movimiento
		if (movimiento.fila() == -1 && movimiento.columna() == -1) {
			system("cls"); // borrar consola
			return;
		}
		else {
			solitario.jugar(movimiento);					 // Aplicamos el movimiento
			solitario.mostrar(true);						 // Mostramos el estado
		}
	}

}

// Funcion para jugar una partida con el gestor de partidas
void jugarGestor(GestorPartidas& gestor) {
	
	char respuesta;

	do {

		system("cls"); // borrar consola

		int partida;

		// Si el usuario tiene partidas, mostramos las partidas y preguntamos cual quiere jugar
		if (gestor.tiene_partidas()) {
			gestor.mostrar_partidas();
			// Preguntamos la partida a jugar
			std::cout << "Introduce el numero de la partida (0 para crear una aleatoria): ";
			std::cin >> partida;
			// Comprobamos que la partida seleccionada sea valida
			while (partida < 0 || partida > gestor.num_partidas()) {
				std::cout << RED "Introduce un numero de partida VALIDO: " RESET;
				std::cin >> partida;
			}
			// Si se selecciona la opcion de crear una partida aleatoria, la creamos preguntando la informacion necesaria
			if (partida == 0) {
				int pasos, filas, columnas;
				preguntarInfoAleatorio(pasos, filas, columnas);
				partida = gestor.insertar_aleatoria(pasos, filas, columnas);
			}
		}
		// Si el usuario no tiene partidas, creamos una partida aleatoria
		else {
			std::cout << "No tienes partidas, proderemos a crear un tablero ALEATORIO\n";
			int pasos, filas, columnas;
			preguntarInfoAleatorio(pasos, filas, columnas);
			partida = gestor.insertar_aleatoria(pasos, filas, columnas);

		}

		// Obtenemos la partida seleccionada
		Juego& solitario = gestor.partida(partida);

		// Jugamos la partida
		jugar(solitario);


		// Mostramos el resultado de la partida y eliminamos la partida si es necesario
		if (solitario.estado() == GANADOR) {
			gestor.eliminar_partida(partida);
			std::cout << YELLOW "¡Enhorabuena, has ganado!\n" RESET;
		}
		else if (solitario.estado() == BLOQUEO) {
			gestor.eliminar_partida(partida);
			std::cout << RED "No hay mas movimientos posibles, has perdido\n" RESET;
		}

		// Preguntamos si se quiere seguir jugando
		std::cout << "¿Quieres seguir jugando? (s/n): ";
		
		std::cin >> respuesta;
		// Comprobamos que la respuesta sea valida
		while (respuesta != 's' && respuesta != 'n') {
			std::cout << RED "Introduce una respuesta VALIDA (s/n): " RESET;
			std::cin >> respuesta;
		}

	} while (respuesta == 's'); // Si se quiere seguir jugando, volvemos a jugar

	// Si no, volvemos al menu de usuario
	system("cls"); // borrar consola

}

// Mensaje inicial del juego 
void mensajeInicial() {
	std::cout << RESET "¡Hola y bienvenido al juego del solitario!\n";
	std::cout << "El objetivo del juego es dejar solo una " GREEN "ficha" RESET" en el " GRAY "tablero" RESET"\n";
	std::cout << "Para ello, deberas ir saltando " GREEN "fichas" RESET" hasta que solo quede una\n";
	std::cout << "Solo puedes saltar una " GREEN "ficha" RESET" por turno, y solo en horizontal o vertical\n";
	std::cout << "Ademas, solo puedes saltar una " GREEN "ficha" RESET" si hay otra " GREEN "ficha" RESET" justo detras\n";
	std::cout << "Y la ultima " GREEN "ficha" RESET" que quede debe estar en la casilla " YELLOW "final" RESET"\n";
	std::cout << "¿Preparado? ¡Vamos a jugar!\n" RESET;
}

// Funcion que pregunta al usuario la información para crear un tablero aleatorio
void preguntarInfoAleatorio(int& pasos, int& filas, int& columnas) {

	// Preguntamos por el numero de filas y columnas del tablero comprobando que sean validas
	std::cout << "Introduce el numero de filas y columnas del tablero: ";
	std::cin >> filas >> columnas;
	while (filas < 1 || filas > MAXDIM || columnas < 1 || columnas > MAXDIM) {
		std::cout << RED << "Introduce un numero de filas y columnas VALIDO (entre 1 y 10): " << RESET;
		std::cin >> filas >> columnas;
	}

	// Preguntamos por el numero de pasos de creacion (su validez se comprobara al crear el tablero, tan solo comprobamos que no exceda el tamaño del tablero)
	std::cout << "Introduce el numero de pasos de creacion: ";
	std::cin >> pasos;
	while (pasos < 0 || pasos > filas * columnas) {
		std::cout << RED << "Introduce un numero de pasos VALIDO (entre 0 y " << filas * columnas << "): " << RESET;
		std::cin >> pasos;
	}

	std::cout << std::endl;

}

// Funcion que pide el usuario
bool pedirUsuario(GestorPartidas& gestor) {

	std::string usuario;

	// Pedimos el nombre de usuario
	std::cout << "Introduzca su usuario (FIN para terminar): ";
	std::cin >> usuario;

	if (usuario == "FIN") {
		return false;
	}
	else {
		gestor.login(usuario);
		return true;
	}
	

}