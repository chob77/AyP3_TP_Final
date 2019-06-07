/*
 * funciones_archivo.h
 *
 *  Created on: 27 abr. 2019
 *      Author: chob
 */

#include <stdlib.h>
#include <string.h>

void clrscr()
{
    system("@cls||clear");
}



void pause()
{
    printf("\n\n");
	system("@pause");
}



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



Lista *crearNodo()
{
	return ( Nodo *) malloc(sizeof( struct Nodo ));
}



void guardarArchivo( Lista *miLista, FILE *p )
{
	while( miLista->siguiente != NULL )
	{
		fprintf( p, "%d\n", miLista->valor );
		miLista = miLista->siguiente;
	}
}



void recorrerLista ( Lista *miLista)
{
	while( miLista->siguiente != NULL )
	{
		printf("%d", miLista->valor);
		miLista = miLista->siguiente;
	}
	printf("\n");
}


