/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: funciones_arbol_persona.c
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */




/** INSERTAR UN DATO EN EL ÁRBOL ABB */
int InsertarPersonaArbol( ArbolPersonas *arbol, int dni, Persona persona )
{
   pNodoPersonas padre = NULL;
   pNodoPersonas actual = *arbol;

   // Buscar el dni en el árbol, manteniendo un puntero al nodo padre
   while( !VacioPersonas( actual ) && dni != actual->dni ) {
      padre = actual;
      if( dni < actual->dni ) actual = actual->izquierdo;
      else if( dni > actual->dni ) actual = actual->derecho;
   }

   // Si se ha encontrado el elemento, regresar sin insertar
   if( !VacioPersonas( actual ) ) return FALSE;

   // Si padre es NULL, entonces el árbol estaba vacío, el nuevo nodo será el nodo raiz
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
  return TRUE;
}



/** EQUILIBRAR ÁRBOL AVL PARTIENDO DEL NODO NUEVO */
void EquilibrarArbolPersona( ArbolPersonas *arbol, pNodoPersonas nodo, int rama, int nuevo )
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
		 if( nodo->izquierdo->Fac_equ == 1 ) RDD_persona( arbol, nodo ); // Rotación doble
         else RSD_persona( arbol, nodo );                         // Rotación simple
         salir = TRUE;
      }

      else if( nodo->Fac_equ == 2 ) {  // Rotar a izquierda y salir:
         if( nodo->derecho->Fac_equ == -1 ) RDI_persona( arbol, nodo ); // Rotación doble
         else RSI_persona( arbol, nodo );                        // Rotación simple
         salir = TRUE;
      }

	  if( nodo->padre )
         if( nodo->padre->derecho == nodo ) rama = DERECHO; else rama = IZQUIERDO;

	  nodo = nodo->padre; //Calcular Fac_equ, siguiente nodo del camino.
   }
}



/** ROTACIÓN DOBLE A LA DERECHA */
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
void BorrarPersona( ArbolPersonas *arbol, int dni )
{
   pNodoPersonas padre = NULL;
   pNodoPersonas actual;
   pNodoPersonas nodo;
   int aux;

   actual = *arbol;
   // Mientras sea posible que el valor esté en el árbol
   while( !VacioPersonas( actual ) ) {
      if( dni == actual->dni ) { // Si el valor está en el nodo actual
         if( EsHojaPersona( actual ) ) { // Y si además es un nodo hoja: lo borramos
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
               if( padre->derecho == actual ) 	EquilibrarArbolPersona( arbol, padre, DERECHO, FALSE );
               else                         	EquilibrarArbolPersona( arbol, padre, IZQUIERDO, FALSE );
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
            aux = actual->dni;
            actual->dni = nodo->dni;
            nodo->dni = aux;
            actual = nodo;
         }
      }
      else { // Todavía no hemos encontrado el valor, seguir buscándolo
         padre = actual;
         if( dni > actual->dni ) actual = actual->derecho;
         else if( dni < actual->dni ) actual = actual->izquierdo;
      }
   }
}



/** RECORRIDO DE ÁRBOL EN INORDEN,
	APLICAMOS LA FUNCIÓN FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void InOrdenPersona( ArbolPersonas arbol, void ( *func )( int*, char* ) )
{
   if( arbol->izquierdo ) InOrdenPersona( arbol->izquierdo, func );
   func( &( arbol->dni ), arbol->persona.nombre );
   if( arbol->derecho ) InOrdenPersona( arbol->derecho, func );
}



/** RECORRE EL ÁRBOL INORDER */
void InOrdenPersonaTabulada( ArbolPersonas arbol, void ( *func )( int*, char*, char*, int*, int*, char* ) )
{
/* PERSONAS:
	DNI	(clave), NOMBRE, APELLIDO, EDAD, INGRESOS, CRÉDITOS, REFERIDOS, ESTADO
*/
   if( arbol->izquierdo ) InOrdenPersonaTabulada( arbol->izquierdo, func );
   if ( countInOrder == 32 )
   {
       printf( "\n(contin%ca.....) ", acento_u );
       pause();
       countInOrder = 0;
       clrscr();
       printf( "\n\tLISTA DE CLIENTES ALMACENADOS.\n" );
       printf( "\n   DNI\tNOMBRE\t\t\tAPELLIDO\t\tEDAD\tINGRESOS\tREFERIDO\tDEUDA $\tDEUDA U$S" );
       printf( "\n   ----------------------------------------------------------------------------------------------------------------------" );
   }

   func( &( arbol->dni ), arbol->persona.nombre, arbol->persona.apellido, &( arbol->persona.edad ), &( arbol->persona.ingresos ), arbol->persona.amigo->nombre );

   countInOrder++;

   if( arbol->derecho ) InOrdenPersonaTabulada( arbol->derecho, func );
}



/** FUNCIÓN PARA MOSTRAR LA INFO EN RECORRIDOS DEL ÁRBOL */
void MostrarPersonasTabuladas( int *dni, char *nom, char *ape, int *edad, int *ing, char *amigo )
{
	/* PERSONAS: DNI (clave), NOMBRE, APELLIDO, EDAD, INGRESOS, CRÉDITOS, REFERIDOS, ESTADO */

	double p = obtenerDeudaPesos( *dni );
	double d = obtenerDeudaDolares( *dni );

	printf( "\n   %d\t%-20s\t%-20s\t%d\t%-5d\t\t%-9s\t%-9.2f\t%-9.2f", *dni, nom, ape, *edad, *ing, amigo, p, d );
}




/** RECORRIDO DE ÁRBOL EN PREORDEN,
	APLICAMOS LA FUNCIÓN FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void PreOrdenPersona( ArbolPersonas arbol, void ( *func )( int* ) )
{
   func( &arbol->dni );
   if( arbol->izquierdo ) PreOrdenPersona( arbol->izquierdo, func );
   if( arbol->derecho ) PreOrdenPersona( arbol->derecho, func );
}



/** RECORRIDO DE ÁRBOL EN POSTORDEN,
	APLICAMOS LA FUNCIÓN FUNC, QUE TIENE EL PROTOTIPO: void func( int* );
*/
void PostOrdenPersona( ArbolPersonas arbol, void ( *func )( int* ) )
{
   if( arbol->izquierdo ) PostOrdenPersona( arbol->izquierdo, func );
   if( arbol->derecho ) PostOrdenPersona( arbol->derecho, func );
   func( &arbol->dni );
}



/** BUSCAR UN VALOR EN EL ÁRBOL DE PERSONAS*/
int BuscarPersona( ArbolPersonas arbol, int dni )
{
   pNodoPersonas actual = arbol;

   while( !VacioPersonas( actual ) )
   {
      if( dni == actual->dni ) return TRUE; // dni encontrado
      else if( dni < actual->dni ) actual = actual->izquierdo; // Seguir
      else if( dni > actual->dni ) actual = actual->derecho;
   }
   return FALSE; // No está en árbol
}



/** BUSCA EL DNI EN EL ÁRBOL ABB */
Persona *obtenerDireccionPersonaDNI( ArbolPersonas arbol, int dni )
{
   pNodoPersonas actual = arbol;
   Persona *persona = NULL;

   while( !VacioPersonas( actual ) )
   {
      if( dni == actual->dni ) return &actual->persona; // Seguir
      else if( dni > actual->dni ) actual = actual->derecho; // Seguir por la derecha
      else if( dni < actual->dni ) actual = actual->izquierdo; // Seguir por la izquierda
   }
   return persona; // No está en árbol
}



/** BUSCA EL DNI EN EL ÁRBOL ABB */
Persona obtenerPersonaDNI( ArbolPersonas arbol, int dni )
{
   pNodoPersonas actual = arbol;
   Persona persona = inicializarPersona();

   while( !VacioPersonas( actual ) )
   {
      if( dni == actual->dni ) return actual->persona; // Seguir
      else if( dni > actual->dni ) actual = actual->derecho; // Seguir por la derecha
      else if( dni < actual->dni ) actual = actual->izquierdo; // Seguir por la izquierda
   }
   return persona; // No está en árbol
}



/** COMPROBAR SI UN ÁRBOL ESTA VACÍO */
int VacioPersonas( ArbolPersonas arbol )
{
   return arbol==NULL;
}



/** COMPROBAR SI UN NODO ES HOJA */
int EsHojaPersona( pNodoPersonas nodo )
{
   return !nodo->derecho && !nodo->izquierdo;
}



/** FUNCIÓN PARA MOSTRAR LA INFO EN RECORRIDOS DEL ÁRBOL */
void MostrarPersona( int *d, char *c )
{
   printf( "%d (%s), ", *d, c );
}



/** RECORRE EL ÁRBOL INORDER PARA MOSTRAR CLIENTES EN RANGO DE EDADES */
void obtenerPersonasEnRango( ArbolPersonas arbol, int edadMenor, int edadMayor, void ( *func )( int*, char*, char*, int*, int*, int*, int* ) )
{
/* PERSONAS:
	DNI	(clave), NOMBRE, APELLIDO, EDAD, INGRESOS, CRÉDITOS, REFERIDOS, ESTADO
*/
   if( arbol->izquierdo ) obtenerPersonasEnRango( arbol->izquierdo, edadMenor, edadMayor, func );
   if ( countInOrderEdad == 32 )
   {
       printf( "\n(contin%ca.....) ", acento_u );
       pause();
       countInOrderEdad = 0;
       clrscr();
       printf( "\n\n\tLISTA DE CLIENTES ALMACENADOS EN EL RANGO DE EDADES (%d - %d).\n", edadMenor, edadMayor );
       printf( "\n\n\tDNI\tNOMBRE\t\t\tAPELLIDO\t  EDAD\tINGRESOS." );
       printf( "\n\t------------------------------------------------------------------" );
   }
   func( &( arbol->dni ), arbol->persona.nombre, arbol->persona.apellido, &( arbol->persona.edad ), &( arbol->persona.ingresos ), &( edadMenor ), &( edadMayor ));

   if( arbol->derecho ) obtenerPersonasEnRango( arbol->derecho, edadMenor, edadMayor, func );
}




/** FUNCIÓN PARA MOSTRAR LA INFO EN RECORRIDOS DEL ÁRBOL DE EDADES*/
void MostrarEdadesPersonasTabuladas( int *dni, char *nom, char *ape, int *edad, int *ing, int *edadMenor, int *edadMayor )
{
/* PERSONAS:
	DNI	(clave), NOMBRE, APELLIDO, EDAD, INGRESOS, CRÉDITOS, REFERIDOS, ESTADO
*/
   if ( *edad >= *edadMenor && *edad <= *edadMayor ) { printf( "\n\t%d\t%-20s\t%-20s %-3d\t%d", *dni, nom, ape, *edad, *ing ); countInOrderEdad++;}
}



int amigo = 0;
/** CREA LAS RELACIONES DE CLIENTES Y REFERIDOS */
void verificarAmigos ( ArbolPersonas *arbol )
{
	pNodoPersonas actual = *arbol;
	Persona persona;
	amigo = obtenerAmigo( actual->dni );													//OBTENGO DESDE LA LISTA SIMPLE EL AMIGO ASOCIADO AL CLIENTE

	//printf("\nCLIENTE ACTUAL: %d", actual->dni );

	if( actual->izquierdo ) { verificarAmigos( &actual->izquierdo ); }


	//printf("\nVERIFICANDO REFERIDO DEL CLIENTE %d AMIGO %d", actual->dni, amigo );

	if ( amigo != 0 )																			// EL CLIENTE TIENE UN AMIGO CARGADO. NO SABEMOS SI EXISTE EN EL SISTMA O NO.
	{
		if ( isIn( arrayDNIClientesActivos, amigo, LEN_ARR( arrayDNIClientesActivos )))			//VERIFICA SI EL AMIGO ESTÁ ACTIVO
		{
			actual->persona.amigo = obtenerDireccionPersonaDNI( ArbolClientes, amigo );			//OBTENGO LA PERSONA DEL AMIGO ACTIVO
		}
		else if ( isIn( arrayDNIClientesInactivos, amigo, LEN_ARR( arrayDNIClientesInactivos )))//VERIFICA SI EL AMIGO ESTÁ INACTIVO
		{
			actual->persona.amigo = obtenerDireccionPersonaDNI( ArbolClientesInactivos, amigo );//OBTENGO LA PERSONA DEL AMIGO ACTIVO
		}
		else																					//EL AMIGO NO EXISTE EN LA BASE SE CREA UNA PERSONA GENÉRICA.
		{
			//Persona persona;
			persona = inicializarPersona();
			persona.dni = obtenerAmigo( actual->dni );											//SE ASIGNA EL DNI DEL AMIGO OTORGADO POR EL CLIENTE
			if ( persona.dni != 0 )
			{
				almacenarPersonas( persona, tempClientesInactivos ); 							//SE ALMACENA EL DATO DEL REFERIDO
				hayClienteInactivoNuevo = TRUE;
			}
			actual->persona.amigo = &persona;
		}
	}
	else		//NO TIENE AMIGO SE CREA UNA PERSONA GENÉRICA para que no sea NULL.
	{
		persona = inicializarPersona();
		//persona.estado = 0;
		actual->persona.amigo = &persona;
	}

	if( actual->derecho ) { verificarAmigos( &actual->derecho );}
}


