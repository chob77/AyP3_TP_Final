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
}	Lista;



typedef struct NodoArchivo {
	unsigned int cliente;
	unsigned int linea;
	struct NodoArchivo *siguiente;
}	ListaClienteLineaArchivo;



typedef struct NodoCredito {
	unsigned int cliente;
	// unsigned int credito;
	struct structCredito credito;
	struct NodoCredito *siguiente;
}	ListaCreditoCliente;


Lista listaCliAmi;
Lista *listaClienteAmigo = &listaCliAmi;

ListaClienteLineaArchivo listaCliLinArchi;
ListaClienteLineaArchivo *listaClienteLineaArchivo = &listaCliLinArchi ;

ListaClienteLineaArchivo listaCreLinArchi;
ListaClienteLineaArchivo *listaCreditoLineaArchivo = &listaCreLinArchi ;

ListaCreditoCliente listaCreCli;
ListaCreditoCliente *listaCreditoCliente = &listaCreCli;

Lista aux_temp;
Lista *aux = &aux_temp;
