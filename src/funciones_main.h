/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: funciones_tp_final.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */



/** LIMPA TODA LA PANTALLA DE LA CONSOLA*/
void clrscr( )
{
    system( "@cls||clear" );
}



/** GENERA UNA PAUSA EN LA EJECUCIÓN DEL PROGRAMA*/
void pause( )
{
    printf( "\n\nPresiona una tecla para continuar!" );
	system( "@pause>nul" );
}



/** MODIFICA LOS COLORES DE LA CONSOLA */
void SetColores( int color )
{
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), color );
}



/** DETERMINA SI UN ELEMENTO EXISTE EN UN ARRAY */
int isIn( int arr[], int val, int len )
{
    int retorno = 0, i=0;

    for( i=0; i<len; i++) if ( arr[i] == val ) retorno = 1;

    return retorno;
}



/** DETERMINA SI UN STRING ES NUMÉRICO */
int isNumero( char * st )
{
	int len = strlen( st );//obtiene el largo del string
    int i;
    for ( i = 0; i < len; i++ ) {
        if ( (( int ) st[i])< 48 || (( int ) st[i]) > 57 ) {//verifica si alguno de los caracteres del string no es un número de la tabla ASCII
            return FALSE;
        }
    }
    return TRUE;
}



/** DEVUELVE LA OPCIÓN ESCOGIDA POR EL USUARIO */
int OpcionElegida()
{
    int opcion;
    printf("\nElija una Opcion: ");
    scanf("%d", &opcion);
    return opcion;
}



/** DEVUEVE LA FECHA ACTUAL */
void obtenerFecha( char fecha[10] )
{
	time_t t;
	struct tm *tm;
	t=time(NULL);
	tm=localtime(&t);
	strftime( fecha, 100, "%d/%m/%Y", tm );
}



/**
*	MUESTRA EL MANÚ SPLAS DEL PROGRAMA
*	MUESTRA UN RESUMEN DEL SISTEMA PARA HACER TIEMPO AL ABRIR TODA LA INFO
*/
void mostrar_menu_splash( )
{
    SetColores( COLOR_SPLASH );
    printf( "\n\n\tAGUARDA UN MOMENTO MIENTRAS SE CARGA LA INFORMACI%cN.", acento_O );

    gTotalClientes = 0;
    gTotalCreditos = 0;
	gTotalPrestamoPesos = 0;
	gTotalPrestamoDolares = 0;
	gTotalDeudaPesos = 0;
	gTotalDeudaDolares = 0;
	gTotalDeudaDolaresIncobrable = 0;
	gTotalDeudaDolaresIncobrable = 0;
	listaCreditoCliente = NULL;

	cargarArchivoCreditos();	//CARGA LOS CRÉDITOS DESDE EL ARCHIVO
	cargarArchivoPagos();		//CARGA LOS PAGOS DESDE EL ARCHIVO

    gTotalClientes = obtenerTotalPersonas( ); //CARGA LOS CLIENTES DESDE EL ARCHIVO
	if ( gTotalClientes > 0 )
    {
		ArbolClientes = NULL;
		ArbolClientesInactivos = NULL;
		if ( obtenerTotalLineasArchivo( tempClientesActivos ) > 0 ) 	cargarArbolClientes( &ArbolClientes, tempClientesActivos );
        if ( obtenerTotalLineasArchivo( tempClientesInactivos ) > 0 ) 	cargarArbolClientes( &ArbolClientesInactivos, tempClientesInactivos );

// NO SE PUEDE VERIFICAR LOS AMIGOS REFERIDOS SIN ANTES TENER CARGADOS LOS ÁRBOLES DE CLIENTES ACTIVOS E INACTIVOS
        if ( obtenerTotalLineasArchivo( tempClientesActivos ) > 0 ) 	verificarAmigos( &ArbolClientes );
        if ( obtenerTotalLineasArchivo( tempClientesInactivos ) > 0 ) 	verificarAmigos( &ArbolClientesInactivos );


    }

	clrscr();
    printf( "\n\n\t******************************************************" );
	printf( "\n\n\t********** SISTEMA DE GESTI%cN DE CR%cDITOS ************",acento_O ,acento_E );
    printf( "\n\n\t******************************************************" );
    printf( "\n\n\t**************** RESUMEN DEL SISTEMA *****************" );
    printf( "\n\n\t******************************************************" );
    printf( "\n\n\t\tTOTAL DE CR%cDITOS: %d", acento_E, gTotalCreditos );
    printf( "\n\t\tTOTAL DE CLIENTES: %d", gTotalClientes );

    printf( "\n\n\t\tMONTO TOTAL PRESTADO EN PESOS: $%.2f", gTotalPrestamoPesos );
    printf( "\n\t\tMONTO TOTAL DEUDAS   EN PESOS: $%.2f", gTotalDeudaPesos );

    printf( "\n\n\t\tMONTO TOTAL PRESTADO EN DOLARES: $%.2f", gTotalPrestamoDolares );
    printf( "\n\t\tMONTO TOTAL DEUDAS   EN DOLARES: $%.2f", gTotalDeudaDolares );

    printf( "\n\n\t\tMONTO TOTAL INCOBRABLE EN PESOS: $%.2f", gTotalDeudaDolaresIncobrable );
    printf( "\n\t\tMONTO TOTAL INCOBRABLE EN DOLARES: $%.2f", gTotalDeudaDolaresIncobrable );

    printf( "\n\n\t******************************************************" );

    pause();
    clrscr();
}



/**
*	MUESTRA EL MANÚ PRINCIPAL DEL PROGRAMA
*	PARA CUMPLIR CON LAS CONSIGNAS DEL TP.
*/
void mostrar_menu_principal( )
{
    SetColores( COLOR_PRINCIPAL );
	printf( "\n\n\n\t\tSISTEMA DE GESTI%cN DE CR%cDITOS",acento_O ,acento_E );
    printf( "\n\n\t\tOPCIONES DISPONIBLES. ELIJA UNO PARA COMENZAR." );
    printf( "\n\n\t\t\t1.PERSONAS" );
    printf( "\n\n\t\t\t2.CR%cDITOS", acento_E );
    if ( existenPersonasAlmacenadas() == 0 ) printf( "\n\n\t\t\t3.GENERAR 1000 CLIENTES AL AZAR" );//EL SISTEMA ESTÁ VACÍO Y PROPONE GENERAR CLIENTES DE PRUEBA

    if ( existenCreditosAlmacenados() == 0 ) printf( "\n\n\t\t\t4.GENERAR 500 CR%cDITOS AL AZAR", acento_E );

    printf( "\n\n\t\t\t5.MOSTRAR RES%cMEN", acento_U );

    printf( "\n\n\t\t\t0.SALIR\n" );
}




/** FUNCIÓN QUE GENERA 1000 CLIENTES AL AZAR */
void generar_clientes_al_azar( )
{
	int i = 0, edad = 0, ingresos = 0, referido = 0, cero_uno = 0;

	FILE *file = abrirArchivoEscritura( archivoPersonas );

	//fprintf( file, "DNI;NOMBRE;APELLIDO;EDAD;INGRESOS;CRÉDITOS;REFERIDO;ESTADO");

	for ( i = 0; i <= 999; i++)
	{
		edad = rand () % ( 0-56+1 ) + MOYORIA_DE_EDAD;
		ingresos = rand () % ( 0-17000+1 ) + 1000;
		cero_uno = rand () % ( 0-3+1 ) ;			//ENTRE 0 Y 1
		referido = rand () % ( 0-1002+1 ) + 1;		//ENTRE 0 Y 999
		fprintf( file, "%03d;NOMBRE_CLTE%d;APELLIDO_CLTE%d;%d;%d;%d;%03d;%d\n", i+1, i+1, i+1, edad, ingresos, cero_uno, referido, cero_uno );
	}

	fclose( file );
	clrscr();
	printf( "\n\t\t***********************************************************************" );
	printf( "\n\n\t\t\t\tLISTA DE CLIENTES AL AZAR GENERADA CON %cXITO", acento_E );
	printf( "\n\n\t\t***********************************************************************" );
}



/** FUNCIÓN QUE GENERA 500 CRÉDITOS AL AZAR */
void generar_creditos_al_azar( )
{
	int i = 0, dia = 0, mes = 0, anio = 0, monto = 0, moneda = 0, cuotas = 0, cero_uno = 0;

	FILE *file = abrirArchivoEscritura( archivoCreditos );

	//fprintf( file, "ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO");

	for ( i = 0; i <= 499; i++)
	{
		dia = rand () % ( 0-32+1 ) + 1;
		mes = rand () % ( 0-14+1 ) + 1;
		anio = rand () % ( 0-4+1 ) + 2017;
		monto = rand () % ( 0-10070+1 ) + 500;
		moneda = rand () % ( 0-3+1 );
		cero_uno = rand () % ( 0-3+1 ) ;			//ENTRE 0 Y 1
		cuotas = rand () % ( 0-4+1 ) + 57;
		fprintf( file, "%d;%03d;%d;%02d/%02d/%04d;%d;%d;%d;%.2f\n",i, i+1, cero_uno, dia, mes, anio, monto, moneda, cuotas, ((monto/cuotas)*INTERES_POR_CUOTA * cuotas) );
	}

	fclose( file );
	clrscr();
	printf( "\n\t\t***********************************************************************" );
	printf( "\n\n\t\t\t\tLISTA DE CR%cDITOS AL AZAR GENERADO CON %cXITO", acento_E, acento_E );
	printf( "\n\n\t\t***********************************************************************" );
}



/** DEVUELVE EL LARGO DE UN INTEGER */
int get_int_len (int value){
  int l=!value;
  while(value){ l++; value/=10; }
  return l;
}
