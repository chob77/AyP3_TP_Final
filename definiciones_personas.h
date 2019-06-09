/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: definiciones_personas.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


typedef struct structPersona
{
	unsigned int dni;
	char nombre[20];
	char apellido[20];
	unsigned int edad;
	unsigned int ingresos;
	struct structCredito *creditosActivos[ LIMITE_CREDITO_POR_PERSONA_SIMULTANEOS ];
	struct structPersona *amigo;
}Persona;


typedef struct structPersonaArbol
{
	int dni;        //IDENTIFICADOR DE PERSONA
	int Fac_equ;    //FACTOR DE EQUILIBRIO
	struct structPersona *persona;
	struct structPersonaArbol *derecho;
	struct structPersonaArbol *izquierdo;
	struct structPersonaArbol *padre;
}	nodo_arbol_Persona;


/*typedef struct structPersonaArbol   //IMPLEMETA UN ÁRBOL DE PERSONAS
{
	Arbol nodo;        //HEREDA UN NODO DE ÁRBOL
	Persona *persona;  //AGREGA UN PUNTERO A UNA PERSONA

}	nodo_arbol_Persona;*/


typedef nodo_arbol_Persona *pNodoPersonas;
typedef nodo_arbol_Persona *ArbolPersonas;
ArbolPersonas ArbolClientes = NULL;

int InsertarPersonaArbol( ArbolPersonas *arbol, int dni, Persona persona );
int VacioPersonas( ArbolPersonas arbol );

/*

typedef struct
{
    // base members

} Base;

typedef struct
{
    Base base;

    // derived members

} Derived;

Como Derivado comienza con una copia de Base, puede hacer esto:
Base *b = (Base *)d;

*/







// struct st *mySt = malloc(sizeof(struct st) + len * sizeof(mySt->arr[0]));
// struct st *mySt = malloc(sizeof(struct structPersona) + len * sizeof(mySt->creditosActivos[0]));

/* PERSONAS:
	DNI	(clave)
	NOMBRE
	APELLIDO
	EDAD
	INGRESOS
	CRÉDITOS
	REFERIDOS	//ARRAY DE PERSONAS REFERIDAS

*/
