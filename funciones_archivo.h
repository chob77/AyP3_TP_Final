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
	FILE *file = fopen( filename, "r" );
	return file;
}



FILE *abrirArchivoEscritura( const char *filename )
{
	FILE *file = fopen( filename, "w" );
	return file;
}


void leerArchivo( FILE *file )
{
	char c;
	while( c != EOF )
	{
		c = fgetc( file );
		printf( "%c", c );
	}
}


/** OBTIENE EL TOTAL DE LÍNEAS DE UN ARCHIVO DE TEXTO*/
int obtenerTotalLineasArchivo( FILE *file )
{
	char c;
	int nl = 0;

	while( (c = fgetc( file )) != EOF )
	{
		if( c == '\n' ) nl++;
	}
	fclose( file );
	return nl;
}



void guardarArchivo( Lista *miLista, FILE *p )
{
	while( miLista->siguiente != NULL )
	{
		fprintf( p, "%d\n", miLista->valor );
		miLista = miLista->siguiente;
	}
}

