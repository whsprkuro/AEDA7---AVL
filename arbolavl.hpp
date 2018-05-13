/*
 * arbolavl.hpp
 *
 *  Created on: 11 may. 2018
 *      Author: mad18
 */

#pragma once

#include "nodoavl.hpp"

#include <iostream>
#include <stdlib.h> //free

using namespace std;

template <class Clave>

class AVL{

private:
	nodoAVL<Clave>* raiz;

public:
	AVL();
	~AVL();
	void podar(nodoAVL<Clave>*); //funcion de ayuda para borrar el arbol ENTERO
	nodoAVL<Clave>* getraiz();
	int get_nivel(nodoAVL<Clave>* nodo); //devuelve el nivel de altura de un nodo en el árbol

	int buscar(Clave X, nodoAVL<Clave>* nodo_actual, int modo, int contador);
	nodoAVL<Clave>* BuscarExtremo(nodoAVL<Clave>* nodo);
	void insert(nodoAVL<Clave>* aux, int modo);
	nodoAVL<Clave>* insertar(nodoAVL<Clave>* aux, nodoAVL<Clave>* nodo, int modo);
	void elimin(Clave X);
	nodoAVL<Clave>* eliminar(Clave X, nodoAVL<Clave>* nodo);

	nodoAVL<Clave>* RotaIzq(nodoAVL<Clave>* &nodo);
	nodoAVL<Clave>* RotaDch(nodoAVL<Clave>* &nodo);

	void mostrar(nodoAVL<Clave>* nodo, int nivel); //muestra el árbol en vertical
	void mostrar_hijos(nodoAVL<Clave>* nodo, int nivel);

};
