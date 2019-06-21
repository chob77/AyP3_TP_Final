/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: main.c
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "definiciones_main.h"
#include "definiciones_empresa.h"
#include "definiciones_personas.h"
#include "definiciones_arboles.h"
#include "definiciones_archivo.h"
#include "definiciones_creditos.h"
#include "definiciones_lista_simple.h"

#include "funciones_archivo.h"
#include "funciones_arbol_personas.h"
#include "funciones_persona.h"
#include "funciones_lista_simple.h"
#include "funciones_main.h"


/**
 *	Consigna del TP final parte 2: ejercicio integrador

 * Este ejercicio junto con la primer parte de árbol BST constituyen la evaluación final de la materia.

 * Desarrollar un sistema de créditos.
 * Debe permitir:
 * 	Dar de alta
 * 	-Listar clientes
 * 	-Buscar clientes por nombre
 * 	-Buscar clientes por rango de edad
 * 	-Cada cliente tiene una referencia que puede ser otro cliente

 * Además cada cliente puede solicitar un crédito con determinado monto.
 * 	-Dar de alta y listar créditos
 * 	-Pagar crédito
 * 	-Cancelar crédito

 * 	El sistema debe poder soportar un gran listado de clientes y créditos.
	Los datos de clientes y créditos deben ser persistentes en archivos.
	Utilizar estructuras de datos para almacenar los listados.
	Decidir cuántas unidades se guardan en memoria y si se utiliza ordenamiento de los datos.

 * 	Escribir un informe explicando la implementación de cada función y por qué se decidió hacerla de esa forma (un párrafo por cada función, no más).
	Explicar el modelo de negocio diseñado para resolver el problema (cómo se guardan los datos en los archivos, qué datos se guardan, etc.).
	Además detallar las dificultades que se enfrentaron en el desarrollo. Por qué se eligió una alternativa frente a la otra.

 * 	El diseño del sistema y los modelos es libre. Utilizar la creatividad para que el manejo del sistema sea lo más práctico posible.
	Si los requerimientos planteados son cumplidos, el ejercicio está aprobado.
	Puede pasar que en situaciones en la que la cantidad de datos sea muy grande, el sistema sea inmanejable.
	En ese caso, detallar las limitaciones de la solución propuesta (si las limitaciones son reconocidas no se considera desaprobado el punto).

	Ideas no-obligatorias de implentar pero que podrían mejorar el sistema:
		calculadora de préstamos,
		generar clientes de prueba y créditos aleatorios de forma masiva,
		utilizar paginado,
		poder elegir el cliente de un listado reducido,
		dar la posibilidad de hacer pagos parciales,
		estadísticas de los clientes y créditos, etc.
*/


int main(){
    SetColores( COLOR_PRINCIPAL );
	clrscr();
    int opcion;

	do
	{
		mostrar_menu_principal();
        opcion = OpcionElegida();

        switch ( opcion )
        {
            case 1: //OPCION 1 GESTIÓN DE CLIENTES
				opcionesMenuPersonas( );
            	break;

            case 2: //OPCION 2 GESTIÓN DE CRÉDITOS
            	opcionesMenuCreditos( );
            	break;

            case 3: //OPCION 3 GENERAR 1000 CLIENTES AL AZAR
            	generar_clientes_al_azar( );
            	break;

            case 4: //OPCION 4 GENERAR 100 CRÉDITOS AL AZAR
            	generar_creditos_al_azar( );
            	break;

            default:
                clrscr();
                printf( "\n\nFIN DEL PROGRAMA\n");
                break;
        }
    }while( opcion !=0 );
}
