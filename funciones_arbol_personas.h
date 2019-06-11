/*
 * MATERIA: ALGORITMOS Y PROGRAMACI�N 3
 * UNTREF 2019.
 *
 * TRABAJO PR�CTICO FINAL INTEGRADOR: SISTEMA DE CR�DITOS.
 * FILE: funciones_arbol_persona.c
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */



/** ELIMINA UN ELEMENTO DEL �RBOL */
void eliminarElementoPersona( ArbolPersonas *arbol )
{
	int dni;
	clrscr();
	printf("\nELIMINAR UN ELEMENTO DEL %cRBOL: ", acento_A );
	printf( "\n---------------------------------------" );
	printf("\nELEMENTOS DEL %cRBOL: ", acento_A );
	InOrden( *arbol, Mostrar );
	printf("\n\nINGRESA EL ELEMENTO A ELIMINAR DEL %cRBOL: ", acento_A );
	scanf( "%d", &dni );

	printf("\nSE VA A ELIMINAR EL ELEMENTO %d: \n", dni );
	Borrar( arbol, dni );

	printf("\n%cRBOL RESULTANTE: ", acento_A );
	InOrden( *arbol, Mostrar );
	printf("\n\n" );
}



/** INSERTAR UN DATO EN EL �RBOL ABB */
int InsertarPersonaArbol( ArbolPersonas *arbol, int dni, Persona persona )
{
   pNodoPersonas padre = NULL;
   pNodoPersonas actual = *arbol;

   // Buscar el dni en el �rbol, manteniendo un puntero al nodo padre
   while( !VacioPersonas( actual ) && dni != actual->dni ) {
      padre = actual;
      if( dni < actual->dni ) actual = actual->izquierdo;
      else if( dni > actual->dni ) actual = actual->derecho;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if( !VacioPersonas( actual ) ) return 1;

   // Si padre es NULL, entonces el �rbol estaba vac�o, el nuevo nodo ser� el nodo raiz
   if( VacioPersonas( padre ) ) {
      *arbol = malloc( sizeof( nodoArbolPersona ) );
      ( *arbol )->dni = dni;
      ( *arbol )->izquierdo = ( *arbol )->derecho = NULL;
      ( *arbol )->padre = NULL;
      ( *arbol )->Fac_equ = 0;
      ( *arbol )->persona = persona;
   }

   // Si el dni es menor que el que contiene el nodo padre, lo insertamos en la rama izquierda
   else if( dni < padre->dni ) {
      actual = ( ArbolPersonas )malloc( sizeof( nodoArbolPersona ) );
      padre->izquierdo = actual;
      actual->dni = dni;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->Fac_equ = 0;
      actual->persona = persona;
      EquilibrarArbolPersona( arbol, padre, IZQUIERDO, TRUE );
   }

   // Si el dni es mayor que el que contiene el nodo padre, lo insertamos en la rama derecha
   else if( dni > padre->dni ) {
      actual = ( ArbolPersonas )malloc( sizeof( nodoArbolPersona ) );
      padre->derecho = actual;
      actual->dni = dni;
      actual->izquierdo = actual->derecho = NULL;
      actual->padre = padre;
      actual->Fac_equ = 0;
      actual->persona = persona;
      EquilibrarArbolPersona( arbol, padre, DERECHO, TRUE );
  }
  return 0;
}



/** EQUILIBRAR �RBOL AVL PARTIENDO DEL NODO NUEVO */
void EquilibrarArbolPersona( ArbolPersonas *arbol, pNodoPersonas nodo, int rama, int nuevo )
{
   int salir = FALSE;

   // Recorrer camino inverso actualizando valores de Fac_equ:
   while( nodo && !salir ) {

	  if( nuevo )
         if( rama == IZQUIERDO ) nodo->Fac_equ--; // Depende de si a�adimos ...
         else                    nodo->Fac_equ++;

	  else
         if( rama == IZQUIERDO ) nodo->Fac_equ++; // ... o borramos
         else                    nodo->Fac_equ--;

	  if( nodo->Fac_equ == 0 ) salir = TRUE; // La altura de las rama que empieza en nodo no ha variado, salir de Equilibrar

      else if( nodo->Fac_equ == -2 ) { // Rotar a derecha y salir:
		 if( nodo->izquierdo->Fac_equ == 1 ) RDD_persona( arbol, nodo ); // Rotaci�n doble
         else RSD_persona( arbol, nodo );                         // Rotaci�n simple
         salir = TRUE;
      }

      else if( nodo->Fac_equ == 2 ) {  // Rotar a izquierda y salir:
         if( nodo->derecho->Fac_equ == -1 ) RDI_persona( arbol, nodo ); // Rotaci�n doble
         else RSI_persona( arbol, nodo );                        // Rotaci�n simple
         salir = TRUE;
      }

	  if( nodo->padre )
         if( nodo->padre->derecho == nodo ) rama = DERECHO; else rama = IZQUIERDO;

	  nodo = nodo->padre; //Calcular Fac_equ, siguiente nodo del camino.
   }
}



/** ROTACI�N DOBLE A LA DERECHA */
void RDD_persona( ArbolPersonas *raiz, ArbolPersonas nodo )
{
   pNodoPersonas Padre = nodo->padre;
   pNodoPersonas P = nodo;
   pNodoPersonas Q = P->izquierdo;
   pNodoPersonas R = Q->derecho;
   pNodoPersonas B = R->izquierdo;
   pNodoPersonas C = R->derecho;

   if( Padre )
     if( Padre->derecho == nodo ) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *raiz = R;

   // Reconstruir �rbol:
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



/** ROTACI�N DOBLE A LA IZQUIERDA */
void RDI_persona( ArbolPersonas *arbol, pNodoPersonas nodo )
{
   pNodoPersonas Padre = nodo->padre;
   pNodoPersonas P = nodo;
   pNodoPersonas Q = P->derecho;
   pNodoPersonas R = Q->izquierdo;
   pNodoPersonas B = R->izquierdo;
   pNodoPersonas C = R->derecho;

   if( Padre )
     if( Padre->derecho == nodo ) Padre->derecho = R;
     else Padre->izquierdo = R;
   else *arbol = R;

   // Reconstruir �rbol:
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



/** ROTACI�N SIMPLE A LA DERECHA */
void RSD_persona( ArbolPersonas *arbol, pNodoPersonas nodo )
{
   pNodoPersonas Padre = nodo->padre;
   pNodoPersonas P = nodo;
   pNodoPersonas Q = P->izquierdo;
   pNodoPersonas B = Q->derecho;

   if( Padre )
     if( Padre->derecho == P ) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *arbol = Q;

   // Reconstruir �rbol:
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



/** ROTACI�N SIMPLE A LA IZQUIERDA */
void RSI_persona( ArbolPersonas *arbol, pNodoPersonas nodo )
{
   pNodoPersonas Padre = nodo->padre;
   pNodoPersonas P = nodo;
   pNodoPersonas Q = P->derecho;
   pNodoPersonas B = Q->izquierdo;

   if( Padre )
     if( Padre->derecho == P ) Padre->derecho = Q;
     else Padre->izquierdo = Q;
   else *arbol = Q;

   // Reconstruir �rbol:
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



/** ELIMINAR UN ELEMENTO DE UN �RBOL ABB */
void BorrarPersona( ArbolPersonas *arbol, int dni )
{
   pNodoPersonas padre = NULL;
   pNodoPersonas actual;
   pNodoPersonas nodo;
   int aux;

   actual = *arbol;
   // Mientras sea posible que el valor est� en el �rbol
   while( !Vacio( actual ) ) {
      if( dni == actual->dni ) { // Si el valor est� en el nodo actual
         if( EsHojaPersona( actual ) ) { // Y si adem�s es un nodo hoja: lo borramos
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
         else { // Si el valor est� en el nodo actual, pero no es hoja
            padre = actual;
            // Buscar nodo m�s izquierdo de rama derecha
            if( actual->derecho ) {
               nodo = actual->derecho;
               while( nodo->izquierdo ) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            // O buscar nodo m�s derecho de rama izquierda
            else {
               nodo = actual->izquierdo;
               while( nodo->derecho ) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            /* Intercambiar valores de no a borrar u nodo encontrado y continuar, cerrando el bucle. El nodo encontrado no tiene
               por qu� ser un nodo hoja, cerrando el bucle nos aseguramos de que s�lo se eliminan nodos hoja. */
            aux = actual->dni;
            actual->dni = nodo->dni;
            nodo->dni = aux;
            actual = nodo;
         }
      }
      else { // Todav�a no hemos encontrado el valor, seguir busc�ndolo
         padre = actual;
         if( dni > actual->dni ) actual = actual->derecho;
         else if( dni < actual->dni ) actual = actual->izquierdo;
      }
   }
}



/** RECORRIDO DE �RBOL EN INORDEN,
	APLICAMOS LA FUNCI�N FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void InOrdenPersona( ArbolPersonas arbol, void ( *func )( int*, char* ) )
{
   if( arbol->izquierdo ) InOrdenPersona( arbol->izquierdo, func );
   func( &( arbol->dni ), arbol->persona.nombre );
   if( arbol->derecho ) InOrdenPersona( arbol->derecho, func );
}



/** RECORRIDO DE �RBOL EN PREORDEN,
	APLICAMOS LA FUNCI�N FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void PreOrdenPersona( ArbolPersonas arbol, void ( *func )( int* ) )
{
   func( &arbol->dni );
   if( arbol->izquierdo ) PreOrden( arbol->izquierdo, func );
   if( arbol->derecho ) PreOrden( arbol->derecho, func );
}



/** RECORRIDO DE �RBOL EN POSTORDEN,
	APLICAMOS LA FUNCI�N FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void PostOrdenPersona( ArbolPersonas arbol, void ( *func )( int* ) )
{
   if( arbol->izquierdo ) PostOrden( arbol->izquierdo, func );
   if( arbol->derecho ) PostOrden( arbol->derecho, func );
   func( &arbol->dni );
}



/** BUSCAR UN VALOR EN EL �RBOL */
int BuscarPersona( ArbolPersonas arbol, int dni )
{
   pNodoPersonas actual = arbol;

   // Todav�a puede aparecer, ya que quedan nodos por mirar
   while( !Vacio( actual ) ) {
      if( dni == actual->dni ) return TRUE; // dni encontrado
      else if( dni < actual->dni ) actual = actual->izquierdo; // Seguir
      else if( dni > actual->dni ) actual = actual->derecho;
   }
   return FALSE; // No est� en �rbol
}



/** COMPROBAR SI UN �RBOL ESTA VAC�O */
int VacioPersonas( ArbolPersonas arbol )
{
   return arbol==NULL;
}



/** COMPROBAR SI UN NODO ES HOJA */
int EsHojaPersona( pNodoPersonas nodo )
{
   return !nodo->derecho && !nodo->izquierdo;
}



/** FUNCI�N PARA RECORRIDOS DEL �RBOL */
void MostrarPersona( int *d, char *c )
{
   printf( "%d (%s), ", *d, c );
}
