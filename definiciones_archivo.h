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


typedef struct Nodo {
	unsigned int valor;
	struct Nodo *siguiente;
}Lista;

Lista aux_temp;
Lista *aux = &aux_temp;

const char *archivoPersonas = "personas.csv";


/*
	PUNTEROS
	* devuelve el valor de la variable
	& devuelve la dirección de memoria
*/