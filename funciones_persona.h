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

    if ( existenPersonasAlmacenadas() == 1 )
    {
        printf( "\n\n\t1.CARGAR CLIENTES ALMACENADOS");
    }

    if (  gTotalClientes >= 1000 )
    {
        printf("\t\n\nNO SE PUEDE CARGAR NUEVOS CLIENTES PORQUE SE LLEG%c AL L%cMITE DE 1000 CLIENTES ACTIVOS.", acento_O, acento_I);
    }

    if (  existenPersonasAlmacenadas() == 0 && gTotalClientes < 1000 )
    {
        printf( "\n\n\t2.CARGAR NUEVO CLIENTE");
    }

    if (  existenPersonasAlmacenadas() == 1 && gTotalClientes == 0 )
    {
        printf( "\n\n\t*** SE DEBE CARGRAR LOS CLIENTES ALMACENADOS ****" );
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
		printf( "\n\n\t7.ASIGNAR AMIGO REFERIDO");
	}

    printf( "\n\n\t0.VOLVER\n" );
}



/** ADMINISTRA LA GESTIÓN DE CLIENTES */
void opcionesMenuPersonas()
{
    int opcion;
    int i;

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
                    cargarArbolClientes( &ArbolClientes, tempClientesActivos );
                    cargarArbolClientes( &ArbolClientesInactivos, tempClientesInactivos );

                    verificarAmigos( ArbolClientes );
                    verificarAmigos( ArbolClientesInactivos );

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
                pause();
                break;

            case 3: //OPCION 3 LISTAR CLIENTES EXISTENTES
                clrscr();
                printf( "\n\n\t\tLISTA DE CLIENTES ALMACENADOS (ACTIVOS).\n" );
                printf( "\n\n\tDNI\tNOMBRE\t\tAPELLIDO\tEDAD\tINGRESOS\tREFERIDO" );
                countInOrder=0;
                InOrdenPersonaTabulada( ArbolClientes, MostrarPersonasTabuladas );
                pause();
                break;

            case 4: //OPCION 3 LISTAR CLIENTES EXISTENTES
                clrscr();
                printf( "\n\n\t\tLISTA DE CLIENTES ALMACENADOS (INACTIVOS).\n" );
                printf( "\n\n\tDNI\tNOMBRE\t\tAPELLIDO\tEDAD\tINGRESOS\tREFERIDO." );
                countInOrder=0;
                InOrdenPersonaTabulada( ArbolClientesInactivos, MostrarPersonasTabuladas );
                pause();
                break;

            case 5: //OPCION 4 BUSCAR CLIENTE POR DNI
                clrscr();
                int dni = 0;
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

            case 7: //OPCION 6 ASIGNAR AMIGO REFERIDO
                //mostrar_menu_personas( );
                break;

            default:
                clrscr();
                if (  existenPersonasAlmacenadas() == 1 && gTotalClientes > 1 ) concatenarClientes();
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

	    else    //CARGA EL NUEVO CLIENTE EN EL ÁRBOL DE CLIENTES
        {
            int res = InsertarPersonaArbol( arbol, persona.dni, persona );
            if ( res == TRUE )
            {
                printf( "\nEL NUEVO CLIENTE SE CARG%c CON %cXITO!\n", acento_O, acento_E );
                almacenarPersonas( persona );
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
		arrayDNIClientesActivos[ LEN_ARR( arrayDNIClientesActivos ) +1 ] = persona.dni;
    }
    return persona;
}



/** DEVUELVE UN STRUCT DE PERSONA INICIALIZADO CON DATOS GENÉRICOS */
Persona inicializarPersona()
{
	Persona persona;
	persona.dni = 0;
	strcpy( persona.nombre, "---" );
    strcpy( persona.apellido, "---" );
	persona.edad = 0;
	persona.ingresos = 0;
	persona.creditosActivos[0] = 0;
	persona.creditosActivos[1] = 0;
    persona.amigo = NULL;
    persona.estado = ACTIVO;
    return persona;
}



/** ACTUALIZA EL ARCHIVO DE CLIENTES */
void almacenarPersonas( Persona *persona )
{
	FILE *file = abrirArchivoEscrituraContinua( tempClientesActivos );

	if ( file != NULL )
	{
        fprintf( file, "%03d;%s;%s;%d;%d;%d;%03d;%d\n", persona->dni, persona->nombre, persona->apellido, persona->edad, persona->ingresos, 0, 0, ACTIVO );
	}
	else
	{
		printf( "\nERROR AL ABRBIR EL ARCHIVO DE CLIENTES!!\n");
		pause();
	}
	fclose( file );
}



/** CARGA EL ÁRBOL DE CLIENTES CON LOS DEL ARCHIVO DE CLIENTES */
void cargarArbolClientes( ArbolPersonas *arbol, const char *filename )
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
            parcerarDNIArchivo( linea, arbol );
        }
        fclose( file );
	}
	else
	{
		printf( "\nEL ARCHIVO NO SE PUDO ABRIR.\n");
	}

	//recorrerLista( lista );
}



/** PARCEA CADA LÍNEA DEL CSV */
void parcerarDNIArchivo( char linea[1024], ArbolPersonas *arbol )
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
				case 5: persona.ingresos  = atoi( dato ); break;
				case 7: agregarElementoLista( lista, persona.dni, atoi( dato )); break;//CREA LA LISTA SIMPLE DE CLIENTES Y AMIGOS
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

	return retorno;
}



/** VERIFICA LA EXISTENCIA DEL ARCHIVO DE CRÉDITOS */
int existenCreditosAlmacenados()
{
	int retorno = 0;
	FILE *file = abrirArchivoLectura( archivoCreditos );
	if  ( file ) retorno = 1;

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
    file = abrirArchivoLectura( archivoPersonas );

    while( fgets( linea, 1024, file ))
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
    fclose( file );
	return retorno;
}



/** CONCATENA LOS ARCHIVOS TEMPORALES DE ACTIVOS E INACTIVOS */
void concatenarClientes()
{
    char linea[1024];
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


