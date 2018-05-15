/*
 * nodoavl.cpp
 *
 *  Created on: 11 may. 2018
 *      Author: mad18
 */

#include "nodoavl.hpp"

template <class Clave>
nodoAVL<Clave>::nodoAVL():
	hijoizq(NULL), hijodch(NULL), nivel(0){}

template <class Clave>
nodoAVL<Clave>::nodoAVL(Clave X):
	dato(X), hijoizq(NULL), hijodch(NULL), nivel(0){}

template <class Clave>
nodoAVL<Clave>::~nodoAVL(){}

template class nodoAVL<class DNI>;
