/*
 * definiciones.h
 *
 *  Created on: 27 abr. 2019
 *      Author: chob
 */


typedef struct structPersona
{
	unsigned int dni;
	char nombre[20];
	char apellido[20];
	unsigned int edad;
	double ingresos;
	struct structCredito *creditos[ PLAZO_MINIMO_CREDITO ];
	struct structPersona *referido;
}	Persona;

/* PERSONAS:
	DNI	(clave)
	NOMBRE
	APELLIDO
	EDAD
	INGRESOS
	CRÉDITOS
	REFERIDOS	//ARRAY DE PERSONAS REFERIDAS

	PROTOTIPO JSON:
	{
		dni:{
			"nombre":"",
			"apellido":"",
			"edad":"",
			"ingresos":"",
			"creditos":[],
			"referidos":[]
		}
	}
*/
