/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: funciones_archivo.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


FILE *abrirArchivoLectura( const char *filename )
{
	FILE *f = fopen( filename, "r" );
	return f;
}


FILE *abrirArchivoEscritura( const char *filename )
{
	FILE *f = fopen( filename, "w" );
	return f;
}


FILE *abrirArchivoEscrituraContinua( const char *filename )
{
	FILE *f = fopen( filename, "a" );
	return f;
}


void leerArchivo( FILE *f )
{
	char c;
	while( c != EOF )
	{
		c = fgetc( f );
		printf( "%c", c );
	}
	fclose( f );
}


/** OBTIENE EL TOTAL DE LÍNEAS DE UN ARCHIVO DE TEXTO*/
int obtenerTotalLineasArchivo( const char *filename )
{
	FILE *f = abrirArchivoLectura( filename );
    int nl = 0;
	if ( f != NULL )
	{
        char c;

        while( (c = fgetc( f )) != EOF )
        {
            if( c == '\n' ) nl++;
        }
        fclose( f );
    }
	else
	{
		printf( "\t\n\nEL ARCHIVO NO SE PUDO ABRIR.\n");
	}
	return nl;
}


void guardarArchivo( Lista *miLista, FILE *f )
{
	while( miLista->siguiente != NULL )
	{
		fprintf( f, "%d\n", miLista->cliente );
		miLista = miLista->siguiente;
	}
	fclose( f );
}


/** ALMACENA LOS CLIENTES ACTIVOS EN UN ARCHIVO DE ACCESO RÁPIDO */
void cargarArchivoTemporalClientes( char *linea, const char *filename )
{
    FILE *f = abrirArchivoEscrituraContinua( filename );//AGREGAR CADA LINEA
    fprintf( f, "%s\n", linea );
    fclose( f );
}


/** ACTUALIZA LA LÍNEA EN LA QUE ESTÁ ALMACENADO UN CLIENTE */
void actualizarLineaArchivo( const char *filename, int nlinea, Persona *persona, int dniAmigo )
{

	char linea[ 1024 ];
	int i = 0;

	//printf( "\nPERSONA RECIBIDA PARA ALMACENAR: %d, %s, %s, %d, %d (%d)\n", persona->dni, persona->nombre, persona->apellido, persona->estado, dniAmigo, nlinea );

	strcpy( linea, filename );
	strcat( linea, ".tmp"); //CREA UN TEMPORAL

	if ( persona->amigo ) dniAmigo = persona->amigo->dni;

	FILE *f = abrirArchivoLectura( filename );//LEER CADA LINEA
	FILE *fileOut = abrirArchivoEscritura( linea );//CREA UN TEMPORAL

    while( fgets( linea, 1024, f ) )
    {
        if ( i != nlinea ) fprintf( fileOut, "%s", linea );

        /* PERSONAS: DNI (clave), NOMBRE, APELLIDO, EDAD, INGRESOS, CRÉDITOS, REFERIDOS, ESTADO */
		else fprintf( fileOut, "%03d;%s;%s;%d;%d;%d;%03d;%d\n", persona->dni, persona->nombre, persona->apellido, persona->edad, persona->ingresos, 0, dniAmigo, persona->estado );

        i++;
    }

    fclose( f );
    fclose( fileOut );


    remove( filename );
    strcpy( linea, "@move ");
    strcat( linea, filename );
    strcat( linea, ".tmp " );
    strcat( linea, filename );
    strcat( linea, ">nul" );
    system( linea );			//CONVIERTE EL TEMPORAL EN PRINCIPAL

    printf( "\nEDICI%cN FINALIZADA CON %cXITO.", acento_O, acento_E );
    pause();
    clrscr();
}



/**  */
void actualizarLineaArchivoCreditos( Credito *credito )
{
	int nlinea = credito->idCredito;
	char linea[ 1024 ];
	int i = 0;

	strcpy( linea, archivoCreditos );
	strcat( linea, ".tmp"); //CREA UN TEMPORAL

	FILE *f = abrirArchivoLectura( archivoCreditos );//LEER CADA LINEA
	FILE *fileOut = abrirArchivoEscritura( linea );//CREA UN TEMPORAL

    while( fgets( linea, 1024, f ) )
    {
        if ( i != nlinea ) fprintf( fileOut, "%s", linea );

		else fprintf( fileOut, "%d;%d;%d;%s;%.2f;%d;%d;%.2f\n", credito->idCredito, credito->dniCliente, credito->estado, credito->fechalta, credito->monto, credito->moneda, credito->cuotas, credito->saldo);

        i++;
    }

    fclose( f );
    fclose( fileOut );

    remove( archivoCreditos );
    strcpy( linea, "@move ");
    strcat( linea, archivoCreditos );
    strcat( linea, ".tmp " );
    strcat( linea, archivoCreditos );
    strcat( linea, ">nul" );
    system( linea );			//CONVIERTE EL TEMPORAL EN PRINCIPAL

    printf( "\nEDICI%cN FINALIZADA CON %cXITO.", acento_O, acento_E );
    //pause();
    //clrscr();
}



/** BORRA UNA LÍNEA DEL ARCHIVO DADO */
void borrarLinea( int nlinea, const char *filename )
{
	char linea[ 1024 ];
	int i = 0;
	strcpy( linea, filename );
	strcat( linea, ".tmp");

	//printf("\se debe borrar la linea %d del archivo %s", nlinea, filename);

	FILE *f = abrirArchivoLectura( filename );//LEER CADA LINEA
	FILE *ff = abrirArchivoEscritura( linea );//CREA UN TEMPORAL

    while( fgets( linea, 1024, f ) )
    {
        if ( i != nlinea ) fprintf( ff, "%s", linea );
        i++;
    }

    fclose( f );
    fclose( ff );

    remove( filename );
    strcpy( linea, "@move ");
    strcat( linea, filename );
    strcat( linea, ".tmp " );
    strcat( linea, filename );
    strcat( linea, ">nul" );
    system( linea );			//CREA UNA COPIA TEMPORAL DEL ARCHIVO A EDITAR

    printf( "\nEDICI%cN FINALIZADA CON %cXITO.", acento_O, acento_E );
    pause();
    clrscr();
}



/** VERIFICA LA EXISTENCIA DEL ARCHIVO DE PAGOS */
int existenPagosAlmacenados()
{
	int retorno = FALSE;
	FILE *f = abrirArchivoLectura( archivoPagos );
	if  ( f ) retorno = TRUE;
	fclose( f );
	return retorno;
}



/** VERIFICA LA EXISTENCIA DEL ARCHIVO DE CRÉDITOS */
int existenCreditosAlmacenados()
{
	int retorno = FALSE;
	FILE *f = abrirArchivoLectura( archivoCreditos );
	if  ( f ) retorno = TRUE;
	fclose( f );
	return retorno;
}


/** VERIFICA LA EXISTENCIA DEL ARCHIVO DE CLIENTES */
int existenPersonasAlmacenadas()
{
	int retorno = FALSE;
	FILE *file = abrirArchivoLectura( archivoPersonas );
	if  ( file ) retorno = TRUE;
	fclose( file );
	return retorno;
}



