/*
 * main.cpp
 *
 *  Created on: 11 may. 2018
 *      Author: mad18
 */

#include <iostream>
#include <stdlib.h> //srand, rand

#include "dni.hpp"
#include "nodoavl.hpp"
#include "arbolavl.hpp"

using namespace std;

void menu();
void demo(AVL<DNI>& Arbol);
void insert(AVL<DNI>& Arbol);
void eliminar(AVL<DNI>& Arbol);
void est(AVL<DNI>& Arbol);
void contador_busqueda(AVL<DNI>& Arbol, int nPruebas, nodoAVL<DNI> *dnivector, int tree_sz);
void contador_insercion(AVL<DNI>& Arbol, int nPruebas, nodoAVL<DNI> *dnivector, int tree_sz);

ostream& os = cout;

void menu(){
	os << "Introducir Tipo de Prueba" << endl << endl;
	os << "1. Demostración" << endl;
	os << "2. Estadística" << endl;
	int tPrueba;
	cin >> tPrueba;

	AVL<DNI> Arbol;

	if(tPrueba == 1){
		Arbol.mostrar(Arbol.getraiz(), 0);
		demo(Arbol); //Modo Demostración
	}
	else if(tPrueba == 2)
		est(Arbol); //Modo Estadística
	else{
		os << "Opción inválida" << endl;
		menu();
	}
}

void demo(AVL<DNI>& Arbol){

	os << "Seleccione Operación" << endl << endl;
	os << "[0] Salir" << endl;
	os << "[1] Insertar Clave" << endl;
	os << "[2] Eliminar Clave" << endl;
	int opcion;
	cin >> opcion;

	switch(opcion){
		case 0:
			os << endl;
			menu();
			break;
		case 1:
			insert(Arbol);
			break;
		case 2:
			eliminar(Arbol);
			break;
		default:
			os << endl << "Opción no Válida" << endl << endl;
			demo(Arbol);
	}
}

void insert(AVL<DNI>& Arbol){

	nodoAVL<DNI> *aux = new nodoAVL<DNI>;

	os << endl << "Introduzca Valor a Insertar" << endl;
	cin >> aux->dato; //introduzco el valor del DNI directamente en el nodo
	os << endl;

	Arbol.insert(aux, 1); //inserto el nodo con el nuevo valor en el árbol
	Arbol.mostrar(Arbol.getraiz(), 0);
	os << endl;

	demo(Arbol);
}

void eliminar(AVL<DNI>& Arbol){

	if(Arbol.getraiz() == NULL){
		os << endl << "Árbol Vacío, no hay Nada que Borrar" << endl << endl;
		demo(Arbol);
	}

	os << endl << "Introduzca Valor a Eliminar" << endl;
	string val;
	cin >> val;

	DNI A; //creo un DNI con valor especificado
	A.set_numDNI(val);

	Arbol.elimin(A); //el DNI será buscado en el árbol y eliminado
	Arbol.mostrar(Arbol.getraiz(), 0);
	os << endl;

	demo(Arbol);
}

void est(AVL<DNI>& Arbol){
	os << endl << "Introducir Tamaño del Árbol" << endl;
	int N;
	cin >> N;

	os << endl << "Introducir Número de Pruebas a Realizar" << endl;
	int nPruebas;
	cin >> nPruebas;
	os << endl;

	nodoAVL<DNI> *dnivector = new nodoAVL<DNI>[2*N]; //Genera vector de DNI aleatorios (Banco de Pruebas)
	for(int i = 0; i < 2*N; i++){
		dnivector[i].dato = DNI();
	}

	for(int i = 0; i < N; i++){ //Insertar DNI hasta el tamaño del árbol
		Arbol.insert(&dnivector[i], 0);
	}

	os << "\t\t\t\tNúmero de Comparaciones" << endl;
	os << "                N        Pruebas        Mínimo        Medio        Máximo" << endl;

	contador_busqueda(Arbol, nPruebas, dnivector, N);
	contador_insercion(Arbol, nPruebas, dnivector, N);

	os << endl << endl;
	menu();
}

void contador_busqueda(AVL<DNI>& Arbol, int nPruebas, nodoAVL<DNI> *dnivector, int tree_sz){
	int total = 0;
	int min = 99999;
	int max = 0;
	int clave_random = 0;

	for(int j = 0; j <= nPruebas; j++){
		clave_random = rand() % tree_sz; //extraer clave de forma aleatoria de entre las insertadas en el árbol

		int contador = Arbol.buscar(dnivector[clave_random].dato, Arbol.getraiz(), 0, 0); //Buscar en el árbol las nPruebas claves

		if(contador < min){ min = contador; }
		if(contador > max){ max = contador; }
		total += contador;
	}

	os << "Búsqueda:       " << tree_sz << "\t    " << nPruebas << "\t\t   " << min << "\t\t" << total/nPruebas << "\t     " << max << endl;
}

void contador_insercion(AVL<DNI>& Arbol, int nPruebas, nodoAVL<DNI> *dnivector, int tree_sz){
	int total = 0;
	int min = 99999;
	int max = 0;
	int clave_random = 0;

	for(int j = 0; j <= nPruebas; j++){
		clave_random = rand() % tree_sz + tree_sz; //extraer clave de forma aleatoria del banco de pruebas que no se insertaron en el árbol

		int contador = Arbol.buscar(dnivector[clave_random].dato, Arbol.getraiz(), 0, 0); //Buscar en el árbol las nPruebas claves

		if(contador < min){ min = contador; }
		if(contador > max){ max = contador; }
		total += contador;
	}

	os << "Inserción:      " << tree_sz << "\t    " << nPruebas << "\t\t   " << min << "\t\t" << total/nPruebas << "\t     " << max << endl;
}

int main(){

	menu();

	return 0;
}
