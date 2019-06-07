/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019. 
 *
 * TRABAJO PRÁCTICO: ÁRBOLES BINARIOS DE BÚSQUEDA.
 * FILE: funcioines_arboles.c
 *
 *  CREATED ON: 26 may. 2019
 *      AUTHOR: chob
 */

#include <stdlib.h>
#include <string.h>

/** LIMPA TODA LA PANTALLA DE LA CONSOLA*/
void clrscr( )
{
    system( "@cls||clear" );
}


/** GENERA UNA PAUSA EN LA EJECUCIÓN DEL PROGRAMA*/
void pause( )
{
    printf( "\n\n" );
	system( "@pause" );
}

/**
*	MUESTRA EL MANÚ PRINCIPAL DEL PROGRAMA
*	PARA CUMPLIR CON LAS CONSIGNAS DEL TP.
*/
void mostrar_menu_principal( )
{
    printf( "\n\nSISTEMA DE GESTI%cN DE CR%cDITOS",acento_O ,acento_E );
    printf( "\n\nOPCIONES DISPONIBLES" );
    printf( "\n\t1.PERSONAS" );
    printf( "\n\t2.CR%cDITOS", acento_E );
    printf( "\n\t0.SALIR" );
}


/**
*	MUESTRA EL MANÚ PARA MANEJAR LAS UTILIDADES CON LAS PERSONAS
*/
void mostrar_menu_personas( )
{
    clrscr();
	printf( "\n\nSISTEMA DE GESTI%cN DE CR%cDITOS.",acento_O ,acento_E );
    printf( "\n\nOPCIONES DISPONIBLES PARA EL LA GESTI%cN DE CLIENTES:", acento_O );
    printf( "\n\t1.INGRESAR CLIENTE." );
    printf( "\n\t2.LISTAR CLIENTES EXISTENTES" );
	printf( "\n\t3.BUSCAR CLIENTE POR NOMBRE" );
	printf( "\n\t4.BUSCAR CLIENTE POR RANGO DE EDAD" );
    printf( "\n\t0.SALIR" );
}


/**
*	MUESTRA EL MANÚ PARA MANEJAR LAS UTILIDADES CON LAS PERSONAS
*/
void mostrar_menu_creditos( )
{
    clrscr();
	printf( "\n\nSISTEMA DE GESTI%cN DE CR%cDITOS",acento_O ,acento_E );
    printf( "\n\nOPCIONES DISPONIBLES PARA LA GESTI%cN DE CR%cDITOS:", acento_O, acento_E );
    printf( "\n\t1.CREAR CR%cDITO", acento_E );
    printf( "\n\t2.LISTAR CR%cDITOS EXISTENTES", acento_E );
	printf( "\n\t3.INGRESAR PAGO PARCIAL." );
	printf( "\n\t4.CANCELAR CR%cDITO", acento_E );
    printf( "\n\t0.SALIR" );
}