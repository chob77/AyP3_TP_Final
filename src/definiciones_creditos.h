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
	char fechalta[ 10 ]; // dd/mm/yyyy
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


/*	CRÉDITOS:
	ID			//AUTOINCREMENTAL
	DNI	(clave)	//IDENTIFICACIÓN DEL PROPIETARIO. UN CLIENTE PUEDE TENER MÁS DE UN CRÉDITO
	ESTADO		//ACTIVO-CANCELADO
	FECHALTA	//FECHA DE CREACIÓN
	MONTO		//MONTO PRESTADO
	MONEDA		//PESOS-DOLARES
	CUOTAS		//MESES PARA CANCELAR LA DEUDA
	SALDO		//MONTO ADEUDADO
	PAGOS		//ARRAY DE PAGOS REALIZADOS
*/

/*	PAGOS:		//ALMACENA LOS PAGOS REALIZADOS POR UN CLIENTE
 *  ID_PAGO     //CORRELATIVO
 *  DNI         //PERSONA
 *  ID_CREDITO  //IDENTIFOCADOR DE CRÉDITO
 *  FECHA_PAGO  //FECHA
 *  MONTO       //MONTO PAGADO
 *  TIPO_PAGO   //EFECTIVO-TARJETA-CHEQUE
 *  MONEDA      //PESOS-DOLARES
*/



void parcerarLineaArchivoCredito( char linea[1024] );
Credito inicializarCredito();
Credito IngresarDatosCredito();
double obtenerDeudaPesos( int dni );
double obtenerDeudaDolares( int dni );

