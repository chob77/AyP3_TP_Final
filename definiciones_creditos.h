/*
 * definiciones_creditos.h
 *
 *  Created on: 27 abr. 2019
 *      Author: chob
 */


typedef struct structCredito
{
	unsigned int dni;
	unsigned int id;
	unsigned int moneda;
	double monto;
	double tna;
	double pagos[ 50 ];
	double saldo;
	unsigned int estado;
	char *fechalta[ 8 ]; //06.06.19
	unsigned int cuotas;
}	Credito;

enum {PESOS, DOLARES};
enum {ACTIVO, CANCELADO, FINALIZADO, MORA, ADEUDADO};

/* CRÉDITOS:
	DNI	(clave)	//IDENTIFICACIÓN DEL PROPIETARIO. UN CLIENTE PUEDE TENER MÁS DE UN CRÉDITO
	FECHALTA	//FECHA DE CREACIÓN
	ID			//AUTOINCREMENTAL
	MONTO		//MONTO PRESTADO
	MONEDA		//PESOS-DOLARES
	PAGOS		//ARRAY DE PAGOS REALIZADOS
	SALDO		//MONTO ADEUDADO
	ESTADO		//ACTIVO-CANCELADO
	CUOTAS		//MESES PARA CANCELAR LA DEUDA
	TNA			//TASA NOMINAL ANUAL

	PROTOTIPO JSON:
	{
		dni:{
			id:{
				"moneda":"",
				"monto":"",
				"tna":"",
				"pagos":[],
				"saldo":"",
				"estado":"",
				"fechalta":"",
				"cuotas":""
				}
			}
		}
	}
*/
