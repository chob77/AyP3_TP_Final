/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: definiciones_archivo.h
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
}Lista;

const char *archivoPersonas = "clientes.csv";
const char *tempClientesActivos = "temp_clientes_activos.csv";
const char *tempClientesInactivos = "temp_clientes_inactivos.csv";
const char *archivoCreditos = "creditos.csv";
const char *archivoPagos = "pagos.csv";

/*
	PUNTEROS
	* devuelve el valor de la variable
	& devuelve la dirección de memoria
*/
