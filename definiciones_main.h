/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: definiciones_tp_final.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */

const int acento_a = 160; //á: 160
const int acento_e = 130; //é: 130
const int acento_i = 161; //í: 161
const int acento_o = 162; //ó: 162
const int acento_u = 163; //ú: 163
const int acento_A = 181; //Á: 181
const int acento_E = 144; //É: 144
const int acento_I = 214; //Í: 214
const int acento_O = 224; //Ó: 224
const int acento_U = 23;  //Ú: 23
const int enie     = 164; //ñ: 164
const int Enie     = 165; //Ñ: 165

# define COLOR_PRINCIPAL 242
# define COLOR_PERSONAS 244
# define COLOR_CREDITOS 241

int gTotalClientes = 0;

/*
#include <windows.h>

SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), X );
printf("  X  ");

Con esta instruccion, se colorea la letra desde donde aparece el comando.
Para mas colores:

0 = NEGRO
1 = AZUL
2 = VERDE
3 = AGUAMARINA
4 = ROJO
5 = PURPURA
6 = AMARILLO
7 = BLANCO
8 = GRIS
9 = AZUL CLARO
A = VERDE CLARO
B = AGUAMARINA CLARO
C = ROJO CLARO
D = PURPURA CLARO
E = AMARILLO CLARO
F = BLANCO BRILLANTE

como calcular X?: X=A*16+B;
A=color de fondo
B=color de texto
Asi, si queremos por ejemplo un texto azul claro sobre fondo amarillo:
X=6(fondo amarillo)*16+9(texto azul claro)= 105
*/



