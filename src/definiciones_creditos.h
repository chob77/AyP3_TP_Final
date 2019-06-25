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


typedef struct structPago
{
	unsigned int idPago;
	unsigned int idCredito;
	unsigned int dniCliente;
	char fechalta[ 10 ]; // dd/mm/yyyy
	double monto;
}	Pago;



typedef struct structCredito
{
	unsigned int idCredito;
	unsigned int dniCliente;
	unsigned int estado;
	char fechalta[ 10 ]; // dd/mm/yyyy
	double monto;
	unsigned int moneda;
	unsigned int cuotas;
	double saldo;
}	Credito;



/*	CRÉDITOS:
	ID			//AUTOINCREMENTAL
	DNI	(clave)	//IDENTIFICACIÓN DEL PROPIETARIO. UN CLIENTE PUEDE TENER MÁS DE UN CRÉDITO
	ESTADO		//ACTIVO-CANCELADO
	FECHALTA	//FECHA DE CREACIÓN
	MONTO		//MONTO PRESTADO
	MONEDA		//PESOS-DOLARES
	CUOTAS		//MESES PARA CANCELAR LA DEUDA
	SALDO		//MONTO ADEUDADO
*/
/*	PAGOS:		//ALMACENA LOS PAGOS REALIZADOS POR UN CLIENTE
 *  ID_PAGO     //CORRELATIVO
 *  DNI         //PERSONA
 *  ID_CREDITO  //IDENTIFOCADOR DE CRÉDITO
 *  FECHA_PAGO  //FECHA
 *  MONTO       //MONTO PAGADO
*/



Credito inicializarCredito();
Credito IngresarDatosCredito();
Pago inicializarPago();

double obtenerDeudaPesos( int dni );
double obtenerDeudaDolares( int dni );

void parcerarLineaArchivoCredito( char linea[1024] );
void CancelarCredito();
void cargarListaPagos( Pago pago );

