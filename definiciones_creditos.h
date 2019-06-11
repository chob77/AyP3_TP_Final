/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: definiciones_creditos.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


typedef struct structCredito
{
	unsigned int id;
	unsigned int dni;
	unsigned int estado;
	char *fechalta[ 10 ]; // dd/mm/yyyy
	double monto;
	unsigned int moneda;
	double saldo;
	unsigned int cuotas;
	struct structPagos *pagos; //LISTA ENLAZADA DE PAGOS REALIZADOS
}	Credito;

typedef struct structPagos
{
	unsigned int id;
	unsigned int dni;
	unsigned int id_credito;
	char *fechalta[ 10 ]; // dd/mm/yyyy
	double monto;
	unsigned int moneda;
	unsigned int tipo_pago;
}	Pago;

enum {PESOS, DOLARES};
enum {ACTIVO, DESACTIVO, CANCELADO, MORA, INCOBRABLE};
enum {EFECTIVO, TARJETA, CHEQUE};

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

*/

/* PAGOS:       //ALMACENA LOS PAGOS REALIZADOS POR UN CLIENTE
 *  ID_PAGO     //CORRELATIVO
 *  DNI         //PERSONA
 *  ID_CREDITO  //IDENTIFOCADOR DE CRÉDITO
 *  FECHA_PAGO  //FECHA
 *  MONTO       //MONTO PAGADO
 *  TIPO_PAGO   //EFECTIVO-TARJETA-CHEQUE
 *  MONEDA      //PESOS-DOLARES
*/
