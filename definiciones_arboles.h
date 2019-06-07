/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019. 
 *
 * TRABAJO PRÁCTICO: ÁRBOLES BINARIOS DE BÚSQUEDA.
 * FILE: definiciones_arboles.c
 *
 *  CREATED ON: 26 may. 2019
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
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;

Arbol ArbolInt = NULL;

// Funciones con árboles:
// Insertar en árbol ordenado:
void Insertar(Arbol *a, int dat);

// Borrar un elemento:
void Borrar(Arbol *a, int dat);

// Función de búsqueda:
int Buscar(Arbol a, int dat);

// Comprobar si el árbol está vacío:
int Vacio(Arbol r);

// Comprobar si es un nodo hoja:
int EsHoja(pNodo r);

// Contar número de nodos:
int NumeroNodos(Arbol a, int* c);

// Aplicar una función a cada elemento del árbol:
void InOrden(Arbol, void (*func)(int*));
void PreOrden(Arbol, void (*func)(int*));
void PostOrden(Arbol, void (*func)(int*));

// Funciones de equilibrado:
void Equilibrar(Arbol *raiz, pNodo nodo, int, int);
void RSI(Arbol *raiz, pNodo nodo);
void RSD(Arbol *raiz, pNodo nodo);
void RDI(Arbol *raiz, pNodo nodo);
void RDD(Arbol *raiz, pNodo nodo);

// Funciones auxiliares:
void Mostrar(int *d);
int isNumero( char * st );