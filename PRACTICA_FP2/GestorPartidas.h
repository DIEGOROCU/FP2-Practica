// 1ºDG FP2 - Diego Rodriguez Cubero.

#pragma once

#include "memoryleaks.h"
#include "CoJuego.h"
#include "Lista.h"

using Usuario = std::string;

class GestorPartidas {
public:
	GestorPartidas(); // crea un gestor vacío
	~GestorPartidas(); // destructora
	bool cargar(std::istream&/*ent/sal*/ entrada);
	bool salvar(std::ostream&/*ent/sal*/ salida);
	void login(Usuario const& usuario);
	void logout();
	bool tiene_partidas() const;
	void mostrar_partidas() const;
	int insertar_aleatoria(int movimientos, int filas, int columnas);
	Juego& partida(int part);
	void eliminar_partida(int part);
	int num_partidas() const;
	int buscarUsuario(Usuario const& usuario) const;
private:
	static const int NOLOGIN = -1;
	int usuario_activo; // posición del usuario que ha hecho login
	struct UsuarioPartidas {
		Usuario user;
		Lista<Juego*> partidas;
		bool operator==(Usuario const& u) const { return user == u; }
		bool operator<(Usuario const& u) const { return user < u; }
	};
	Lista<UsuarioPartidas*> usuarios;
};