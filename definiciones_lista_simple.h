/*
 * MATERIA: ALGORITMOS Y PROGRAMACI�N 3
 * UNTREF 2019.
 *
 * TRABAJO PR�CTICO FINAL INTEGRADOR: SISTEMA DE CR�DITOS.
 * FILE: definiciones_lista_simple.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


typedef struct Nodo {
	unsigned int cliente;
	unsigned int amigo;
	struct Nodo *siguiente;
}	Lista;


typedef struct NodoArchivo {
	unsigned int cliente;
	unsigned int linea;
	struct NodoArchivo *siguiente;
}	ListaClienteLineaArchivo;


Lista listaCliAmi;
Lista *listaClienteAmigo = &listaCliAmi;


ListaClienteLineaArchivo listaCliLinArchi;
ListaClienteLineaArchivo *listaClienteLineaArchivo = &listaCliLinArchi ;


Lista aux_temp;
Lista *aux = &aux_temp;
