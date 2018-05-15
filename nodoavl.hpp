/*
 * nodoavl.hpp
 *
 *  Created on: 11 may. 2018
 *      Author: mad18
 */

#pragma once

#include <iostream>

#include "dni.hpp"

template <class Clave>

class nodoAVL{

public:
	Clave dato;
	nodoAVL<Clave>* hijoizq;
	nodoAVL<Clave>* hijodch;
	int nivel;

	nodoAVL();
	nodoAVL(Clave X);
	~nodoAVL();
};
