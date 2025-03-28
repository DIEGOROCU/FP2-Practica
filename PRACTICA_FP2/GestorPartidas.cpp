// 1ºDG FP2 - Diego Rodriguez Cubero.

#include "GestorPartidas.h"

// Constructor por defecto de la clase GestorPartidas
GestorPartidas::GestorPartidas(): usuario_activo(-1) {
}

// Destructor de la clase GestorPartidas
GestorPartidas::~GestorPartidas() {
	for (int i = 0; i < usuarios.size(); i++) {
		// Destruimos las partidas
		for (int j = 0; j < usuarios[i]->partidas.size(); j++) {
			delete usuarios[i]->partidas[j];
		}
		// Destruimos el usuario
		delete usuarios[i];
	}
}

// Carga los datos de un fichero de entrada en el gestor de partidas
bool GestorPartidas::cargar(std::istream& entrada) {

	// Leer el número de usuarios
	int numUsuarios;
	entrada >> numUsuarios;

	// Por cada usuario
	for (int i = 0; i < numUsuarios; i++) {
		
		// Creamos un nuevo usuario
		UsuarioPartidas* usuario = new UsuarioPartidas;

		// Leemos el nombre del usuario y el número de partidas
		entrada >> usuario->user;
		int numPartidas;
		entrada >> numPartidas;
		// Por cada partida creamos un nuevo juego y lo cargamos
		for (int j = 0; j < numPartidas; j++) {
			Juego* juego = new Juego;
			// Si no se ha podido cargar la partida, devolvemos false
			if (!juego->cargar(entrada)) {
				return false;
			}
			usuario->partidas.push_back(juego);
		}
		usuarios.push_back(usuario);
	}

	// Si se han cargado todos los usuarios, devolvemos true
	return true;
}

// Guarda los datos del gestor de partidas en el fichero de salida
bool GestorPartidas::salvar(std::ostream& salida) {

	// Guardamos el número de usuarios
	salida << usuarios.size() << std::endl;

	// Por cada usuario
	for (int i = 0; i < usuarios.size(); i++) {
		// Guardamos el nombre del usuario y el número de partidas
		salida << usuarios[i]->user << std::endl;
		salida << usuarios[i]->partidas.size() << std::endl;
		// Guardamos cada partida
		for (int j = 0; j < usuarios[i]->partidas.size(); j++) {
			// Si no se ha podido guardar la partida, devolvemos false
			if (!usuarios[i]->partidas[j]->salvar(salida)) {
				return false;
			}
		}
	}
	// Si se han guardado todas las partidas, devolvemos true
	return true;
}

// Inicia sesión con un usuario, si no existe lo crea y lo inserta en orden alfabético
void GestorPartidas::login(Usuario const& usuario) {

	// Buscamos el usuario en el vector de usuarios
	int pos = buscarUsuario(usuario);
	// Si no lo encontramos, lo insertamos en la posición que le corresponde
	if (pos == usuarios.size() || usuarios[pos]->user != usuario) {
		UsuarioPartidas* nuevo = new UsuarioPartidas;
		nuevo->user = usuario;
		usuarios.insertar(pos, nuevo);
	}
    // Actualizamos el usuario activo
	usuario_activo = pos;
}

// Cierra la sesión del usuario activo
void GestorPartidas::logout() {
	if (usuarios[usuario_activo]->partidas.size() == 0) {
		delete usuarios[usuario_activo];
		usuarios.borrar(usuario_activo);
	}
	usuario_activo = NOLOGIN;
}

// Devuelve si el usuario activo tiene partidas
bool GestorPartidas::tiene_partidas() const {
	return usuarios[usuario_activo]->partidas.size() > 0;
}

// Muestra las partidas del usuario activo
void GestorPartidas::mostrar_partidas() const {
	for (int i = 0; i < usuarios[usuario_activo]->partidas.size(); i++) {
		std::cout << i+1 << " ---------------" << std::endl;
		usuarios[usuario_activo]->partidas[i]->mostrar(false);
	}
}

// Inserta una partida aleatoria en el usuario activo
int GestorPartidas::insertar_aleatoria(int movimientos, int filas, int columnas) {
	
	// Creamos la partida aleatoria
	Juego* juego = new Juego(movimientos, filas, columnas);

	// Lo añadimos a la lista de partidas del usuario activo, y devolvemos su posicion
	usuarios[usuario_activo]->partidas.push_back(juego);
	return usuarios[usuario_activo]->partidas.size();

}

// Devuelve una partida del usuario activo
Juego& GestorPartidas::partida(int part) {
	return *usuarios[usuario_activo]->partidas[part-1];
}

// Elimina una partida del usuario activo
void GestorPartidas::eliminar_partida(int part) {
	delete usuarios[usuario_activo]->partidas[part-1];
	usuarios[usuario_activo]->partidas.borrar(part-1);
}

// Devuelve el número de partidas del usuario activo
int GestorPartidas::num_partidas() const {
	return usuarios[usuario_activo]->partidas.size();
}

// Busca un usuario en el vector de usuarios, si no lo encuentra devuelve la posición donde debería estar (usa búsqueda binaria)
int GestorPartidas::buscarUsuario(Usuario const& usuario) const {
	int ini = 0, fin = usuarios.size();
	while (ini < fin) {
		int mitad = (ini + fin) / 2;
		if (usuarios[mitad]->user < usuario) {
			ini = mitad + 1;
		}
		else {
			fin = mitad;
		}
	}
	return ini;
}