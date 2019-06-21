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
    //printf( "\n\n" );
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

	//int len = sizeof( array ) / sizeof( array[0] );

    for( i=0; i<len; i++) if ( arr[i] == val ) retorno = 1;

    return retorno;
}


/** DEVUELVE LA OPCIÓN ESCOGIDA POR EL USUARIO */
int OpcionElegida()
{
    int opcion;
    printf("\nElija una Opcion: ");
    scanf("%d", &opcion);
    return opcion;
}


/**
*	MUESTRA EL MANÚ PRINCIPAL DEL PROGRAMA
*	PARA CUMPLIR CON LAS CONSIGNAS DEL TP.
*/
void mostrar_menu_principal( )
{
    SetColores( COLOR_PRINCIPAL );
	printf( "\n\n\nSISTEMA DE GESTI%cN DE CR%cDITOS",acento_O ,acento_E );
    printf( "\n\nOPCIONES DISPONIBLES. ELIJA UNO PARA COMENZAR." );
    printf( "\n\n\t1.PERSONAS" );
    printf( "\n\n\t2.CR%cDITOS", acento_E );
    if ( existenPersonasAlmacenadas() == 0 ) printf( "\n\n\t3.GENERAR 1000 CLIENTES AL AZAR" );//EL SISTEMA ESTÁ VACÍO Y PROPONE GENERAR CLIENTES DE PRUEBA

    if ( existenCreditosAlmacenados() == 0 ) printf( "\n\n\t4.GENERAR 100 CR%cDITOS AL AZAR", acento_E );

    printf( "\n\n\t0.SALIR\n" );
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
                opcionesMenuPersonas( );
                break;

            case 2: //OPCION 2 LISTAR CRÉDITOS EXISTENTES
                opcionesMenuCreditos( );
                break;

            case 3: //OPCION 3 INGRESAR PAGO PARCIAL
                mostrar_menu_creditos( );
                break;

            case 4: //OPCION 4 CANCELAR CRÉDITO
                mostrar_menu_creditos( );
                break;

            default:
                clrscr();
                break;
        }
    }while( opcion !=0 );
}




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



/** FUNCIÓN QUE GENERA 1000 CLIENTES AL AZAR */
void generar_clientes_al_azar( )
{
	int i = 0, edad = 0, ingresos = 0, referido = 0, cero_uno = 0;

	FILE *file = abrirArchivoEscritura( archivoPersonas );

	//fprintf( file, "DNI;NOMBRE;APELLIDO;EDAD;INGRESOS;CRÉDITOS;REFERIDO;ESTADO");

	for ( i = 0; i <= 999; i++)
	{
		edad = rand () % ( 0-56+1 ) + 18;
		ingresos = rand () % ( 0-170000+1 ) + 10000;
		cero_uno = rand () % ( 0-3+1 ) ;			//ENTRE 0 Y 1
		referido = rand () % ( 0-1002+1 ) + 1;			//ENTRE 0 Y 999
		fprintf( file, "%03d;NOMBRE_CLTE%d;APELLIDO_CLTE%d;%d;%d;%d;%03d;%d\n", i+1, i+1, i+1, edad, ingresos, cero_uno, referido, cero_uno );
	}

	fclose( file );
	clrscr();
	printf( "\n***********************************************************************" );
	printf( "\n\n\t\tLISTA DE CLIENTES AL AZAR GENERADA CON %cXITO", acento_E );
	printf( "\n\n***********************************************************************" );
}



/** FUNCIÓN QUE GENERA 100 CRÉDITOS AL AZAR */
void generar_creditos_al_azar( )
{
	int i = 0, dia = 0, mes = 0, anio = 0, monto = 0, moneda = 0, cuotas = 0;

	FILE *file = abrirArchivoEscritura( archivoCreditos );

	//fprintf( file, "ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO");

	for ( i = 0; i <= 99; i++)
	{
		dia = rand () % ( 0-32+1 ) + 1;
		mes = rand () % ( 0-14+1 ) + 1;
		anio = rand () % ( 0-4+1 ) + 2017;
		monto = rand () % ( 0-100000+1 ) + 5000;
		moneda = rand () % ( 0-3+1 );
		cuotas = rand () % ( 0-4+1 ) + 1;
		fprintf( file, "%d;%03d;%d;%02d/%02d/%04d;%d;%d;%d;%d\n",i, i+1, moneda, dia, mes, anio, monto, moneda, cuotas, monto );
	}

	fclose( file );
	clrscr();
	printf( "\n***********************************************************************" );
	printf( "\n\n\t\tLISTA DE CR%cDITOS AL AZAR GENERADO CON %cXITO", acento_E, acento_E );
	printf( "\n\n***********************************************************************" );
}




int get_int_len (int value){
  int l=!value;
  while(value){ l++; value/=10; }
  return l;
}
