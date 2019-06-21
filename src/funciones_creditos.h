/*
 * MATERIA: ALGORITMOS Y PROGRAMACI�N 3
 * UNTREF 2019.
 *
 * TRABAJO PR�CTICO FINAL INTEGRADOR: SISTEMA DE CR�DITOS.
 * FILE: funciones_creditos.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */



/**
*	MUESTRA EL MAN� PARA MANEJAR LAS UTILIDADES CON LAS PERSONAS
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




/** ADMINISTRA LA GESTI�N DE CR�DITOS */
void opcionesMenuCreditos()
{
    int opcion;
    do
    {
        mostrar_menu_creditos( );
        opcion = OpcionElegida();

        switch ( opcion )
        {
            case 1: //OPCION 1 CREAR CR�DITO
                opcionesMenuPersonas( );
                break;

            case 2: //OPCION 2 LISTAR CR�DITOS EXISTENTES
                opcionesMenuCreditos( );
                break;

            case 3: //OPCION 3 INGRESAR PAGO PARCIAL
                mostrar_menu_creditos( );
                break;

            case 4: //OPCION 4 CANCELAR CR�DITO
                mostrar_menu_creditos( );
                break;

            default:
                clrscr();
                break;
        }
    }while( opcion !=0 );
}




