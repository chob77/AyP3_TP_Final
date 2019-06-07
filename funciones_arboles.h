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


/**
*	MUESTRA EL MANÚ PRINCIPAL DEL PROGRAMA
*	PARA CUMPLIR CON LAS CONSIGNAS DEL TP.
*/
void mostrar_menu_arboles( )
{
    printf( "\nELIJA UNA OPCION" );
    printf( "\n\t1.INSERTAR UN ELEMENTO AL %cRBOL", acento_A );
    printf( "\n\t2.ELMINAR UN ELEMENTO DEL %cRBOL", acento_A );
	printf( "\n\t3.RECORRER EL %cRBOL PRE-ORDER", acento_A );
	printf( "\n\t4.RECORRER EL %cRBOL IN-ORDER", acento_A );
	printf( "\n\t5.RECORRER EL %cRBOL POST-ORDER", acento_A );
	printf( "\n\t6.BUSCAR UN ELEMENTO" );
    printf( "\n\t0.SALIR" );
}



/** DETERMINA SI UN STRING ES NUMÉRICO */
int isNumero( char * st )
{
	int len = strlen( st );//obtiene el largo del string

    for ( int i = 0; i < len; i++ ) {
        if ( (( int ) st[i])< 48 || (( int ) st[i]) > 57 ) {//verifica si alguno de los caracteres del string no es un número de la tabla ASCII
            return FALSE;
        }
    }
    return TRUE;
}



/** CARGA REPETITIVAMENTE UN VALOR NUMÉRICO EN EL ÁRBOL. */
void cargarArbol( Arbol *arbol )
{
	char nro_entero[ 10 ];
	int i=0;
	int opcion=0;

	clrscr( );

	printf( "\nINGRESAR ELEMENTOS AL %cRBOL", acento_A );
	printf( "\n---------------------------------------" );

	do {
		printf( "\nIngrese un n%cmero entero ( %02d ingresados ): ", acento_u, i );
		scanf( "%s", nro_entero );

	    if ( isNumero( nro_entero ) )
		{
			opcion = 1;
			Insertar( arbol, atoi( nro_entero ) );
			i++;
		}
		else opcion = 0;

    } while( opcion == 1 );

	clrscr( );
	printf( "\nFINALIZO LA CARGA DEL %cRBOL. SE CARGARON %d ELEMENTO/S\n", acento_A, i );
}




/** ELIMINA UN ELEMENTO DEL ÁRBOL */
void eliminarElemento( Arbol *arbol )
{
	int dato;
	clrscr();
	printf("\nELIMINAR UN ELEMENTO DEL %cRBOL: ", acento_A );
	printf( "\n---------------------------------------" );
	printf("\nELEMENTOS DEL %cRBOL: ", acento_A );
	InOrden( *arbol, Mostrar );
	printf("\n\nINGRESA EL ELEMENTO A ELIMINAR DEL %cRBOL: ", acento_A );
	scanf( "%d", &dato );

	printf("\nSE VA A ELIMINAR EL ELEMENTO %d: \n", dato );
	Borrar( arbol, dato );

	printf("\n%cRBOL RESULTANTE: ", acento_A );
	InOrden( *arbol, Mostrar );
	printf("\n\n" );
}




/** INSERTAR UN DATO EN EL ÁRBOL ABB */
void Insertar( Arbol *arbol, int dato )
{
   pNodo padre = NULL;
   pNodo actual = *arbol;

   // Buscar el dato en el árbol, manteniendo un puntero al nodo padre
   while( !Vacio( actual ) && dato != actual->dato ) {
      padre = actual;
      if( dato < actual->dato ) actual = actual->izquierdo;
      else if( dato > actual->dato ) actual = actual->derecho;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if( !Vacio( actual ) ) return;

   // Si padre es NULL, entonces el árbol estaba vacío, el nuevo nodo será el nodo raiz
   if( Vacio( padre ) ) {
      *arbol = ( Arbol )malloc( sizeof( tipoNodo ) );
      ( *arbol )->dato = dato;
      ( *arbol )->izquierdo = ( *arbol )->derecho = NULL;
      ( *arbol )->padre = NULL;
      ( *arbol )->Fac_equ = 0;
   }

   // Si el dato es menor que el que contiene el nodo padre, lo insertamos en la rama izquierda
   else if( dato < padre->dato ) {
      actual = ( Arbol )malloc( sizeof( tipoNodo ) );
      padre->izquierdo = actual;
      actual->dato = dato;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->Fac_equ = 0;
      Equilibrar( arbol, padre, IZQUIERDO, TRUE );
   }

   // Si el dato es mayor que el que contiene el nodo padre, lo insertamos en la rama derecha
   else if( dato > padre->dato ) {
      actual = ( Arbol )malloc( sizeof( tipoNodo ) );
      padre->derecho = actual;
      actual->dato = dato;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->Fac_equ = 0;
      Equilibrar( arbol, padre, DERECHO, TRUE );
  }
}




/** EQUILIBRAR ÁRBOL AVL PARTIENDO DEL NODO NUEVO */
void Equilibrar( Arbol *arbol, pNodo nodo, int rama, int nuevo )
{
   int salir = FALSE;

   // Recorrer camino inverso actualizando valores de Fac_equ:
   while( nodo && !salir ) {

	  if( nuevo )
         if( rama == IZQUIERDO ) nodo->Fac_equ--; // Depende de si añadimos ...
         else                    nodo->Fac_equ++;

	  else
         if( rama == IZQUIERDO ) nodo->Fac_equ++; // ... o borramos
         else                    nodo->Fac_equ--;

	  if( nodo->Fac_equ == 0 ) salir = TRUE; // La altura de las rama que empieza en nodo no ha variado, salir de Equilibrar

      else if( nodo->Fac_equ == -2 ) { // Rotar a derecha y salir:
		 if( nodo->izquierdo->Fac_equ == 1 ) RDD( arbol, nodo ); // Rotación doble
         else RSD( arbol, nodo );                         // Rotación simple
         salir = TRUE;
      }

      else if( nodo->Fac_equ == 2 ) {  // Rotar a izquierda y salir:
         if( nodo->derecho->Fac_equ == -1 ) RDI( arbol, nodo ); // Rotación doble
         else RSI( arbol, nodo );                        // Rotación simple
         salir = TRUE;
      }

	  if( nodo->padre )
         if( nodo->padre->derecho == nodo ) rama = DERECHO; else rama = IZQUIERDO;

	  nodo = nodo->padre; //Calcular Fac_equ, siguiente nodo del camino.
   }
}



/** ROTACIÓN DOBLE A LA DERECHA */
void RDD( Arbol *raiz, Arbol nodo )
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->izquierdo;
   pNodo R = Q->derecho;
   pNodo B = R->izquierdo;
   pNodo C = R->derecho;

   if( Padre )
     if( Padre->derecho == nodo ) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *raiz = R;

   // Reconstruir árbol:
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;

   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if( B ) B->padre = Q;
   if( C ) C->padre = P;

   // Ajustar valores de Fac_equ:
   switch( R->Fac_equ ) {
      case -1: Q->Fac_equ = 0; P->Fac_equ = 1; break;
      case 0:  Q->Fac_equ = 0; P->Fac_equ = 0; break;
      case 1:  Q->Fac_equ = -1; P->Fac_equ = 0; break;
   }
   R->Fac_equ = 0;
}



/** ROTACIÓN DOBLE A LA IZQUIERDA */
void RDI( Arbol *arbol, pNodo nodo )
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->derecho;
   pNodo R = Q->izquierdo;
   pNodo B = R->izquierdo;
   pNodo C = R->derecho;

   if( Padre )
     if( Padre->derecho == nodo ) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *arbol = R;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;

   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if( B ) B->padre = P;
   if( C ) C->padre = Q;

   // Ajustar valores de Fac_equ:
   switch( R->Fac_equ ) {
      case -1: P->Fac_equ = 0; Q->Fac_equ = 1; break;
      case 0:  P->Fac_equ = 0; Q->Fac_equ = 0; break;
      case 1:  P->Fac_equ = -1; Q->Fac_equ = 0; break;
   }
   R->Fac_equ = 0;
}



/** ROTACIÓN SIMPLE A LA DERECHA */
void RSD( Arbol *arbol, pNodo nodo )
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->izquierdo;
   pNodo B = Q->derecho;

   if( Padre )
     if( Padre->derecho == P ) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *arbol = Q;

   // Reconstruir árbol:
   P->izquierdo = B;
   Q->derecho = P;

   // Reasignar padres:
   P->padre = Q;
   if( B ) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de Fac_equ:
   P->Fac_equ = 0;
   Q->Fac_equ = 0;
}



/** ROTACIÓN SIMPLE A LA IZQUIERDA */
void RSI( Arbol *arbol, pNodo nodo )
{
   pNodo Padre = nodo->padre;
   pNodo P = nodo;
   pNodo Q = P->derecho;
   pNodo B = Q->izquierdo;

   if( Padre )
     if( Padre->derecho == P ) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *arbol = Q;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = P;

   // Reasignar padres:
   P->padre = Q;
   if( B ) B->padre = P;
   Q->padre = Padre;

   // Ajustar valores de Fac_equ:
   P->Fac_equ = 0;
   Q->Fac_equ = 0;
}



/** ELIMINAR UN ELEMENTO DE UN ÁRBOL ABB */
void Borrar( Arbol *arbol, int dato )
{
   pNodo padre = NULL;
   pNodo actual;
   pNodo nodo;
   int aux;

   actual = *arbol;
   // Mientras sea posible que el valor esté en el árbol
   while( !Vacio( actual ) ) {
      if( dato == actual->dato ) { // Si el valor está en el nodo actual
         if( EsHoja( actual ) ) { // Y si además es un nodo hoja: lo borramos
            if( padre ) // Si tiene padre ( no es el nodo raiz )
               // Anulamos el puntero que le hace referencia
               if( padre->derecho == actual ) padre->derecho = NULL;
               else if( padre->izquierdo == actual ) padre->izquierdo = NULL;
            free( actual ); // Borrar el nodo
            actual = NULL;
            /* El nodo padre del actual puede ser ahora un nodo hoja, por lo tanto su Fac_equ es cero, pero debemos seguir el camino a partir de
               su padre, si existe. */
            if( ( padre->derecho == actual && padre->Fac_equ == 1 ) ||
               ( padre->izquierdo == actual && padre->Fac_equ == -1 ) )
            {
               padre->Fac_equ = 0;
               actual = padre;
               padre = actual->padre;
            }
            if( padre )
               if( padre->derecho == actual ) 	Equilibrar( arbol, padre, DERECHO, FALSE );
               else                         	Equilibrar( arbol, padre, IZQUIERDO, FALSE );
            return;
         }
         else { // Si el valor está en el nodo actual, pero no es hoja
            padre = actual;
            // Buscar nodo más izquierdo de rama derecha
            if( actual->derecho ) {
               nodo = actual->derecho;
               while( nodo->izquierdo ) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo más derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while( nodo->derecho ) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            /* Intercambiar valores de no a borrar u nodo encontrado y continuar, cerrando el bucle. El nodo encontrado no tiene
               por qué ser un nodo hoja, cerrando el bucle nos aseguramos de que sólo se eliminan nodos hoja. */
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if( dato > actual->dato ) actual = actual->derecho;
         else if( dato < actual->dato ) actual = actual->izquierdo;
      }
   }
}



/** RECORRIDO DE ÁRBOL EN INORDEN,
	APLICAMOS LA FUNCIÓN FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void InOrden( Arbol arbol, void ( *func )( int* ) )
{
   if( arbol->izquierdo ) InOrden( arbol->izquierdo, func );
   func( &( arbol->dato ) );
   if( arbol->derecho ) InOrden( arbol->derecho, func );
}



/** RECORRIDO DE ÁRBOL EN PREORDEN,
	APLICAMOS LA FUNCIÓN FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void PreOrden( Arbol arbol, void ( *func )( int* ) )
{
   func( &arbol->dato );
   if( arbol->izquierdo ) PreOrden( arbol->izquierdo, func );
   if( arbol->derecho ) PreOrden( arbol->derecho, func );
}



/** RECORRIDO DE ÁRBOL EN POSTORDEN,
	APLICAMOS LA FUNCIÓN FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void PostOrden( Arbol arbol, void ( *func )( int* ) )
{
   if( arbol->izquierdo ) PostOrden( arbol->izquierdo, func );
   if( arbol->derecho ) PostOrden( arbol->derecho, func );
   func( &arbol->dato );
}



/** BUSCAR UN VALOR EN EL ÁRBOL */
int Buscar( Arbol arbol, int dato )
{
   pNodo actual = arbol;

   // Todavía puede aparecer, ya que quedan nodos por mirar
   while( !Vacio( actual ) ) {
      if( dato == actual->dato ) return TRUE; // dato encontrado
      else if( dato < actual->dato ) actual = actual->izquierdo; // Seguir
      else if( dato > actual->dato ) actual = actual->derecho;
   }
   return FALSE; // No está en árbol
}



/** COMPROBAR SI UN ÁRBOL ES VACÍO */
int Vacio( Arbol nodo )
{
   return nodo==NULL;
}



/** COMPROBAR SI UN NODO ES HOJA */
int EsHoja( pNodo nodo )
{
   return !nodo->derecho && !nodo->izquierdo;
}



/** FUNCIÓN PARA RECORRIDOS DEL ÁRBOL */
void Mostrar( int *d )
{
   printf( "%d, ", *d );
}
