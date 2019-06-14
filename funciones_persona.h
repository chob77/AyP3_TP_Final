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


Persona inicializarPersona();
Persona ingresarDatosPersona();
int obtenerTotalPersonas();
void parcerarLineaArchivo( char linea[1024], ArbolPersonas *arbol );
void cargarArchivoTemporalClientesActivos( char *linea );
void parcerarLineaArchivoPorAmigo( char *linea, Persona *listaPersonas, int pos_persona );
void concatenarClientes();


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
        printf("\t\n\nNO SE PUEDE CARGAR NUEVOS CLIENTES PORQUE SE LLEG%c AL L%cMITE DE 1000 CLIENTES ACTIVOS.",acento_A, acento_O, acento_I);
    }

    if (  existenPersonasAlmacenadas() == 0 && gTotalClientes < 1000 )
    {
        printf( "\n\n\t2.CARGAR NUEVO CLIENTE");
    }

    if (  existenPersonasAlmacenadas() == 1 && gTotalClientes == 0 )
    {
        printf( "\n\n\t*** SE DEBE CARGRAR LOS CLIENTES ALMACENADOS ****" );
    }
    else
    {
        printf( "\n\n\t2.CARGAR NUEVO CLIENTE");
    }

    if ( gTotalClientes >= 1 )
	{
		printf( "\n\n\t3.LISTAR CLIENTES EXISTENTES" );
		printf( "\n\n\t4.BUSCAR CLIENTE POR DNI");
		printf( "\n\n\t5.LISTAR CLIENTES POR RANGO DE EDAD" );
		printf( "\n\n\t6.ASIGNAR AMIGO REFERIDO");
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
                printf( "\n\nESTO PUEDE TOMAR UNOS MINUTOS.");
				i = obtenerTotalPersonas( );
				if ( i > 0 )
                {
                    gTotalClientes += i;
                    cargarArbolClientes( &ArbolClientes );
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
                printf( "\n\n\t\tLISTA DE CLIENTES ALMACENADOS.\n" );
                printf( "\n\n\tDNI\tNOMBRE\t\tAPELLIDO\tEDAD\tINGRESOS." );
                countInOrder=0;
                InOrdenPersonaTabulada( ArbolClientes, MostrarPersonasTabuladas );
                pause();
                break;

            case 4: //OPCION 4 BUSCAR CLIENTE POR DNI
                //mostrar_menu_personas( );
                break;

            case 5: //OPCION 5 LISTAR CLIENTE POR RANGO DE EDAD
                //mostrar_menu_personas( );
                break;

            case 6: //OPCION 6 ASIGNAR AMIGO REFERIDO
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
	    else    //CARGA EL NUEVO CLIENTE EN EL ÁRBOL DE CLIENTES
        {
            //VERIFICAR SI EL CLIENTE EXISTE
            //int res = BuscarPersona( arbol, persona.dni );

            //if ( res == FALSE ) //EL CLIENTE NO EXISTE
            //{
            int res = InsertarPersonaArbol( arbol, persona.dni, persona );
            if ( res == TRUE )
            {
                printf( "\nEL NUEVO CLIENTE SE CARG%c CON %cXITO!\n", acento_O, acento_E );
                almacenarPersonas( persona );
                i++;
                //pause();
            }
            else
            {
                printf( "\nHUBO UN ERROR AL CARGAR EL NUEVO CLIENTE!\n", acento_O, acento_E );
                opcion = 0; //SI EL DNI ES CERO SALE
                pause();
            }
            //}
        }
    } while( opcion !=0 );

	printf( "\nFINALIZO LA CARGA DE PERSONAS. SE CARGARON %d PERSONA/S\n", --i);
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

    int len = sizeof(arrayDNIClientes)/sizeof(arrayDNIClientes[0]);
    if( persona.dni == 0 )//SI EL DNI ES CERO SALE
    {
		return persona;
    }
    else if ( isIn( arrayDNIClientes, persona.dni, len ))//SALE PORQUE EL DNI EXISTE
    {
        printf( "\nVerificando . . . .  ");
        printf( "\n\n\t***EL DNI INGRESADO YA EXISTE EN LA BASE DE DATOS***" );
        printf( "\n\n\t\t***INTENTA INGRESAR OTRO***" );
        persona.dni == 0;
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
		arrayDNIClientes[ len +1 ] = persona.dni;
    }
    return persona;
}



/** DEVUELVE UN STRUCT DE PERSONA INICIALIZADO CON DATOS GENÉRICOS */
Persona inicializarPersona()
{
	Persona persona;
	persona.dni = 0;
	strcpy( persona.nombre, "------------------------------" );
    strcpy( persona.apellido, "------------------------------" );
	persona.edad = 0;
	persona.ingresos = 0;
	persona.creditosActivos[0] = 0;
	persona.creditosActivos[1] = 0;
    persona.amigo = NULL;
    persona.estado = ACTIVO;
    return persona;
}



void buscarPersonaNombre( Persona *listaPersonas )
{
	char nombre[20];
	clrscr();
	printf( "BUSCAR PERSONA POR NOMBRE");
	printf( "\nIngrese el nombre a buscar: ");
    scanf( "%s", nombre );
    int i=0;

    do
    {
    	if( strncmp( (*listaPersonas).nombre, nombre, 20 ) == 0 )
    	{
    		printf( "\nNOMBRE HALLADO:");
    		printf( "\n-------------------------");
    		printf( "\nLegajo\tNombre\tapellido" );
    		printf( "\n%d\t%s\t%s\n", (*listaPersonas).dni, (*listaPersonas).nombre, (*listaPersonas).apellido );

    		i=10;
    	}
    	i++;
        listaPersonas++;
    } while( i < 10 );

    if ( i == 10) printf( "\nNOMBRE NO HALLADO.\n");
}




void asignarAmigoPersona( Persona *listaPersonas  )
{
    clrscr();
    printf( "ASIGNAR AMIGO A PERSONA");
    printf( "\n-------------------------");
    //mostrarListaPersonas( listaPersonas );

    printf( "\nSELECCIONE LA PERSONA A ASIGNARLE UN AMIGO");
    int nroPersonaAAsignarleAmigo;
    //nroPersonaAAsignarleAmigo = seleccionarPersona();

    //mostrarListaPersonas( listaPersonas );

    printf( "\nSELECCIONE UN AMIGO PARA LA PERSONA: %d", (nroPersonaAAsignarleAmigo+1) );
    int nroPersonaAmigo;
    //nroPersonaAmigo = seleccionarPersona();

    Persona *persona;
    persona = listaPersonas + nroPersonaAAsignarleAmigo;
    Persona *amigo;
    amigo = listaPersonas + nroPersonaAmigo;

    persona->amigo = amigo;

    printf( "\nLa persona es: %s --> su amigo es: %s\n", (*persona).nombre, (*amigo).nombre );
}




/** ACTUALIZA EL ARCHIVO DE CLIENTES */
void almacenarPersonas( Persona *persona )
{
	//FILE *file = abrirArchivoEscritura( archivoPersonas );
	FILE *file = abrirArchivoEscrituraContinua( tempClientesActivos );

	if ( file != NULL )
	{
		//fprintf( file, "DNI;NOMBRE;APELLIDO;EDAD;INGRESOS;CRÉDITOS;REFERIDO;ESTADO");

        fprintf( file, "%03d;%s;%s;%d;%d;%d;%03d;%d\n", persona->dni, persona->nombre, persona->apellido, persona->edad, persona->ingresos, 0, 0, ACTIVO );
		//clrscr();
		//printf( "\n\tLA INFORMACI%cN SE ALMACEN%c CORRECTAMENTE.\n", acento_O, acento_O );
	}
	else
	{
		printf( "\nERROR AL ABRBIR EL ARCHIVO DE CLIENTES!!\n");
		pause();
	}
	fclose( file );
}




void verificarAmigos( Persona *listaPersonas )
{
	FILE *file = abrirArchivoLectura( archivoPersonas );

	// printf( "\nVERIFICACI%cN DE AMIGOS\n", acento_O );

	if ( file != NULL )
	{
		int totalLineas = obtenerTotalLineasArchivo( file );
		file = abrirArchivoLectura( archivoPersonas );
		int pos_persona = 0;

		if ( totalLineas > 0 )
		{
			char linea[1024];
			while( fgets( linea, 1024, file ))
			{
				int n = strlen( linea );//ELIMINACIÓN DEL \n
				linea[n-1] = 0;
				parcerarLineaArchivoPorAmigo( linea, listaPersonas, pos_persona );
				pos_persona++;
			}
			fclose( file );
			if ( pos_persona > 9 ) pos_persona=0;
		}
		else
		{
			printf( "\nEL ARCHIVO DE PERSONAS EST%c VAC%cO.\n", acento_A, acento_I );
		}

	}
}



/** CARGA EL ÁRBOL DE CLIENTES CON LOS DEL ARCHIVO DE CLIENTES */
void cargarArbolClientes( ArbolPersonas *arbol )
{
	FILE *file = abrirArchivoLectura( tempClientesActivos );

	if ( file != NULL )
	{
		int totalLineas = 0;
		file = abrirArchivoLectura( tempClientesActivos );

        char linea[1024];
        char c;
        while(fgets(linea, 1024, file))
        {
            int n = strlen( linea );
            linea[n-1] = 0;         //ELIMINACIÓN DEL \n
            parcerarLineaArchivo( linea, arbol );
        }
        fclose( file );
	}
	else
	{
		printf( "\nEL ARCHIVO NO SE PUDO ABRIR.\n");
	}

	//verificarAmigos( listaPersonas );
}




void parcerarLineaArchivo( char linea[1024], ArbolPersonas *arbol )
{
	//printf( "\nL%cnea obtenida: %s\n", acento_i, linea );
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
			//printf ( "CUENTADATO:%d. ", cuentaDato );

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
				// case 1: printf( "EL DNI es: %s\n", dato); persona.dni = atoi( dato );  break;
				case 1: persona.dni = atoi( dato );  break;
				// case 2: printf( "EL NOMBRE es: %s\n", dato); strcpy( persona.nombre, dato ); break;
				case 2: strcpy( persona.nombre, dato ); break;
				// case 3: printf( "EL APELLIDO es: %s\n", dato); strcpy( persona.apellido, dato ); break;
				case 3: strcpy( persona.apellido, dato ); break;
				case 4: persona.edad = atoi( dato );  break;
				case 5: persona.ingresos  = atoi( dato );  break;
				// case 4: printf( "EL AMIGO es: %s\n", dato ); break;
				case 6: res = InsertarPersonaArbol( arbol, persona.dni, persona ); cuentaDato = 0; break;
			}
			strcpy( dato, "" );
		}

		/*if ( cuentaDato == 4 ) {
			// printf( "%02d, %d\t%s\t%s\t%s\n", pos_persona, persona.dni, persona.nombre, persona.apellido, persona.amigo );
			listaPersonas[ pos_persona ] = persona;
			cuentaDato = 0;
		}*/
	}
}




// Persona *buscarAmigoNombre( Persona *listaPersonas, char nombre[20] )
int buscarAmigoNombre( Persona *listaPersonas, char nombre[20] )
{
    int i = 0;
	// Persona *retorno;
	int retorno = 0;

    do
    {
    	if( strncmp( (*listaPersonas).nombre, nombre, 20 ) == 0 )
    	{
    		// printf( "\nAMIGO HALLADO:");
    		// printf( "-------------------------\n");
    		// printf( "\nLegajo\tNombre\tapellido" );
    		// printf( "\n%d\t%s\t%s\n", (*listaPersonas).dni, (*listaPersonas).nombre, (*listaPersonas).apellido );
			// retorno = listaPersonas;
			retorno++;

    		i=10;
    	}
    	i++;
        listaPersonas++;
    } while( i < 10 );

    if ( i == 10) printf( "\nNOMBRE NO HALLADO.\n");

	return retorno;
}



void parcerarLineaArchivoPorAmigo( char linea[1024], Persona *listaPersonas, int pos_persona )
{
	//printf( "\nL%cnea obtenida: %s\n", acento_i, linea );
	int ln = strlen( linea );
	int cuentaDato = 0;
	char dato[ 100 ];
	char caracter;
	int a, i, j=0;
	//1-DNI
	//2-NOMBRE
	//3-APELLIDO
	//4-AMIGO

	Persona *persona;
	Persona *amigo;
	// persona = inicializarPersona();

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
			//printf ( "CUENTADATO:%d. ", cuentaDato );

			switch ( cuentaDato )
			{
				// case 1: persona.dni = atoi( dato );  break;
				// case 2: strcpy( persona.nombre, dato ); break;
				// case 3: strcpy( persona.apellido, dato ); break;
				case 4:
					a = strcmp( "----", dato );
					persona = listaPersonas + pos_persona;
					// printf( "EL AMIGO de %s es: %s (%d) \n", persona->nombre, dato, a );
					if ( a != 0 )
					{
						amigo = listaPersonas + buscarAmigoNombre( listaPersonas, dato );
						// printf( "%02d, %d\t%s\t%s\t%s\n", pos_persona, amigo->dni, amigo->nombre, amigo->apellido, amigo->amigo );
						persona->amigo = amigo;
						cuentaDato = 0;
					}

					break;
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
	int i = 0, n, estado, j=0;
    FILE *file = abrirArchivoEscritura( tempClientesActivos );//SOBREESCRIBE SI EXISTÍA
    fclose( file );

    file = abrirArchivoEscritura( tempClientesInactivos );//SOBREESCRIBE SI EXISTÍA
    fclose( file );

    char linea[ 1024 ];
    char dni[ 20 ];
    file = abrirArchivoLectura( archivoPersonas );

    while( fgets( linea, 1024, file ))
    {
        n = strlen( linea );//ELIMINACIÓN DEL \n
        linea[n-1] = 0;//ELIMINACIÓN DEL \n
        estado = atoi( &linea[n-2] );//OBTIENE EL ÚLTIMO CARACTER

        i=0;
        do
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

        arrayDNIClientes[ j++ ] = atoi( &dni );//CARGA SOLO LOS DNIs PARA VERIFICAR SU EXISTENCIA MÁS RAPIDAMENTE

        printf("%s, ", dni );

        if ( estado == ACTIVO )
        {
            cargarArchivoTemporalClientes( linea, tempClientesActivos );
            //printf(".");
            retorno++;
        }

        if ( estado == INACTIVO )
        {
            cargarArchivoTemporalClientes( linea, tempClientesInactivos );
        }
    }
    fclose( file );
	return retorno;
}




/** CONCATENA LOS ARCHIVOS TEMPORALES DE ACTIVOS E INACTIVOS */
void concatenarClientes()
{
    //printf("\n\tREALIZANDO BACKUP DE LA INFORMACIÓN AGUARDE POR FAVOR....")
    FILE *file = abrirArchivoEscritura( archivoPersonas );
    fclose( file );

    strcpy( linea, "@copy ");
    strcat( linea, tempClientesActivos );
    strcat( linea, "+" );
    strcat( linea, tempClientesInactivos );
    strcat( linea, " " );
    strcat( linea, archivoPersonas );
    strcat( linea, ">nul" );

    system( linea );
    remove( tempClientesActivos );
    remove( tempClientesInactivos );
}
