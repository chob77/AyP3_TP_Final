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
	printf( "\n\nSISTEMA DE GESTI%cN DE CR%cDITOS",acento_O ,acento_E );
    printf( "\n\nOPCIONES DISPONIBLES PARA LA GESTI%cN DE CR%cDITOS:", acento_O, acento_E );

    printf( "\n\n\t1.CREAR CR%cDITO", acento_E );
    printf( "\n\n\t2.LISTAR CR%cDITOS EXISTENTES", acento_E );
	printf( "\n\n\t3.INGRESAR PAGO PARCIAL" );
	printf( "\n\n\t4.CANCELAR CR%cDITO", acento_E );
    printf( "\n\n\t0.VOLVER\n" );
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

            case 3: //OPCION 3 INGRESAR PAGO PARCIAL
                procesarPagoParcial();
                break;

            case 4: //OPCION 4 CANCELAR CRÉDITO
                mostrar_menu_creditos( );
                break;

            default:
                clrscr();
                break;
        }
    }	while( opcion !=0 );
}



/** RECORRE EL ARCHIVO DE CRÉDITOS Y CARGA LA LISTA */
void cargarCreditos()
{
	listaCreditoCliente = &listaCreCli;;
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
				case 1: credito.id = atoi( dato ); break;
				case 2: credito.dni = atoi( dato ); break;
				case 3: credito.estado = atoi( dato );  break;
				case 4: strcpy( credito.fechalta, dato ); break;
				case 5: credito.monto = atof( dato );  break;
				case 6:
					credito.moneda = atoi( dato );
					if ( credito.moneda == PESOS ) gTotalPrestamoPesos += credito.monto;
					if ( credito.moneda == DOLARES ) gTotalPrestamoDolares += credito.monto;
					break;

				case 7: credito.cuotas  = atoi( dato ); break;
				case 8:
					credito.saldo = atof( dato );
					if ( credito.moneda == PESOS ) gTotalDeudaPesos += credito.saldo;
					if ( credito.moneda == DOLARES ) gTotalDeudaDolares += credito.saldo;

					agregarElementoListaCredito( listaCreditoCliente, credito.dni, credito ); //CREA LA LISTA SIMPLE DE CLIENTES Y CREDITOS
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
	credito.id = 1;
	credito.dni = 0;
	credito.estado = ACTIVO;
	strcpy( credito.fechalta, "00/00/0000" );
	credito.monto = 0;
	credito.moneda = PESOS;
	credito.cuotas = 0;
	credito.saldo = 0;
	credito.pagos = NULL;
	return credito;
}



/** ALMACENA UN NUEVO CRÉDITO */
void almacenarCredito( Credito credito )
{
	printf("\nCREDITO RECIBIDO: %d, %d, %d, %s, %.2f, %s, %d, %.2f", credito.id, credito.dni, credito.estado, credito.fechalta, credito.monto, (credito.moneda==0?"PESOS":"DOLARES"), credito.cuotas, credito.saldo);

	FILE *c;
	if (  !existenCreditosAlmacenados() ) //DETECTA QUE ES EL PRIMER CRÉDITO DEL SISTEMA Y CREA EL ARCHIVO
	{
		c = abrirArchivoEscritura( archivoCreditos );
        fprintf( c, "%d;%d;%d;%s;%.2f;%d;%d;%.2f", credito.id, credito.dni, credito.estado, credito.fechalta, credito.monto, credito.moneda, credito.cuotas, credito.saldo);
        fclose( c );
	}
	else
	{
		c = abrirArchivoEscrituraContinua( archivoCreditos );
		fprintf( c, "%d;%d;%d;%s;%.2f;%d;%d;%.2f", credito.id, credito.dni, credito.estado, credito.fechalta, credito.monto, credito.moneda, credito.cuotas, credito.saldo);
		fclose( c );
	}
	gTotalCreditos++;
}



/** CREA UN NUEVO CRÉDITO */
void crearNuevoCredito()
{
/* CRÉDITOS: ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO */

	clrscr();
	printf("\n\tDAR DE ALTA UN NUEVO CR%cDITO", acento_E);
	Credito credito = inicializarCredito();
	credito.id = obtenerTamanioListaCredito( listaCreditoCliente );
	credito.estado = ACTIVO;
	obtenerFecha( credito.fechalta );


	int correcto;
	do
	{
		correcto = 1;
		printf("\n\n\tINGRESA EL DNI DEL CLIENTE: ");
		scanf( "%d", &credito.dni );
		if ( !isIn( arrayDNIClientesActivos, credito.dni, LEN_ARR( arrayDNIClientesActivos ) ))
		{
			printf("\n\t*** EL DNI INGRESADO NO PERTENECE A UN CLIENTE ACTIVO. INTENTA CARGAR OTRO. ***");
			correcto = 0;
		}
		else
		{
			//int cantidadCreditosCliente = obtenerCreditosCliente( credito.dni );
			if ( obtenerCreditosCliente( credito.dni ) >= LIMITE_CREDITO_POR_PERSONA_SIMULTANEOS )
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


	Persona persona = obtenerPersonaDNI( ArbolClientes, credito.dni );
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

	agregarElementoListaCredito( listaCreditoCliente, credito.dni, credito );
	almacenarCredito( credito );

	pause();
}



/** OBTIENE LA DEUDA EN PESOS DE UN CLIENTE */
double obtenerDeudaPesos( int dni )
{
	double deudaPesos = 0;
	ListaCreditoCliente *miLista = listaCreditoCliente;

	while( miLista != NULL )
	{
		if ( miLista->cliente == dni && miLista->credito.moneda == PESOS ) deudaPesos += miLista->credito.saldo;
		miLista = miLista->siguiente;

	}
	return deudaPesos;
}



/** OBTIENE LA DEUDA EN DOLARES DE UN CLIENTE */
double obtenerDeudaDolares( int dni )
{
	double deudaDolares = 0;
	ListaCreditoCliente *miLista = listaCreditoCliente;

	while( miLista != NULL )
	{
		if ( miLista->cliente == dni && miLista->credito.moneda == DOLARES ) deudaDolares += miLista->credito.saldo;
		miLista = miLista->siguiente;
	}
	return deudaDolares;
}




/** DEVUELVE LA CANTIDAD DE RÉDITOS DE UN CLIENTE */
int obtenerCreditosCliente( int dni )
{
	int c = 0;
	ListaCreditoCliente *miLista = listaCreditoCliente;

	while( miLista != NULL )
	{
		if ( miLista->cliente == dni  ) c++;
		miLista = miLista->siguiente;
	}
	return c;
}




void procesarPagoParcial()
{
	clrscr();
	int dni=0;
	printf("\nPROCESAR PAGO DE CR%cDITO.", acento_E);
	printf("\n--------------------------------------", acento_E);

	Pago pago;
	do
	{
		printf("\nINGRESA EL DNI DEL CLIENTE: ");
		scanf("%d", &dni );
	}	while( dni == 0);

	int totalCreditosCliente = listarCreditosDNI( listaCreditoCliente, dni );

	pago.dni = dni;

	if ( totalCreditosCliente ==1 )
	{
		int idCredito = obtenerIDCreditoCliente( listaCreditoCliente, dni ); //SOLO SE LA UTILIZA CUANO EL CLIENTE POSEE UN ÚNICO CRÉDITO ACTIVO
		Credito *credito = obtenerDireccionCredito( listaCreditoCliente, idCredito );

		do
		{
			printf("\n\tINGRESA EL MONTO DEL PAGO A REALIZAR: ");
			scanf("%d", &pago.monto );
		}	while( pago.monto==0 );

		credito->saldo -= pago.monto;	//ACTUALIZO EL SALDO DE LA DEUDA
	}



	pause();
}











