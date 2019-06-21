/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: funciones_persona.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */





/** MUESTRA EL MANÚ PARA MANEJAR LAS UTILIDADES CON LAS PERSONAS */
void mostrar_menu_personas()
{
    clrscr();
    SetColores( COLOR_PERSONAS );
	printf( "\n\nSISTEMA DE GESTI%cN DE CR%cDITOS.",acento_O ,acento_E );
    printf( "\n\nOPCIONES DISPONIBLES PARA EL LA GESTI%cN DE CLIENTES:", acento_O );

    if ( existenPersonasAlmacenadas() == 1 && !clientesCargados )
    {
        printf( "\n\n\t1.CARGAR CLIENTES ALMACENADOS");
        clientesCargados = TRUE;
    }

    if (  gTotalClientes >= 1000 )
    {
        printf("\t\n\nNO SE PUEDE CARGAR NUEVOS CLIENTES PORQUE SE LLEG%c AL L%cMITE DE 1000 CLIENTES ACTIVOS.", acento_O, acento_I);
    }

    if (  existenPersonasAlmacenadas() && gTotalClientes == 0 )
    {
        printf( "\n\n\t*** SE DEBE CARGRAR LOS CLIENTES ALMACENADOS ANTES DE AGREGAR UNO NUEVO ****" );
    }

    //if (  existenPersonasAlmacenadas() && gTotalClientes < 1000 )
    else
    {
        printf( "\n\n\t2.CARGAR NUEVO CLIENTE");
    }
    /*else
    {
        printf( "\n\n\t2.CARGAR NUEVO CLIENTE");
    }*/

    if ( gTotalClientes >= 1 )
	{
		printf( "\n\n\t3.LISTAR CLIENTES ACTIVOS" );
		printf( "\n\n\t4.LISTAR CLIENTES INACTIVOS" );
		printf( "\n\n\t5.BUSCAR CLIENTE POR DNI");
		printf( "\n\n\t6.LISTAR CLIENTES POR RANGO DE EDAD" );
		printf( "\n\n\t7.EDITAR DATOS DE CLIENTE");
	}

    printf( "\n\n\t0.VOLVER\n" );
}



/** ADMINISTRA LA GESTIÓN DE CLIENTES */
void opcionesMenuPersonas()
{
    int opcion;
    int i, dni = 0;

    do
    {
        mostrar_menu_personas();
        opcion = OpcionElegida();

        switch ( opcion )
        {
            case 1: //OPCION 2 CARGAR CLIENTES ALMACENADOS
                clrscr();
                printf( "\n\nCARGANDO CLIENTES ACTIVOS.");
                printf( "\n\nESTO PUEDE TOMAR UNOS MINUTOS.  ");
				i = obtenerTotalPersonas( );
				if ( i > 0 )
                {
                    gTotalClientes += i;
                    if ( obtenerTotalLineasArchivo( tempClientesActivos ) > 0 ) 	cargarArbolClientes( &ArbolClientes, tempClientesActivos );
                    if ( obtenerTotalLineasArchivo( tempClientesInactivos ) > 0 ) 	cargarArbolClientes( &ArbolClientesInactivos, tempClientesInactivos );

                    //recorrerLista( listaClienteAmigo );
                    //recorrerListaLineaArchivo( listaClienteLineaArchivo );

			// NO SE PUEDE VERIFICAR LOS AMIGOS REFERIDOS SIN ANTES TENER CARGADOS LOS ÁRBOLES DE CLIENTES ACTIVOS E INACTIVOS
                    if ( obtenerTotalLineasArchivo( tempClientesActivos ) > 0 ) 	verificarAmigos( &ArbolClientes );
                    if ( obtenerTotalLineasArchivo( tempClientesInactivos ) > 0 ) 	verificarAmigos( &ArbolClientesInactivos );

                    printf( "%c", 8 ); //CORRIGE BORRANDO LA ÚLTIMA BARRITA QUE QUEDA DESPUES DE LA ANMACIÓN
                    printf( "\nSE CARGARON %d CLIENTES ACTIVOS.", gTotalClientes );

                }
                else
                {
                    printf( "\nNO SE DETECTARON CLIENTES ALMACENADOS." );
                }
				pause();
                break;

            case 2: //OPCION 1 INGRESAR NUEVO CLIENTE
                gTotalClientes += cargarNuevoCliente( &ArbolClientes );

                if ( hayClienteInactivoNuevo == TRUE ) cargarNuevosInactivos();

                pause();
                break;

            case 3: //OPCION 3 LISTAR CLIENTES EXISTENTES
                clrscr();
				printf( "\n\n\t\tLISTA DE CLIENTES ALMACENADOS (ACTIVOS).\n" );

				if ( obtenerTotalLineasArchivo( tempClientesActivos ) > 0 )
                {
					printf( "\n\n\tDNI\tNOMBRE\t\tAPELLIDO\tEDAD\tINGRESOS\tREFERIDO" );
					countInOrder=0;
					InOrdenPersonaTabulada( ArbolClientes, MostrarPersonasTabuladas );
                }
                else
                {
                	printf( "\n\n\t\tNO HAY INFORMACI%cON ALMACENADA.\n", acento_O );
                }
				pause();
                break;

            case 4: //OPCION 3 LISTAR CLIENTES EXISTENTES
                clrscr();
                printf( "\n\n\t\tLISTA DE CLIENTES ALMACENADOS (INACTIVOS).\n" );
				if ( obtenerTotalLineasArchivo( tempClientesInactivos ) > 0 )
                {
					printf( "\n\n\tDNI\tNOMBRE\t\tAPELLIDO\tEDAD\tINGRESOS\tREFERIDO." );
					countInOrder=0;
					InOrdenPersonaTabulada( ArbolClientesInactivos, MostrarPersonasTabuladas );
                }
				else
				{
					printf( "\n\n\t\tNO HAY INFORMACI%cON ALMACENADA.\n", acento_O );
				}
                pause();
                break;

            case 5: //OPCION 4 BUSCAR CLIENTE POR DNI
                clrscr();
                printf( "\n\nINGRESA EL DNI A BUSCAR: ");
                scanf( "%d", &dni );
                Persona persona = inicializarPersona();

                if ( isIn( arrayDNIClientesActivos, dni, LEN_ARR( arrayDNIClientesActivos )))
                {
                    printf("\n\tEL DNI EST%c ACTIVO: ", acento_A );
                    persona = obtenerPersonaDNI( ArbolClientes, dni ); //SE BUSCA UNA PERSONA ENTRE LOS ACTIVOS
                    printf( "\t%d, %s, %s\n", persona.dni, persona.nombre, persona.apellido );
                }

                else if ( isIn( arrayDNIClientesInactivos, dni, LEN_ARR( arrayDNIClientesInactivos )))
                {
                    printf("\n\tEL DNI EST%c INACTIVO:", acento_A );
                    persona = obtenerPersonaDNI( ArbolClientesInactivos, dni ); //SE BUSCA UNA PERSONA ENTRE LOS ACTIVOS
                    printf( "\t%d, %s, %s\n", persona.dni, persona.nombre, persona.apellido );
                }

                else
                {
                    printf("\nEL DNI INGRESADO NO EXISTE EN LA BASE DE DATOS DE CLIENTES");
                }

                pause();
                break;

            case 6: //OPCION 5 LISTAR CLIENTE POR RANGO DE EDAD
                clrscr();

                printf( "\n\nRECOPILANDO INFORMACI%cN POR FAVOR ESPERE UN MOMENTO. ", acento_O );

                cargarArbolEDADClientes( &ArbolEdadClientes, tempClientesActivos );

                printf( "\n\nINGRESA EL RANGO DE EDADES A BUSCAR (xx xx): ");

                int edadMenor = 0, edadMayor = 0;

                scanf( "%d %d", &edadMenor, &edadMayor );

				printf( "\n\n\tDNI\tNOMBRE\t\tAPELLIDO\tEDAD\tINGRESOS." );

				obtenerPersonasEnRango( ArbolEdadClientes, edadMenor, edadMayor, MostrarEdadesPersonasTabuladas );
				pause();
                break;

            case 7: //OPCION 7 EDITAR DATOS DEL CLIENTE
                clrscr();
                dni = 0;
                printf( "\n\nINGRESA EL DNI DEL CLIENTE A EDITAR: ");
                scanf( "%d", &dni );

                if ( isIn( arrayDNIClientesActivos, dni, LEN_ARR( arrayDNIClientesActivos )))
                {
                    printf("\n\tEL DNI EST%c ACTIVO: ", acento_A );
                    Persona *p = obtenerDireccionPersonaDNI( ArbolClientes, dni ); //SE BUSCA UNA PERSONA ENTRE LOS ACTIVOS
                    editarDatosCliente( p, ACTIVO );
                }

                else if ( isIn( arrayDNIClientesInactivos, dni, LEN_ARR( arrayDNIClientesInactivos )))
                {
                    printf("\n\tEL DNI EST%c INACTIVO:", acento_A );
                    Persona *p = obtenerDireccionPersonaDNI( ArbolClientesInactivos, dni ); //SE BUSCA UNA PERSONA ENTRE LOS ACTIVOS
                    editarDatosCliente( p, INACTIVO );
                }

                else
                {
                    printf("\nEL DNI INGRESADO NO EXISTE EN LA BASE DE DATOS DE CLIENTES");
                }


            	break;

            case 8: //OPCION 6 ASIGNAR REFERIDO A CLIENTE
                //mostrar_menu_personas( );
                break;

            default:
                clrscr();
				if ( clientesCargados ) concatenarClientes();
				clientesCargados = FALSE;
				gTotalClientes = 0;
                break;
        }
    }while( opcion !=0 );
}




/** CARGA UN NUEVO CLIENTE EN EL ÁRBOL DE CLIENTES*/
int cargarNuevoCliente( ArbolPersonas *arbol )
{
	int i = 0, opcion = 1;

	do {
        Persona persona = ingresarDatosPersona( );

	    if( persona.dni == 0 )
        {
            opcion = 0; //SI EL DNI ES CERO SALE
        }

	    else if ( persona.dni == -1 ) opcion = 1;//SI EL DNI EXISTE EN LA BASE DE DATOS CONTINÚA

	    else    	//CARGA EL NUEVO CLIENTE EN EL ÁRBOL DE CLIENTES
        {
	    	persona.estado = ACTIVO;
	    	int res = InsertarPersonaArbol( arbol, persona.dni, persona ); //AGREGA LA PERSONA AL ÁRBOL
            if ( res == TRUE )
            {
                if( dniAmigo != 0 )
				{
                	agregarElementoLista( listaClienteAmigo, persona.dni, dniAmigo ); //ACTUALIZA LA LISTA DE CLIENTE-REFERIDO
                	Persona p = inicializarPersona();
                	p.dni = dniAmigo;
                	dniAmigo = 0;
                	almacenarPersonas( p, tempClientesInactivos );
                	arrayDNIClientesInactivos[ LEN_ARR( arrayDNIClientesInactivos ) +1 ] = p.dni;
                	hayClienteInactivoNuevo = TRUE;
				}

                almacenarPersonas( persona, tempClientesActivos );

                printf( "\nEL NUEVO CLIENTE SE CARG%c CON %cXITO!\n", acento_O, acento_E );

                i++;
            }
            else
            {
                printf( "\nHUBO UN ERROR AL CARGAR EL NUEVO CLIENTE!\n" );
                opcion = 0; //SI EL DNI ES CERO SALE
                pause();
            }
        }
    } while( opcion !=0 );

	printf( "\nFINALIZO LA CARGA DE PERSONAS. SE CARGARON %d PERSONA/S\n", i);
	return i;
}




/** FUNCIÓN QUE ITERA EL INRESO MANUAL DE LOS DATOS DE LOS CLIENTES */
Persona ingresarDatosPersona( )
{
	clrscr();
	Persona persona = inicializarPersona();
	Persona amigo = inicializarPersona();
	persona.amigo = &amigo;
	dniAmigo = 0;

	printf( "\nINGRESO DE NUEVOS CLIENTES" );
	printf( "\n---------------------------------");
	printf( "\nIngrese el dni (cero para finalizar): ");
    scanf( "%d", &persona.dni );

    if( persona.dni == 0 )//SI EL DNI ES CERO SALE
    {
		return persona;
    }

    else if ( isIn( arrayDNIClientesActivos, persona.dni, LEN_ARR( arrayDNIClientesActivos )))//SALE PORQUE EL DNI EXISTE
    {
        printf( "\nVerificando . . . .  ");
        printf( "\n\n\t***EL DNI INGRESADO EXISTE EN LA BASE DE DATOS***" );
        printf( "\n\n\t\t***INTENTA INGRESAR OTRO POR FAVOR***" );
        persona.dni = -1;
        pause();
		return persona;
    }

    else if ( isIn( arrayDNIClientesInactivos, persona.dni, LEN_ARR( arrayDNIClientesInactivos )))//SALE PORQUE EL DNI EXISTE
    {
        printf( "\nVerificando . . . .  ");
        printf( "\n\n\t***EL DNI INGRESADO EXISTE EN LA BASE DE DATOS INACTIVO***" );
        printf( "\n\n\t\t***INTENTA INGRESAR OTRO POR FAVOR***" );
        persona.dni = -1;
        pause();
		return persona;
    }

    else
    {
		printf( "Ingrese NOMBRE y APELLIDO: " );
		scanf( "%s %s", persona.nombre, persona.apellido );
		printf( "Ingrese la EDAD (>18 a%cos): ", enie );
		scanf( "%d", &persona.edad );
		printf( "Ingrese el monto de INGRESOS: " );
		scanf( "%d", &persona.ingresos );

		do
		{
			printf( "\nIngrese el DNI de un amigo (Cero para ninguno): ");
			scanf( "%d", &dniAmigo );

		}	while( dniAmigo == persona.dni );

		arrayDNIClientesActivos[ LEN_ARR( arrayDNIClientesActivos ) +1 ] = persona.dni;
    }
    return persona;
}



/** DEVUELVE UN STRUCT DE PERSONA INICIALIZADO CON DATOS GENÉRICOS */
Persona inicializarPersona()
{
	Persona persona;
	persona.dni = 0;
	strcpy( persona.nombre, "-------" );
    strcpy( persona.apellido, "-------" );
	persona.edad = 0;
	persona.ingresos = 0;
	persona.creditosActivos[0] = 0;
	persona.creditosActivos[1] = 0;
    persona.amigo = NULL;
    persona.estado = INACTIVO;
    return persona;
}



/** ACTUALIZA EL ARCHIVO DE CLIENTES */
void almacenarPersonas( Persona *persona, const char *filename )
{
	/* PERSONA: DNI (clave), NOMBRE, APELLIDO, EDAD, INGRESOS, CRÉDITOS, REFERIDOS, ESTADO */

	FILE *file;

	if (  !existenPersonasAlmacenadas() ) //DETECTA QUE ES EL PRIMER CLIENTE DEL SISTEMA Y CREA EL ARCHIVO
	{
		file = abrirArchivoEscritura( filename );
        fprintf( file, "%03d;%s;%s;%d;%d;%d;%03d;%d\n", persona->dni, persona->nombre, persona->apellido, persona->edad, persona->ingresos, 0, dniAmigo, persona->estado );
		fclose( file );
	}
	else
	{
		file = abrirArchivoEscrituraContinua( filename );
        fprintf( file, "%03d;%s;%s;%d;%d;%d;%03d;%d\n", persona->dni, persona->nombre, persona->apellido, persona->edad, persona->ingresos, 0, dniAmigo, persona->estado );
		fclose( file );
	}

}




/** CARGA EL ÁRBOL DE CLIENTES CON LOS DEL ARCHIVO DE CLIENTES */
void cargarArbolClientes( ArbolPersonas *arbol, const char *filename )
{
	FILE *file = abrirArchivoLectura( filename );
	nroLineaArchivo = 0;

	char linea[1024];
	while( fgets(linea, 1024, file) )
	{
		int n = strlen( linea );
		linea[n-1] = 0;         //ELIMINACIÓN DEL \n
		parcerarDNIArchivo( linea, arbol );
	}
	fclose( file );
}




/** PARCEA CADA LÍNEA DEL CSV */
void parcerarDNIArchivo( char linea[1024], ArbolPersonas *arbol )
{
	int ln = strlen( linea );
	int cuentaDato = 0;
	char dato[ 100 ], caracter;
	int i, j = 0, res = 0;

	Persona persona = inicializarPersona();

	for ( i = 0; i <= ln; i++ )
	{
		caracter = linea[i];
		if ( caracter != ';' && caracter != 0 )
		{
			dato[ j ] = caracter;
			dato[ j + 1 ] = 0;//FORMA UNA CADENA
			j++;
		}
		else
		{
			j = 0;
			cuentaDato++;
 /* PERSONAS:
	DNI	(clave)
	NOMBRE
	APELLIDO
	EDAD
	INGRESOS
	CRÉDITOS    //ARRAY DE CRÉDITOS
	REFERIDOS
	ESTADO
*/
			switch ( cuentaDato )
			{
				case 1: persona.dni = atoi( dato ); agregarElementoListaLineaClienteArchivo( listaClienteLineaArchivo, persona.dni, nroLineaArchivo++ ); break;
				case 2: strcpy( persona.nombre, dato ); break;
				case 3: strcpy( persona.apellido, dato ); break;
				case 4: persona.edad = atoi( dato );  break;
				case 5: persona.ingresos  = atoi( dato ); break;
				case 7: agregarElementoLista( listaClienteAmigo, persona.dni, atoi( dato )); break;//CREA LA LISTA SIMPLE DE CLIENTES Y AMIGOS
				case 8: res = InsertarPersonaArbol( arbol, persona.dni, persona ); cuentaDato = 0; break;
			}
			strcpy( dato, "" );
		}
	}
}



/** VERIFICA LA EXISTENCIA DEL ARCHIVO DE CLIENTES */
int existenPersonasAlmacenadas()
{
	int retorno = 0;
	FILE *file = abrirArchivoLectura( archivoPersonas );

	if  ( file ) retorno = 1;

	fclose( file );

	return retorno;
}



/** VERIFICA LA EXISTENCIA DEL ARCHIVO DE CRÉDITOS */
int existenCreditosAlmacenados()
{
	int retorno = 0;
	FILE *f = abrirArchivoLectura( archivoCreditos );
	if  ( f ) retorno = 1;
	fclose( f );
	return retorno;
}



/** RECORRE EL ARCHIVO DE CLIENTES Y OBTIENE EL NÚMERO DE CLIENTES ACTIVOS */
int obtenerTotalPersonas( )
{
	int retorno = 0;
	int i = 0, n, estado, j = 0, k = 0, barra = 0;
	char arrayBarra[]={'|','/','-','\\','|','/','-'};
    FILE *file = abrirArchivoEscritura( tempClientesActivos );//SOBREESCRIBE SI EXISTÍA
    fclose( file );

    file = abrirArchivoEscritura( tempClientesInactivos );//SOBREESCRIBE SI EXISTÍA
    fclose( file );

    char linea[ 1024 ];
    char dni[ 20 ];
    FILE *filep = abrirArchivoLectura( archivoPersonas );

    while( fgets( linea, 1024, filep ))
    {
        n = strlen( linea );
        linea[n-1] = 0;//ELIMINACIÓN DEL \n
        estado = atoi( &linea[n-2] );//OBTIENE EL ÚLTIMO CARACTER

        i=0;
        do      //OBTIENE EL DNI DEL CLIENTE
        {
            if( linea[ i ] != ';' )
            {
                dni[ i ] = linea[ i ];
                i++;
            }
            else
            {
                dni[ i ] = 0;
                i=-1;
            }
        } while( i < n && i > 0 );

        //printf("%s, ", dni );

        int d = atoi( &dni );

        if ( estado == ACTIVO )
        {
            arrayDNIClientesActivos[ j++ ] = d;//CARGA SOLO LOS DNIs PARA VERIFICAR SU EXISTENCIA MÁS RAPIDAMENTE
            cargarArchivoTemporalClientes( linea, tempClientesActivos );
            retorno++;
        }

        if ( estado == INACTIVO )
        {
            arrayDNIClientesInactivos[ k++ ] = d;//CARGA SOLO LOS DNIs PARA VERIFICAR SU EXISTENCIA MÁS RAPIDAMENTE
            cargarArchivoTemporalClientes( linea, tempClientesInactivos );
        }

        printf( "%c", arrayBarra[barra] );  //ANIMACIÓN DE BARRA PARA DENOTAR PROCESAMIENTO
        printf( "%c", 8 );
		barra++;
		if ( barra==7) barra=0;
    }
    fclose( filep );
	return retorno;
}



/** CONCATENA LOS ARCHIVOS TEMPORALES DE ACTIVOS E INACTIVOS */
void concatenarClientes()
{
    char linea[ 128 ];
    printf("\n\tREALIZANDO BACKUP DE LA INFORMACI%cN AGUARDE POR FAVOR....", acento_O);

    remove( archivoPersonas );

    strcpy( linea, "@copy ");
    strcat( linea, tempClientesActivos );
    strcat( linea, "+" );
    strcat( linea, tempClientesInactivos );
    strcat( linea, " " );
    strcat( linea, archivoPersonas );
    strcat( linea, ">nul" );

    system( linea );
    remove( tempClientesInactivos );
    remove( tempClientesActivos );
}



/** CARGA EL ÁRBOL DE EDADES DE LOS CLIENTES CON LOS DEL ARCHIVO DE CLIENTES ACTIVOS*/
void cargarArbolEDADClientes( ArbolPersonas *arbol, const char *filename )
{
	FILE *file = abrirArchivoLectura( filename );

	if ( file != NULL )
	{
        fclose( file );
		file = abrirArchivoLectura( filename );

        char linea[1024];
        while( fgets(linea, 1024, file) )
        {
            int n = strlen( linea );
            linea[n-1] = 0;         //ELIMINACIÓN DEL \n
            parcerarEDADArchivo( linea, arbol );
        }
        fclose( file );
	}
	else
	{
		printf( "\nEL ARCHIVO NO SE PUDO ABRIR.\n");
	}
}



/** PARCEA CADA LÍNEA DEL CSV */
void parcerarEDADArchivo( char linea[1024], ArbolPersonas *arbol )
{
	int ln = strlen( linea );
	int cuentaDato = 0;
	char dato[ 100 ];
	char caracter;
	int i, j = 0, res = 0;

	Persona persona;
	persona = inicializarPersona();

	for ( i = 0; i <= ln; i++ )
	{
		caracter = linea[i];
		if ( caracter != ';' && caracter != 0 )
		{
			dato[ j ] = caracter;
			dato[ j + 1 ] = 0;//FORMA UNA CADENA
			j++;
		}
		else
		{
			j = 0;
			cuentaDato++;
 /* PERSONAS:
	DNI	(clave)
	NOMBRE
	APELLIDO
	EDAD
	INGRESOS
	CRÉDITOS    //ARRAY DE CRÉDITOS
	REFERIDOS
	ESTADO
*/
			switch ( cuentaDato )
			{
				case 1: persona.dni = atoi( dato );  break;
				case 2: strcpy( persona.nombre, dato ); break;
				case 3: strcpy( persona.apellido, dato ); break;
				case 4: persona.edad = atoi( dato );  break;
				case 5: persona.ingresos  = atoi( dato );  break;
				case 6: res = InsertarPersonaArbol( arbol, persona.edad, persona ); cuentaDato = 0; break;
			}
			strcpy( dato, "" );
		}
	}
}




/** DEVUELVE EL DNI DEL AMIGO DEL CLIENTE */
int obtenerAmigo ( int elemento )
{
    Lista *miLista = listaClienteAmigo;
	int retorno = 0;
	while( miLista != NULL  )
	{
		if ( miLista->cliente == elemento )
		{
			//printf("\nCliente: %d Amigo: %d", miLista->cliente, miLista->amigo);
			retorno = miLista->amigo;
		}
		miLista = miLista->siguiente;
	}
	return retorno;
}




/** DEVUELVE EL DNI DEL AMIGO DEL CLIENTE */
int obtenerLineaArchivoCliente ( int elemento )
{
    ListaClienteLineaArchivo *miLista = listaClienteLineaArchivo;
	int retorno = 0;
	while( miLista != NULL  )
	{
		if ( miLista->cliente == elemento )
		{
			//printf("\nCliente: %d linea: %d", miLista->cliente, miLista->linea);
			retorno = miLista->linea;
		}
		miLista = miLista->siguiente;
	}
	return retorno;
}




/** RECIVE UNA PERSONA PARA EDITAR SUS DATOS */
void editarDatosCliente( Persona *persona, int estado )
{
	int opcion, editar = 0, dniReferido = 0;

	int linea = obtenerLineaArchivoCliente( persona->dni );
	do
	{
		persona->estado = estado;

		printf( "\n\t(DNI, NOMBRE, APELLIDO, EDAD, INGRESOS, ESTADO)" );
		printf( "\n\t%03d, %-9s, %-9s, %-2d, %-5d ", persona->dni, persona->nombre, persona->apellido, persona->edad, persona->ingresos );
		if ( estado == ACTIVO ) printf( "ACTIVO, " );
		else printf( "INACTIVO, " );
		printf( " (%d)\n", linea );

		printf( "\n\tOPCIONES PARA EDITAR DEL CLIENTE" );
		printf( "\n\t----------------------------------------------" );
		printf( "\n\t1.EDITAR EL NOMBRE." );
		printf( "\n\t2.EDITAR EL APELLIDO.");
		printf( "\n\t3.EDITAR LA EDAD." );
		printf( "\n\t4.EDITAR EL MONTO DE INGRESOS.");
		printf( "\n\t5.EDITAR ESTADO.");
		printf( "\n\t6.EDITAR REFERIDO.");
		printf( "\n\t0.VOLVER.");

		printf( "\n\tSELECCIONE UNA OPCI%cN: ", acento_O );
		scanf( "%d", &opcion );


		switch ( opcion )
		{
		case 1: //OPCION 1 EDITAR NOMBRE
			printf( "\nIngresa el nuevo NOMBRE: " );
			scanf( "%s", persona->nombre );
			editar=1;
			break;

		case 2: //OPCION 2 EDITAR APELLIDO
			printf( "\nIngresa el nuevo APELLIDO: " );
			scanf( "%s", persona->apellido );
			editar=1;
			break;

		case 3: //OPCION 3 EDITAR EDAD
			printf( "\nIngresa la nueva EDAD: " );
			scanf( "%d", &persona->edad );
			editar=1;
			break;

		case 4: //OPCION 4 EDITAR INGRESOS
			printf( "\nIngresa el nuevo monto de INGRESOS: " );
			scanf( "%d", &persona->ingresos );
			editar=1;
			break;

		case 5: //OPCION 5 EDITAR ESTADO

			editar=0;
			printf( "\nEl ESTADO actual es: " );

			if ( estado == ACTIVO ) printf( "ACTIVO" );
			else printf( "INACTIVO" );

			printf( "\nIngresa el nuevo ESTADO ( 1 = ACTIVO, 0 = INACTIVO) : " );
			scanf( "%d", &estado );

			//AL CAMBIAR EL ESTADO DEL CLIENTE HAY QUE CAMBIARLO DE ARCHIVO TEMPORAL
			if ( estado == ACTIVO )
			{
				persona->estado = estado;
				almacenarPersonas( persona, tempClientesActivos );
				borrarLinea( linea, tempClientesInactivos );
			}
			if ( estado == INACTIVO )
			{
				persona->estado = estado;
				almacenarPersonas( persona, tempClientesInactivos );
				borrarLinea( linea, tempClientesActivos );
			}


			clrscr();
			break;

		case 6: //OPCION 6 EDITAR REFERIDO
			dniReferido = 0;
			printf( "\nIngresa el DNI del referido: " );
			scanf( "%d", &dniReferido );
			editar=1;
			break;

		default:
			clrscr();
			printf( "\n\tOPCI%cN NO V%cLIDA.\n", acento_O, acento_A );
			editar=0;
			break;
		}

		if ( editar )
		{
			if ( estado == ACTIVO )
			{
				actualizarLineaArchivo( tempClientesActivos, linea, persona, dniReferido );
			}
			if ( estado == INACTIVO )
			{
				actualizarLineaArchivo( tempClientesInactivos, linea, persona, dniReferido );
			}

			editar=0;
			clientesCargados = TRUE;
		}

	}	while( opcion != 0 );
}



/** ACTUALIZA EL ÁRBOL DE CLIENTES INACTIVOS */
void cargarNuevosInactivos()
{
	hayClienteInactivoNuevo = FALSE;
	ArbolClientesInactivos = NULL;
	cargarArbolClientes( &ArbolClientesInactivos, tempClientesInactivos );
	verificarAmigos( &ArbolClientesInactivos );
}
