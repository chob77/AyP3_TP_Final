/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: definiciones_lista_simple.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


typedef struct Nodo {
	unsigned int cliente;
	unsigned int amigo;
	struct Nodo *siguiente;
}Lista;

typedef Lista *ListaClienteAmigo;

ListaClienteAmigo listaClienteAmigo;
ListaClienteAmigo *lista = &listaClienteAmigo;


Lista aux_temp;
Lista *aux = &aux_temp;
