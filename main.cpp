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
//void prueba(AVL<DNI>& Arbol);

void menu(){
	cout << "Introducir Tipo de Prueba" << endl << endl;
	cout << "1. Demostraci�n" << endl;
	cout << "2. Estad�stica" << endl;
	int tPrueba;
	cin >> tPrueba;

	AVL<DNI> Arbol;

	if(tPrueba == 1){
		Arbol.mostrar(Arbol.getraiz(), 0);
		demo(Arbol); //Modo Demostraci�n
	}
	else if(tPrueba == 2)
		est(Arbol); //Modo Estad�stica
	else{
		cout << "Opci�n inv�lida" << endl;
		menu();
	}
}

void demo(AVL<DNI>& Arbol){

	cout << "Seleccione Operaci�n" << endl << endl;
	cout << "[0] Salir" << endl;
	cout << "[1] Insertar Clave" << endl;
	cout << "[2] Eliminar Clave" << endl;
	int opcion;
	cin >> opcion;

	switch(opcion){
		case 0:
			cout << endl;
			menu();
			break;
		case 1:
			insert(Arbol);
			break;
		case 2:
			eliminar(Arbol);
			break;
		}

	if((opcion != 0) || (opcion != 1) || (opcion != 2)){
		cout << endl << "Opci�n inv�lida" << endl << endl;
		demo(Arbol);
	}
}

void insert(AVL<DNI>& Arbol){

	nodoAVL<DNI> *aux = new nodoAVL<DNI>;

	cout << endl << "Introduzca Valor a Insertar" << endl;
	cin >> aux->dato; //introduzco el valor del DNI directamente en el nodo
	cout << endl;

	Arbol.insert(aux, 1); //inserto el nodo con el nuevo valor en el �rbol
	Arbol.mostrar(Arbol.getraiz(), 0);
	cout << endl;

	demo(Arbol);
}

void eliminar(AVL<DNI>& Arbol){

	if(Arbol.getraiz() == NULL){
		cout << endl << "�rbol Vac�o, no hay Nada que Borrar" << endl << endl;
		demo(Arbol);
	}

	cout << endl << "Introduzca Valor a Eliminar" << endl;
	string val;
	cin >> val;

	DNI A; //creo un DNI con valor especificado
	A.set_numDNI(val);

	Arbol.elimin(A); //el DNI ser� buscado en el �rbol y eliminado
	Arbol.mostrar(Arbol.getraiz(), 0);
	cout << endl;

	demo(Arbol);
}

void est(AVL<DNI>& Arbol){
	cout << endl << "Introducir Tama�o del �rbol" << endl;
	int N;
	cin >> N;

	cout << endl << "Introducir N�mero de Pruebas a Realizar" << endl;
	int nPruebas;
	cin >> nPruebas;
	cout << endl;

	nodoAVL<DNI> *dnivector = new nodoAVL<DNI>[2*N]; //Genera vector de DNI aleatorios (Banco de Pruebas)
	for(int i = 0; i < 2*N; i++){
		dnivector[i].dato = DNI();
	}

	for(int i = 0; i < N; i++){ //Insertar DNI hasta el tama�o del �rbol
		Arbol.insert(&dnivector[i], 0);
	}

//	Arbol.mostrar(Arbol.getraiz(), 0);

	cout << "\t\t\t\tN�mero de Comparaciones" << endl;
	cout << "                N        Pruebas        M�nimo        Medio        M�ximo" << endl;

	contador_busqueda(Arbol, nPruebas, dnivector, N);
	contador_insercion(Arbol, nPruebas, dnivector, N);

	cout << endl << endl;
	menu();
}

void contador_busqueda(AVL<DNI>& Arbol, int nPruebas, nodoAVL<DNI> *dnivector, int tree_sz){
	int total = 0, min = 99999, max = 0, clave_random = 0;

	for(int j = 0; j <= nPruebas; j++){
		clave_random = rand() % tree_sz; //extraer clave de forma aleatoria de entre las insertadas en el �rbol

//		dnivector[clave_random].mostrarNodo();
//		cout << endl << endl;

		int contador = Arbol.buscar(dnivector[clave_random].dato, Arbol.getraiz(), 0, 0); //Buscar en el �rbol las nPruebas claves

		if(contador < min){ min = contador; }
		if(contador > max){ max = contador; }
		total += contador;

		if(j == nPruebas)
			cout << "B�squeda:       " << tree_sz << "\t    " << nPruebas << "\t\t   " << min << "\t\t" << total/nPruebas << "\t     " << max << endl;
	}
}

void contador_insercion(AVL<DNI>& Arbol, int nPruebas, nodoAVL<DNI> *dnivector, int tree_sz){
	int total = 0, min = 99999, max = 0, clave_random = 0;

	for(int j = 0; j <= nPruebas; j++){
		clave_random = rand() % tree_sz + tree_sz; //extraer clave de forma aleatoria del banco de pruebas que no se insertaron en el �rbol

//		dnivector[clave_random].mostrarNodo();
//		cout << endl << endl;

		int contador = Arbol.buscar(dnivector[clave_random].dato, Arbol.getraiz(), 0, 0); //Buscar en el �rbol las nPruebas claves

		if(contador < min){ min = contador; }
		if(contador > max){ max = contador; }
		total += contador;

		if(j == nPruebas)
			cout << "Inserci�n:      " << tree_sz << "\t    " << nPruebas << "\t\t   " << min << "\t\t" << total/nPruebas << "\t     " << max << endl;
	}
}

int main(){

	menu();

	return 0;
}
