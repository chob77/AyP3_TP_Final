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
	unsigned int dniCliente;
	unsigned int linea;
	struct NodoArchivo *siguiente;
}	ListaClienteLineaArchivo;


typedef struct NodoCredito {
	unsigned int dniCliente;
	struct structCredito credito;
	struct NodoCredito *siguiente;
}	ListaCreditosClientes;


typedef struct nodoSubPagos
{
	struct structPago pago;
	struct nodoSubPagos *siguiente;
}	SubListaPagos;


typedef struct NodoPago {
	unsigned int idCredito;
	struct NodoPago *siguiente;
	struct nodoSubPagos *pagos;
}	ListaPagoCliente;


/** LISTA ENLAZADA PARA ALMACENAR LOS CRÉDITOS QUE POSEEN PAGOS*/
typedef struct arrayCredito {
	unsigned int idCredito;
	struct arrayCredito *siguiente;
}	ArrayCreditos;



Lista listaCliAmi;
Lista *listaClienteAmigo = &listaCliAmi;

ListaClienteLineaArchivo listaCliLinArchi;
ListaClienteLineaArchivo *listaClienteLineaArchivo = &listaCliLinArchi ;

ListaClienteLineaArchivo listaCreLinArchi;
ListaClienteLineaArchivo *listaCreditoLineaArchivo = &listaCreLinArchi ;

ListaCreditosClientes listaCreCli;
ListaCreditosClientes *listaCreditoCliente = &listaCreCli;

ListaPagoCliente listaPagCli;
ListaPagoCliente *listaPagoCliente = &listaPagCli;

ArrayCreditos arrayCredPag;
ArrayCreditos *arrayCreditoPagos = &arrayCredPag;

Lista aux_temp;
Lista *aux = &aux_temp;

Credito *obtenerDireccionCredito( ListaCreditosClientes *miLista, int idCredito );
