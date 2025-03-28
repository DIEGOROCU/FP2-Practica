// 1ºDG FP2 - Diego Rodriguez Cubero.

#pragma once

#include "memoryleaks.h"

const int max_elems = 10;

template <typename T>
class Lista {
public:
	Lista(int N = 0, T vini = T()); // constructora
	~Lista(); // destructora
	T& operator[](int i);
	T const& operator[](int i) const;
	void push_back(T elem);
	void pop_back();
	int size() const;
	bool empty() const;
	void insertar(int pos, T elem);
	void borrar(int pos);
private:
	T* datos;
	int num_elems;
	int capacidad;
};

// Constructor por defecto de la clase Lista
template <typename T>
Lista<T>::Lista(int N, T vini): capacidad(N), num_elems(N) {
	if (N > 0) {
		datos = new T[N];
		for (size_t i = 0; i < N; ++i) {
			datos[i] = vini;
		}
	}
	else
		datos = nullptr;
}

// Destructor de la clase Lista
template <typename T>
Lista<T>::~Lista() {
	delete[] datos;
	datos = nullptr;
	capacidad = num_elems = 0;
}

// Devuelve el elemento en la posición i de la lista
template <typename T>
T& Lista<T>::operator[](int i) {
	return datos[i];
}

// Devuelve el elemento en la posición i de la lista (constante)
template <typename T>
T const& Lista<T>::operator[](int i) const {
	return datos[i];
}

// Añade un elemento al final de la lista (si no hay espacio, se duplica la capacidad)
template <typename T>
void Lista<T>::push_back(T elem) {
	if (num_elems == capacidad) {
		capacidad = capacidad == 0 ? 2 : 2 * capacidad;
		T* aux = new T[capacidad];
		for (int i = 0; i < num_elems; i++) {
			aux[i] = datos[i];
		}
		delete[] datos;
		datos = aux;
	}
	datos[num_elems] = elem;
	num_elems++;
}

// Elimina el último elemento de la lista (si hay elementos)
template <typename T>
void Lista<T>::pop_back() {
	if (num_elems > 0) {
		num_elems--;
	}
}

// Devuelve el número de elementos de la lista
template <typename T>
int Lista<T>::size() const {
	return num_elems;
}

// Devuelve si la lista está vacía
template <typename T>
bool Lista<T>::empty() const {
	return num_elems == 0;
}

// Inserta un elemento en la posición pos de la lista
template <typename T>
void Lista<T>::insertar(int pos, T elem) {
	if (num_elems == capacidad) {
		capacidad *= 2;
		T* aux = new T[capacidad];
		for (int i = 0; i < num_elems; i++) {
			aux[i] = datos[i];
		}
		delete[] datos;
		datos = aux;
	}
	for (int i = num_elems; i > pos; i--) {
		datos[i] = datos[i - 1];
	}
	datos[pos] = elem;
	num_elems++;
}

// Borra el elemento en la posición pos de la lista
template <typename T>
void Lista<T>::borrar(int pos) {
	for (int i = pos; i < num_elems - 1; i++) {
		datos[i] = datos[i + 1];
	}
	num_elems--;
}