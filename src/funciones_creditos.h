/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: funciones_creditos.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */



/**
*	MUESTRA EL MANÚ PARA MANEJAR LAS UTILIDADES CON LAS PERSONAS
*/
void mostrar_menu_creditos( )
{
    clrscr();
    SetColores( COLOR_CREDITOS );
	printf( "\n\n\tSISTEMA DE GESTI%cN DE CR%cDITOS",acento_O ,acento_E );
    printf( "\n\n\tOPCIONES DISPONIBLES PARA LA GESTI%cN DE CR%cDITOS:", acento_O, acento_E );

    printf( "\n\n\t\t1.CREAR CR%cDITO", acento_E );
    printf( "\n\n\t\t2.LISTAR CR%cDITOS EXISTENTES", acento_E );
    printf( "\n\n\t\t3.LISTAR CR%cDITOS DE UN CLIENTE", acento_E );
	printf( "\n\n\t\t4.INGRESAR PAGO CUOTA" );
	printf( "\n\n\t\t5.CANCELAR CR%cDITO", acento_E );
    printf( "\n\n\t\t0.VOLVER\n" );
}



/** ADMINISTRA LA GESTIÓN DE CRÉDITOS */
void opcionesMenuCreditos()
{
    int opcion;
    do
    {
        mostrar_menu_creditos( );
        opcion = OpcionElegida();

        switch ( opcion )
        {
            case 1: //OPCION 1 CREAR CRÉDITO
                crearNuevoCredito();
                break;

            case 2: //OPCION 2 LISTAR CRÉDITOS EXISTENTES

                listarCreditos( listaCreditoCliente );
                pause();
                break;

            case 3: //OPCION 3 LISTAR CRÉDITO DE UN CLIENTE
                clrscr();
				printf("\n\n\t\tLISTA DE CR%cDITOS DEL CLIENTE.", acento_E );
				int dni=0;
				do
				{
					printf("\n\nINGRESA EL DNI DEL CLIENTE: ");
					scanf("%d", &dni );
				}	while( dni == 0);

				int totalCreditosCliente = listarCreditosDNI( listaCreditoCliente, dni );	//MUESTRA LA LISTA DE CRÉDITOS DEL CLIENTE INGRESADO
				pause();
                break;

            case 4: //OPCION 4 INGRESAR PAGO CUOTA
                procesarPagoParcial();
                break;

            case 5: //OPCION 5 CANCELAR CRÉDITO
                cancelarCredito();
                break;

            default:
                clrscr();
                break;
        }
    }	while( opcion !=0 );
}



/** RECORRE EL ARCHIVO DE CRÉDITOS Y CARGA LA LISTA */
void cargarArchivoCreditos()
{
	listaCreditoCliente = &listaCreCli;
	if ( existenCreditosAlmacenados() )
	{
		FILE *file = abrirArchivoLectura( archivoCreditos );
		nroLineaArchivo = 0;
		gTotalCreditos = 0;
		gTotalPrestamoPesos = 0;
		gTotalPrestamoDolares = 0;
		gTotalDeudaPesos = 0;
		gTotalDeudaDolares = 0;

		char linea[1024];
		while( fgets(linea, 1024, file) )
		{
			int n = strlen( linea );
			linea[n-1] = 0;         //ELIMINACIÓN DEL \n
			parcerarLineaArchivoCredito( linea );
		}
		fclose( file );
	}
}



/** RECORRE EL ARCHIVO DE CRÉDITOS Y CARGA LA LISTA */
void cargarArchivoPagos()
{
	if ( existenPagosAlmacenados() )
	{
		FILE *file = abrirArchivoLectura( archivoPagos );

		char linea[1024];
		arrayCreditoPagos = NULL;
		listaPagoCliente = NULL;

		while( fgets(linea, 1024, file) )
		{
			int n = strlen( linea );
			linea[n-1] = 0;         //ELIMINACIÓN DEL \n
			parcerarLineaArchivoPagos( linea );
		}
		fclose( file );
	}
}



/** PARCEA CADA LÍNEA DEL CSV DE CRÉDITOS*/
void parcerarLineaArchivoPagos( char linea[1024] )
{
	int ln = strlen( linea );
	int cuentaDato = 0;
	char dato[ 100 ], caracter;
	int i = 0, j = 0;

	Pago pago = inicializarPago();

	for ( i = 0; i <= ln; i++ )
	{
		caracter = linea[i];
		if ( caracter != ';' && caracter != 0 )
		{
			dato[ j ] = caracter;
			dato[ j + 1 ] = 0;//FORMA UNA CADENA
			j++;
		}
		else
		{
			j = 0;
			cuentaDato++;

/* CRÉDITOS: ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO */

			switch ( cuentaDato )
			{
				case 1: pago.idPago = atoi( dato ); break;
				case 2: pago.idCredito = atoi( dato );  break;
				case 3: pago.dniCliente = atoi( dato ); break;
				case 4: strcpy( pago.fechalta, dato ); break;
				case 5:
					pago.monto = atof( dato );

					cargarListaPagos ( pago );

					cuentaDato = 0;
					break;
			}
			strcpy( dato, "" );
		}
	}
}



/** PARCEA CADA LÍNEA DEL CSV DE CRÉDITOS*/
void parcerarLineaArchivoCredito( char linea[1024] )
{
	int ln = strlen( linea );
	int cuentaDato = 0;
	char dato[ 100 ], caracter;
	int i = 0, j = 0;

	Credito credito = inicializarCredito();

	for ( i = 0; i <= ln; i++ )
	{
		caracter = linea[i];
		if ( caracter != ';' && caracter != 0 )
		{
			dato[ j ] = caracter;
			dato[ j + 1 ] = 0;//FORMA UNA CADENA
			j++;
		}
		else
		{
			j = 0;
			cuentaDato++;

/* CRÉDITOS: ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO */

			//printf("\nDATO: %s", dato );
			switch ( cuentaDato )
			{
				case 1: credito.idCredito = atoi( dato ); break;
				case 2: credito.dniCliente = atoi( dato ); break;
				case 3: credito.estado = atoi( dato );  break;
				case 4: strcpy( credito.fechalta, dato ); break;
				case 5: credito.monto = atof( dato );  break;
				case 6:
					credito.moneda = atoi( dato );
					if ( credito.estado == ACTIVO && credito.moneda == PESOS ) gTotalPrestamoPesos += credito.monto;
					if ( credito.estado == ACTIVO && credito.moneda == DOLARES ) gTotalPrestamoDolares += credito.monto;
					break;

				case 7: credito.cuotas  = atoi( dato ); break;
				case 8:
					credito.saldo = atof( dato );
					if ( credito.estado == ACTIVO && credito.moneda == PESOS ) gTotalDeudaPesos += credito.saldo;
					if ( credito.estado == ACTIVO && credito.moneda == DOLARES ) gTotalDeudaDolares += credito.saldo;

					if ( credito.estado == INCOBRABLE && credito.moneda == PESOS ) gTotalDeudaPesosIncobrable += credito.saldo;
					if ( credito.estado == INCOBRABLE && credito.moneda == DOLARES ) gTotalDeudaDolaresIncobrable += credito.saldo;

					if ( credito.estado == ACTIVO )
					{
						arrayCreditos = agregraArrayCreditoPagos( arrayCreditos, credito.idCredito );
						agregarElementoListaCredito( listaCreditoCliente, credito.dniCliente, credito ); //CREA LA LISTA SIMPLE DE CLIENTES Y CREDITOS
					}

					cuentaDato = 0;
					break;
			}
			strcpy( dato, "" );
		}
	}
	//printf("\nCREDITO CREADO: %d, %d, %d, %s, %.2f, %d, %d, %.2f", credito.id, credito.dni, credito.estado, credito.fechalta, credito.monto, credito.moneda, credito.cuotas, credito.saldo);
	//pause();
	gTotalCreditos++;
}



/** INICIALIZA UN CRÉDITO GENÉRICO */
Credito inicializarCredito()
{
/* CRÉDITOS: ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO */
	Credito credito;
	credito.idCredito = 1;
	credito.dniCliente = 0;
	credito.estado = ACTIVO;
	strcpy( credito.fechalta, "00/00/0000" );
	credito.monto = 0;
	credito.moneda = PESOS;
	credito.cuotas = 0;
	credito.saldo = 0;
	return credito;
}



/** INICIALIZA UN CRÉDITO GENÉRICO */
Pago inicializarPago()
{
/* CRÉDITOS: ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO */
	Pago pago;
	pago.idPago = 0;
	pago.idCredito = 0;
	pago.dniCliente = 0;
	strcpy( pago.fechalta, "00/00/0000" );
	pago.monto = 0;
	return pago;
}



/** ALMACENA UN NUEVO CRÉDITO */
void almacenarCredito( Credito credito )
{
	//printf("\nCREDITO RECIBIDO: %d, %d, %d, %s, %.2f, %s, %d, %.2f", credito.id, credito.dni, credito.estado, credito.fechalta, credito.monto, (credito.moneda==0?"PESOS":"DOLARES"), credito.cuotas, credito.saldo);

	FILE *c;
	if (  !existenCreditosAlmacenados() ) //DETECTA QUE ES EL PRIMER CRÉDITO DEL SISTEMA Y CREA EL ARCHIVO
	{
		c = abrirArchivoEscritura( archivoCreditos );
        fprintf( c, "%d;%d;%d;%s;%.2f;%d;%d;%.2f\n", credito.idCredito, credito.dniCliente, credito.estado, credito.fechalta, credito.monto, credito.moneda, credito.cuotas, credito.saldo);
        fclose( c );
	}
	else
	{
		c = abrirArchivoEscrituraContinua( archivoCreditos );
		fprintf( c, "%d;%d;%d;%s;%.2f;%d;%d;%.2f\n", credito.idCredito, credito.dniCliente, credito.estado, credito.fechalta, credito.monto, credito.moneda, credito.cuotas, credito.saldo);
		fclose( c );
	}
	printf("\nEL CR%cDITO SE CRE%c CON %cXITO.", acento_E, acento_O, acento_O );
	gTotalCreditos++;
}



/** ALMACENA UN NUEVO CRÉDITO */
void almacenarPago( Pago pago )
{
	//printf("\nPAGO RECIBIDO: %d, %d, %d, %s, %.2f", pago.id, pago.id_credito, pago.dni, pago.fechalta, pago.monto );

	FILE *c;
	if (  !existenPagosAlmacenados() ) //DETECTA QUE ES EL PRIMER CRÉDITO DEL SISTEMA Y CREA EL ARCHIVO
	{
		c = abrirArchivoEscritura( archivoPagos );
        fprintf( c, "%d;%d;%d;%s;%.2f\n", pago.idPago, pago.idCredito, pago.dniCliente, pago.fechalta, pago.monto);
        fclose( c );
	}
	else
	{
		c = abrirArchivoEscrituraContinua( archivoPagos );
		fprintf( c, "%d;%d;%d;%s;%.2f\n", pago.idPago, pago.idCredito, pago.dniCliente, pago.fechalta, pago.monto);
		fclose( c );
	}
}



/** CREA UN NUEVO CRÉDITO */
void crearNuevoCredito()
{
/* CRÉDITOS: ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO */

	clrscr();
	printf("\n\tDAR DE ALTA UN NUEVO CR%cDITO", acento_E);
	Credito credito = inicializarCredito();
	credito.idCredito = obtenerTamanioListaCredito( listaCreditoCliente );
	credito.estado = ACTIVO;
	obtenerFecha( credito.fechalta );


	int correcto;
	do
	{
		correcto = 1;
		printf("\n\n\tINGRESA EL DNI DEL CLIENTE: ");
		scanf( "%d", &credito.dniCliente );
		if ( !isIn( arrayDNIClientesActivos, credito.dniCliente, LEN_ARR( arrayDNIClientesActivos ) ))
		{
			printf("\n\t*** EL DNI INGRESADO NO PERTENECE A UN CLIENTE ACTIVO. INTENTA CARGAR OTRO. ***");
			correcto = 0;
		}
		else
		{
			if ( obtenerCreditosCliente( credito.dniCliente ) >= LIMITE_CREDITO_POR_PERSONA_SIMULTANEOS )
			{
				printf("\n\t*** EL DNI INGRESADO ALCANZ%c EL L%cMITE DE CR%cDITOS PERMITIDOS POR PERSONA. INTENTA CARGAR OTRO. ***", acento_O, acento_I, acento_E );
				correcto = 0;
			}
		}
	}	while ( correcto == 0 );


	do
	{
		printf("\n\tSELECCIONE LA MONEDA DEL PR%cSTAMO:", acento_E );
		printf("\n\t1. PESOS" );
		printf("\n\t2. DOLARES" );
		printf("\n\tINGRESE UNA OPCI%cN: ", acento_O );
		scanf("%d", &credito.moneda );
	}	while( credito.moneda < 1 && credito.moneda > 2 );
	credito.moneda--;


	Persona persona = obtenerPersonaDNI( ArbolClientes, credito.dniCliente );
	double ingresos = persona.ingresos *  PORCENTAJE_DE_INGRESOS_A_CEDER;

	do
	{
		correcto = 1;
		printf("\n\tINGRESA EL MONTO DEL CR%cDITO OTORGADO ( $%.2f M%cXIMO ): ", acento_E, ingresos, acento_A);
		scanf("%lf", &credito.monto );

		if ( credito.monto <= 0 )
		{
			printf("\n*** EL MONTO DEBE SER MAYOR QUE CERO. ***");
			correcto= 0;
		}

		if ( credito.monto > ingresos )
		{
			printf("\n*** EL MONTO DEBE SER MENOR AL 70\% DE LOS INGRESOS DECLARADOS POR EL CLIENTE. ***");
			correcto= 0;
		}

	}	while ( correcto == 0 );


	do
	{
		correcto = 1;
		printf("\n\tINGRESA LAS CUOTAS: ");
		scanf( "%d", &credito.cuotas );

		if ( credito.cuotas > PLAZO_MAXIMO_CREDITO && credito.cuotas < PLAZO_MINIMO_CREDITO )
		{
			printf("\n\t*** LA CANTIDAD DE CUOTAS NO CUMPLEN LA POL%cTICA DE LA EMPRESA. ***.",acento_I );
			correcto= 0;
		}
	}	while ( correcto == 0 );


	do
	{
		correcto = 1;
		printf("\n\tINGRESA EL MONTO DE ANTICIPO ( cero si no hay ): ");
		scanf( "%lf", &credito.saldo );

		if ( credito.saldo < 0 )
		{
			printf("\n\t*** EL MONTO INGRESADO NO PUEDEN SER MENOR QUE CERO. ***.");
			correcto= 0;
		}
	}	while ( correcto == 0 );

	credito.saldo = credito.monto - credito.saldo; //SI HUBO UN ANTICIPO ACTUALIZO EL SALDO
	credito.saldo = ( credito.saldo / credito.cuotas) * INTERES_POR_CUOTA * credito.cuotas; //SE CALCULA EL SALDO ADEUDADO CON LA GANANCIA AGREGADA

	//printf("\nCREDITO CREADO: %d, %d, %d, %s, %.2f, %s, %d, %.2f", credito.id, credito.dni, credito.estado, credito.fechalta, credito.monto, (credito.moneda==0?"PESOS":"DOLARES"), credito.cuotas, credito.saldo);

	agregarElementoListaCredito( listaCreditoCliente, credito.dniCliente, credito );
	almacenarCredito( credito );

	pause();
}



/** OBTIENE LA DEUDA EN PESOS DE UN CLIENTE */
double obtenerDeudaPesos( int dni )
{
	double deudaPesos = 0;
	ListaCreditosClientes *miLista = listaCreditoCliente;

	while( miLista != NULL )
	{
		if ( miLista->dniCliente == dni && miLista->credito.moneda == PESOS ) deudaPesos += miLista->credito.saldo;
		miLista = miLista->siguiente;

	}
	return deudaPesos;
}



/** OBTIENE LA DEUDA EN DOLARES DE UN CLIENTE */
double obtenerDeudaDolares( int dni )
{
	double deudaDolares = 0;
	ListaCreditosClientes *miLista = listaCreditoCliente;

	while( miLista != NULL )
	{
		if ( miLista->dniCliente == dni && miLista->credito.moneda == DOLARES ) deudaDolares += miLista->credito.saldo;
		miLista = miLista->siguiente;
	}
	return deudaDolares;
}




/** DEVUELVE LA CANTIDAD DE CRÉDITOS DE UN CLIENTE */
int obtenerCreditosCliente( int dni )
{
	int c = 0;
	ListaCreditosClientes *miLista = listaCreditoCliente;

	while( miLista != NULL )
	{
		if ( miLista->dniCliente == dni  ) c++;
		miLista = miLista->siguiente;
	}
	return c;
}




void procesarPagoParcial()
{
	clrscr();
	int dni=0;
	printf("\nPROCESAR PAGO DE CUOTA." );
	printf( "\n--------------------------------------" );

	Credito *credito;
	Pago pago = inicializarPago();
	pago.idPago = obtenerSiguienteIDPago();
	obtenerFecha( pago.fechalta );

	do
	{
		printf("\nINGRESA EL DNI DEL CLIENTE: ");
		scanf("%d", &dni );
	}	while( dni == 0);

	int totalCreditosCliente = listarCreditosDNI( listaCreditoCliente, dni );	//MUESTRA LA LISTA DE CRÉDITOS DEL CLIENTE INGRESADO

	pago.dniCliente = dni;
	int idCredito = 0;

	if ( totalCreditosCliente ==1 )		//EL CLIENTE POSEE UN ÚNICO CRÉDITO ACTIVO
	{
		idCredito = obtenerIDCreditoCliente( listaCreditoCliente, dni ); //SOLO SE LA UTILIZA CUANO EL CLIENTE POSEE UN ÚNICO CRÉDITO ACTIVO
		credito = obtenerDireccionCredito( listaCreditoCliente, idCredito );
		pago.idCredito = idCredito;

	}
	else if ( totalCreditosCliente > 1 )		//EL CLIENTE TIENE MÁS DE UN CRÉDITO
	{

		do
		{
			printf("\n\tEL CLIENTE POSEE M%cS DE UN CR%cDITO.", acento_A, acento_E );
			printf("\n\tINGREA EL N%cMERO DE CR%cDITO A PAGAR: ", acento_U, acento_E );
			scanf("%d", &idCredito );
		}	while( idCredito == 0 );

		credito = obtenerDireccionCredito( listaCreditoCliente, idCredito );
		pago.idCredito = idCredito;
	}
	else
	{
		clrscr();
		printf("\n\n\n\tEL CLIENTE NO POSEE CR%cDITOS ACTIVOS.", acento_A, acento_E );
		pause();
		return;
	}

	printf("\n\n\n\tEL VALOR DE LA CUOTA DEL CREDITO ES: $%.2f", (credito->saldo/credito->cuotas) );
	do
	{
		printf("\n\tINGRESA EL MONTO DEL PAGO A REALIZAR: ");
		scanf("%lf", &pago.monto );

	}	while( pago.monto <= 0 );

	credito->saldo -= pago.monto;	//ACTUALIZO EL SALDO DE LA DEUDA
	printf("\n\tEL NUEVO SALDO ES: %.2f", credito->saldo );

	almacenarPago( pago );						//SIEMPRE HABRÁ UN NUEVO PAGO PARA AGREGAR AL ARCHIVO

//SE ACTUALIZA LA LISTA ENLAZADA DE PAGOS
	cargarListaPagos( pago );


	if ( credito->saldo == 0 )
	{
		credito->cuotas--; 			//DECREMENTO LA CANTIDAD DE CUOTAS RESTANTES PARA ESE CRÉDITO
		credito->estado = INACTIVO;	//SE LO DESACTIVA PORQUE YA FINALIZPO DE PAGARLO

		printf("\n\n\t\t******************************************************");
		printf("\n\n\t\t***************** FELICITACIONES!! *******************");
		printf("\n\t\t\tEL CLIENTE FINALIZ%c DE PAGAR SU CR%cDITO!!!", acento_O, acento_E);
		printf("\n\n\t\t******************************************************");
	}

	if ( credito->cuotas > 1 )
	{
		credito->cuotas--; //DECREMENTO LA CANTIDAD DE CUOTAS RESTANTES PARA ESE CRÉDITO
	}

	actualizarLineaArchivoCreditos( credito );	 //ACTUALIZA EL SALDO DEL CLIENTE EN EL ARCHIVO


	pause();
}



/** DEVUELVE EL SIGUIENTE ID */
int obtenerSiguienteIDPago()
{
	return obtenerTotalLineasArchivo( archivoPagos );
}



/** DA DE BAJA UN CRÉDITO */
void cancelarCredito()
{
	clrscr();
	int dni=0;
	printf("\nCANCELACI%cN DE CR%cDITO.", acento_O, acento_E );
	printf( "\n--------------------------------------" );

	do
	{
		printf("\nINGRESA EL DNI DEL CLIENTE: ");
		scanf("%d", &dni );
	}	while( dni == 0);

	int totalCreditosCliente = listarCreditosDNI( listaCreditoCliente, dni );	//MUESTRA LA LISTA DE CRÉDITOS DEL CLIENTE INGRESADO

	int idCredito = 0;
	Credito *credito;
	if ( totalCreditosCliente ==1 )		//EL CLIENTE POSEE UN ÚNICO CRÉDITO ACTIVO
	{
		idCredito = obtenerIDCreditoCliente( listaCreditoCliente, dni ); //SOLO SE LA UTILIZA CUANO EL CLIENTE POSEE UN ÚNICO CRÉDITO ACTIVO
		credito = obtenerDireccionCredito( listaCreditoCliente, idCredito );

	}
	else if ( totalCreditosCliente > 1 )		//EL CLIENTE TIENE MÁS DE UN CRÉDITO
	{

		do
		{
			printf("\n\tEL CLIENTE POSEE M%cS DE UN CR%cDITO.", acento_A, acento_E );
			printf("\n\tINGREA EL N%cMERO DE CR%cDITO A CANCELAR: ", acento_U, acento_E );
			scanf("%d", &idCredito );
		}	while( idCredito == 0 );

		credito = obtenerDireccionCredito( listaCreditoCliente, idCredito );
	}
	else
	{
		clrscr();
		printf("\n\n\n\tEL CLIENTE NO POSEE CR%cDITOS ACTIVOS.", acento_A, acento_E );
		pause();
		return;
	}

	printf("\n\tSELECCIONE EL MOTIVO DE LA CANCELACI%cN:", acento_O );
	printf("\n\t\t1.PAGADO" );
	printf("\n\t\t2.CANCELADO" );
	printf("\n\t\t3.MORA" );
	printf("\n\t\t4.INCOBRABLE" );
	printf("\n\t\t0.VOLVER" );

	int opcion = 5;
	do
	{
		printf("\n\tSELECCIONE UNA OPCI%cN: ", acento_O);
		scanf("%d", &opcion );
	}	while( opcion == 5 );

	switch ( opcion )
	{
		case 1: credito->estado = INACTIVO; opcion = 7; break;
		case 2: credito->estado = CANCELADO; opcion = 7; break;
		case 3: credito->estado = MORA; opcion = 7; break;
		case 4: credito->estado = INCOBRABLE; opcion = 7; break;
		default: break;
	}

	if ( opcion == 7 )
	{
		actualizarLineaArchivoCreditos( credito );	 //ACTUALIZA EL ESTADO DEL CLIENTE EN EL ARCHIVO
		opcion = 5;
	}

	pause();
}



/** PROCESA LOS PAGOS DEL ARCHIVO DE PAGOS */
void cargarListaPagos( Pago pago )
{
	ListaPagoCliente *aux;

	if ( isInArrayCreditosPagos( arrayCreditos, pago.idCredito ) ) //VERIFICA SI EL CRÉDITO ESTÁ ACTIVO
	{
		if ( isInArrayCreditosPagos( arrayCreditoPagos, pago.idCredito ) ) //VERIFICA SI EL CRÉDITO YA FUE PROCESADO
		{
			aux = obtenerNodoLista( pago.idCredito );
			aux->pagos = agregrarSubLista( aux->pagos, pago );
		}
		else
		{
			arrayCreditoPagos = agregraArrayCreditoPagos( arrayCreditoPagos, pago.idCredito );
			listaPagoCliente = agregarPagoCredito( pago.idCredito ); //VINCULA CLIENTES Y SUS PAGOS
			aux = obtenerNodoLista( pago.idCredito );
			aux->pagos = agregrarSubLista( aux->pagos, pago );
		}
	}
}
