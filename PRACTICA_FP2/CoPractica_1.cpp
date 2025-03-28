// 1ºDG FP2 - Diego Rodriguez Cubero.

#include "MainFunciones.h"

int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));

	mensajeInicial(); // Mensaje de bienvenida

	GestorPartidas gestor; // Creamos el gestor de partidas
	std::ifstream archivo;
	preguntaParacargar(archivo, gestor); // Preguntamos el archivo a cargar

	while (pedirUsuario(gestor)) {

		jugarGestor(gestor); // Jugamos la partida

		gestor.logout();     // Cerramos la sesion

	}

	std::ofstream archivoSalida;
	salvarGestor(archivoSalida, gestor); // Salvamos el gestor en un archivo
	archivoSalida.close();

	// Mensaje de despedida
	system("cls");
	std::cout << BLUE << "¡Hasta la próxima!\n" << RESET;

	return 0;
}