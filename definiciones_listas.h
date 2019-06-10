/*
 * MATERIA: ALGORITMOS Y PROGRAMACI�N 3
 * UNTREF 2019.
 *
 * TRABAJO PR�CTICO FINAL INTEGRADOR: SISTEMA DE CR�DITOS.
 * FILE: definiciones_listas.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


typedef struct NodoDoble {
	unsigned int valor;
	struct NodoDoble *siguiente;
	struct NodoDoble *anterior;
}ListaDoble;


typedef struct Nodo {
	unsigned int valor;
	struct Nodo *siguiente;
}ListaSimple;
