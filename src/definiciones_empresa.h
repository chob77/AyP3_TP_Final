/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: definiciones_empresa.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */

#define MOYORIA_DE_EDAD 21
#define MAXIMO_NUMERO_CLIENTES 1000

#define	LIMITE_CREDITO_PESOS  1000000
#define	LIMITE_CREDITO_DOLARES  50000
#define	LIMITE_CREDITO_POR_PERSONA_SIMULTANEOS  2 //DOS CRÉDITOS PERMITIDOS
#define	LIMITE_CREDITO_POR_PERSONA_POR_DIA  1

// #define	MONTO_CREDITO_PESOS
// #define	MONTO_CREDITO_DOLARES

#define	PLAZO_MINIMO_CREDITO  3  			//meses
#define	PLAZO_MAXIMO_CREDITO  60 			//meses ( 5 años )

//#define TNA     12
#define	INTERES_POR_CUOTA  1.07	 			//7%
#define	INTERES_POR_MORA  20% 	 			//está en mora cuando se supera el plazo de pago estipulado
#define	INTERES_POR_REFINANCIONACION  15	//15%

#define	PORCENTAJE_DE_INGRESOS_A_CEDER  0.7	//70%
#define	PLUS_POR_REFERIDOS  				//pesos o cuotas?
