/*
 * arbolavl.cpp
 *
 *  Created on: 11 may. 2018
 *      Author: mad18
 */

#include "arbolavl.hpp"

template <class Clave>
AVL<Clave>::AVL():
	raiz(NULL){}

template <class Clave>
AVL<Clave>::~AVL(){
	podar(raiz->hijoizq);
	podar(raiz->hijodch);

	delete raiz;
	raiz = 0;
}

template <class Clave>
void AVL<Clave>::podar(nodoAVL<Clave>* nodo){
	return;
}

template <class Clave>
nodoAVL<Clave>* AVL<Clave>::getraiz(){
	return raiz;
}

template <class Clave>
int AVL<Clave>::get_nivel(nodoAVL<Clave>* nodo){
	if(nodo == NULL)
		return -1;
	else
		return nodo->nivel;
}

template <class Clave>
int AVL<Clave>::buscar(Clave X, nodoAVL<Clave>* nodo_actual, int modo, int contador){

	if(nodo_actual != NULL){ //si el nodo a comparar no está vacío
		if(X == nodo_actual->dato){
			contador++;
			if(modo == 1)
				cout << "Dato ya Insertado" << endl << endl;
			return contador;
		}
		else{
			if(X < nodo_actual->dato){
				contador++;
				return buscar(X, nodo_actual->hijoizq, modo, contador);
			}
			if(X > nodo_actual->dato){
				contador++;
				return buscar(X, nodo_actual->hijodch, modo, contador);
			}
		}
	}
	else{
		if(modo == 1)
			cout << "Dato no Encontrado" << endl << endl;
	}

	return contador;
}

template <class Clave>
void AVL<Clave>::insert(nodoAVL<Clave>* aux, int modo){
	buscar(aux->dato, raiz, modo, 0);
	raiz = insertar(aux, raiz, modo);
}

template <class Clave>
nodoAVL<Clave>* AVL<Clave>::insertar(nodoAVL<Clave>* aux, nodoAVL<Clave>* nodo, int modo){

	if(nodo == NULL){ //inserta el nuevo dato
		nodo = new nodoAVL<Clave>;
		nodo->dato = aux->dato;
		nodo->hijoizq = NULL;
		nodo->hijodch = NULL;
		nodo->nivel = 0;
	}

	else if(aux->dato < nodo->dato){
//		if(modo == 1)
//			cout << "Elemento Añadido a la Izquierda" << endl << endl;

		nodo->hijoizq = insertar(aux, nodo->hijoizq, modo);

		if(get_nivel(nodo->hijoizq) - get_nivel(nodo->hijodch) == 2){ //si existe una diferencia de dos niveles, se reajusta
			if(aux->dato < (nodo->hijoizq)->dato)
				nodo = RotaDch(nodo);
			else{
				nodo->hijoizq = RotaIzq(nodo->hijoizq);
				return RotaDch(nodo);
			}
		}
	}

	else if(aux->dato > nodo->dato){
//		if(modo == 1)
//			cout << "Elemento Añadido a la Derecha" << endl << endl;

		nodo->hijodch = insertar(aux, nodo->hijodch, modo);

		if(get_nivel(nodo->hijodch) - get_nivel(nodo->hijoizq) == 2){ //si existe una diferencia de dos niveles, se reajusta
			if(aux->dato > (nodo->hijodch)->dato)
				nodo = RotaIzq(nodo);
			else{
				nodo->hijodch = RotaDch(nodo->hijodch);
				return RotaIzq(nodo);
			}
		}
	}

	nodo->nivel = max(get_nivel(nodo->hijoizq), get_nivel(nodo->hijodch)) + 1; //se actualiza el nivel al mayor de los hijos + 1
	return nodo;
}

template <class Clave>
void AVL<Clave>::elimin(Clave X){
	raiz = eliminar(X, raiz);
}

template <class Clave>
nodoAVL<Clave>* AVL<Clave>::eliminar(Clave X, nodoAVL<Clave>* nodo){
	nodoAVL<Clave>* temp = NULL;

	if(nodo == NULL){
		cout << "El Dato no Está en el Árbol" << endl << endl;
		return NULL;
	}

	else if(X < nodo->dato){
		nodo->hijoizq = eliminar(X, nodo->hijoizq);
	}

	else if(X > nodo->dato){
		nodo->hijodch = eliminar(X, nodo->hijodch);
	}

	else if((nodo->hijoizq != NULL) && (nodo->hijodch != NULL)){ //Si el nodo a eliminar tiene dos hijos
		temp = BuscarExtremo(nodo->hijodch);
		nodo->dato = temp->dato;
		nodo->hijodch = eliminar(nodo->dato, nodo->hijodch);
	}

	else{ //Si el nodo a eliminar tiene un hijo o no tiene
		temp = nodo;
		if(nodo->hijoizq == NULL)
			nodo = nodo->hijodch;
		else if(nodo->hijodch == NULL)
			nodo = nodo->hijoizq;
		delete temp;
		cout << "Dato Eliminado" << endl << endl;
	}

	if(nodo == NULL)
		return nodo;

	nodo->nivel = max(get_nivel(nodo->hijoizq), get_nivel(nodo->hijodch)) + 1; //se actualiza el nivel al mayor de los hijos + 1

	if(get_nivel(nodo->hijoizq) - get_nivel(nodo->hijodch) == 2){
		if(get_nivel(nodo->hijoizq->hijoizq) - get_nivel(nodo->hijoizq->hijodch) == 1)
			nodo = RotaDch(nodo);
		else{
			nodo->hijoizq = RotaIzq(nodo->hijoizq);
			return RotaDch(nodo);
		}
	}
	else
		if(get_nivel(nodo->hijodch) - get_nivel(nodo->hijoizq) == 2){
			if(get_nivel(nodo->hijodch->hijodch) - get_nivel(nodo->hijodch->hijoizq) == 1)
				nodo = RotaIzq(nodo);
			else{
				nodo->hijodch = RotaDch(nodo->hijodch);
				return RotaIzq(nodo);
			}
		}

	return nodo;
}

template <class Clave>
nodoAVL<Clave>* AVL<Clave>::BuscarExtremo(nodoAVL<Clave>* nodo){
	if(nodo == NULL)
		return NULL;
	else if(nodo->hijoizq == NULL)
		return nodo;
	else
		return BuscarExtremo(nodo->hijoizq);
}

template <class Clave>
nodoAVL<Clave>* AVL<Clave>::RotaIzq(nodoAVL<Clave>* &nodo){
	nodoAVL<Clave>* temp = nodo->hijodch;
	nodo->hijodch = temp->hijoizq;
	temp->hijoizq = nodo;
	nodo->nivel = max(get_nivel(nodo->hijoizq), get_nivel(nodo->hijodch)) + 1;
	temp->nivel = max(get_nivel(nodo->hijodch), nodo->nivel) + 1;
	return temp;
}

template <class Clave>
nodoAVL<Clave>* AVL<Clave>::RotaDch(nodoAVL<Clave>* &nodo){
	nodoAVL<Clave>* temp = nodo->hijoizq;
	nodo->hijoizq = temp->hijodch;
	temp->hijodch = nodo;
	nodo->nivel = max(get_nivel(nodo->hijoizq), get_nivel(nodo->hijodch)) + 1;
	temp->nivel = max(get_nivel(nodo->hijoizq), nodo->nivel) + 1;
	return temp;
}

template <class Clave>
void AVL<Clave>::mostrar(nodoAVL<Clave>* nodo, int nivel){
	if(nodo != NULL){ //si el nodo tiene contenido
		if(nodo == raiz){ //Si el nodo es igual a la raiz, la muestra junto con sus hijos
			cout << "Nivel " << nivel << ": [" << nodo->dato << "]" << endl;
			mostrar_hijos(nodo, nivel);
		}
		else
			mostrar_hijos(nodo, nivel);

		mostrar(nodo->hijoizq, nivel + 1);
		mostrar(nodo->hijodch, nivel + 1);
	}
	if(raiz == NULL)
		cout << endl << "Árbol Vacío:" << endl << endl << "Nivel 0: [.]" << endl << endl;
}

template <class Clave>
void AVL<Clave>::mostrar_hijos(nodoAVL<Clave>* nodo, int nivel){
	if((nodo->hijoizq == NULL) && (nodo->hijodch == NULL)){
		cout << "Nivel " << nivel + 1 << ": [.] [.]";
	}
	if((nodo->hijoizq != NULL) && (nodo->hijodch == NULL)){
		cout << "Nivel " << nivel + 1 << ": [" << (nodo->hijoizq)->dato << "] [.]";
	}
	if((nodo->hijoizq == NULL) && (nodo->hijodch != NULL)){
		cout << "Nivel " << nivel + 1 << ": [.] [" << (nodo->hijodch)->dato << "]";
	}
	if((nodo->hijoizq != NULL) && (nodo->hijodch != NULL)){
		cout << "Nivel " << nivel + 1 << ": [" << (nodo->hijoizq)->dato << "] [" << (nodo->hijodch)->dato << "]";
	}
	cout << endl;
}

template class AVL<class DNI>;
