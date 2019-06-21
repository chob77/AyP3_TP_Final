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


 /* PERSONAS:
	DNI	(clave)
	NOMBRE
	APELLIDO
	EDAD
	INGRESOS
	CRÉDITOS    //ARRAY DE CRÉDITOS
	REFERIDOS
	ESTADO
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
	unsigned int estado;
}	Persona;


typedef struct structPersonaArbol
{
	int dni;        //IDENTIFICADOR DE PERSONA
	int Fac_equ;    //FACTOR DE EQUILIBRIO
	struct structPersona persona;
	struct structPersonaArbol *derecho;
	struct structPersonaArbol *izquierdo;
	struct structPersonaArbol *padre;
}	nodoArbolPersona;


typedef nodoArbolPersona *pNodoPersonas;
typedef nodoArbolPersona *ArbolPersonas;

ArbolPersonas ArbolClientes = NULL;
ArbolPersonas ArbolClientesInactivos = NULL;
ArbolPersonas ArbolEdadClientes = NULL;

int arrayDNIClientesActivos[ 800 ];		//INTENTA SER UNA ESTRUCTURA DE BUSQUEDA RÁPIDA DE LA EXISTENCIA DE UN CLIENTE
int arrayDNIClientesInactivos[ 800 ];	//INTENTA SER UNA ESTRUCTURA DE BUSQUEDA RÁPIDA DE LA EXISTENCIA DE UN CLIENTE

int countInOrderEdad = 0;
int countInOrder = 0;
int clientesCargados = FALSE;
int dniAmigo = 0;
int hayClienteInactivoNuevo = FALSE;
int hayClienteActivoNuevo = FALSE;

int InsertarPersonaArbol( ArbolPersonas *arbol, int dni, Persona persona );
int VacioPersonas( ArbolPersonas arbol );

Persona inicializarPersona();
Persona ingresarDatosPersona();
int obtenerTotalPersonas();

void parcerarDNIArchivo( char linea[1024], ArbolPersonas *arbol );
void parcerarEDADArchivo( char linea[1024], ArbolPersonas *arbol );

void cargarArchivoTemporalClientesActivos( char *linea );
void parcerarLineaArchivoPorAmigo( char *linea, Persona *listaPersonas, int pos_persona );
void concatenarClientes();
Persona obtenerPersonaDNI( ArbolPersonas arbol, int dni );

void cargarArbolClientes( ArbolPersonas *arbol, const char *filename );
void cargarArbolEDADClientes( ArbolPersonas *arbol, const char *filename );

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


