/*
 * definiciones_Lista_doble.h
 *
 *  Created on: 27 abr. 2019
 *      Author: chob
 */


typedef struct NodoDoble {
	unsigned int valor;
	struct NodoDoble *siguiente;
	struct NodoDoble *anterior;
}ListaDoble;

