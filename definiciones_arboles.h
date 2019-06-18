/*
 * MATERIA: ALGORITMOS Y PROGRAMACI�N 3
 * UNTREF 2019.
 *
 * TRABAJO PR�CTICO FINAL INTEGRADOR: SISTEMA DE CR�DITOS.
 * FILE: definiciones_arboles.c
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


enum {IZQUIERDO, DERECHO};

#define TRUE 1
#define FALSE 0

// Estructuras y tipos
typedef struct nodo_arbol
{
   int dato;
   int Fac_equ; //FACTOR DE EQUILIBRIO
   struct nodo_arbol *derecho;
   struct nodo_arbol *izquierdo;
   struct nodo_arbol *padre;
} nodoArbol;


typedef nodoArbol *pNodo;
typedef nodoArbol *Arbol;

Arbol ArbolInt = NULL;


// Funciones con árboles:
// Insertar en árbol ordenado:
void Insertar(Arbol *a, int dat);


// Borrar un elemento:
void Borrar(Arbol *a, int dat);

// Función de búsqueda:
int Buscar(Arbol a, int dat);

// Comprobar si el árbol está vacío:
int Vacio(Arbol nodo);

// Comprobar si es un nodo hoja:
int EsHoja(pNodo nodo);

// Contar número de nodos:
int NumeroNodos(Arbol a, int* c);

// Aplicar una función a cada elemento del árbol:
void InOrden(Arbol arbol, void (*func)(int*));
void InOrdenPersona( ArbolPersonas arbol , void (*func)(int*, char*));

void PreOrden(Arbol, void (*func)(int*));
void PostOrden(Arbol, void (*func)(int*));

// Funciones de equilibrado:
void Equilibrar(Arbol *raiz, pNodo nodo, int, int);
void EquilibrarArbolPersonas( ArbolPersonas *arbol, pNodoPersonas nodo, int, int );

void RSI(Arbol *raiz, pNodo nodo);
void RSD(Arbol *raiz, pNodo nodo);
void RDI(Arbol *raiz, pNodo nodo);
void RDD(Arbol *raiz, pNodo nodo);

// Funciones auxiliares:
void Mostrar(int *d);
int isNumero( char * st );
