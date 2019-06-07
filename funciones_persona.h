/*
 * funciones_personas.h
 *
 *  Created on: 27 abr. 2019
 *      Author: chob
 */

#include <stdlib.h>
#include <string.h>


Persona inicializarPersona();
Persona ingresarDatosPersona( int indice );
Persona cargarPersonaEnPosicion();

int existenPersonasAlmacenadas();
int obtenerTotalPersonas( Persona *plistaPersonas );
void parcerarLineaArchivo( char *linea, Persona *listaPersonas, int pos_persona );
void parcerarLineaArchivoPorAmigo( char *linea, Persona *listaPersonas, int pos_persona );


int existenPersonasAlmacenadas()
{
	int retorno = 0;
	FILE *file = abrirArchivoLectura( archivoPersonas );
	if  ( file ) retorno = 1;

	return retorno;
}



int obtenerTotalPersonas( Persona *listaPersonas )
{
	int retorno = 0;
	int i;
	for ( i=0; i<=9; i++)
	{
		if ( (*listaPersonas).dni != NULL ) retorno++;
		listaPersonas++;
	}

	return retorno;
}


void mostrar_menu_ingresos()
{
    printf("\nELIJA UNA OPCION");
    printf("\n\t1.INGRESAR LISTA PERSONAS CORRELATIVOS (10 en total)");
    printf("\n\t2.INGRESAR PERSONA EN UNA UBICACION (sobre 10 posibles)");

    if ( obtenerTotalPersonas( plistaPersonas ) > 0 )
	{
		printf("\n\t3.VER NOMINA DE PERSONAS");
		printf("\n\t4.BUSCAR PERSONA POR DNI");
		printf("\n\t5.BUSCAR PERSONA POR NOMBRE");
		printf("\n\t6.ASIGNAR AMIGO");
		printf("\n\t7.ALMACENAR INFORMACI%cN INGRESADA", acento_O );
	}

    if ( existenPersonasAlmacenadas() == 1 ) printf("\n\t8.CARGAR PERSONAS ALMACENADAS");
    printf("\n\t0.SALIR");
}



void menuElegido( int valor )
{
    printf("\nSe escogio la opcion: %d\n", valor);
}




void cargarDiezPersonas( Persona *listaPersonas )
{
	int opcion=1;
	int i=0;
	Persona persona_temp;

	do {
        persona_temp = ingresarDatosPersona( i+1 );
	    if( persona_temp.dni == 0 )
        {
            opcion = 0; //SI EL DNI ES CERO SALE
			i++;
        }
	    else
        {
            (*listaPersonas) = persona_temp;
            listaPersonas++;
			i++;
        }
    } while( opcion !=0 && i < 10 );

	if ( i == 10 ) i++;
	clrscr();
	printf("\nFINALIZO LA CARGA DE PERSONAS. SE CARGARON %d PERSONA/S\n", --i);
}




Persona ingresarDatosPersona( int indice )
{
	clrscr();
	Persona persona = inicializarPersona();

	printf("\nINGRESO DE PERSONAS (%02d de 10)", indice);
	printf("\n---------------------------------");
	printf("\nIngrese el dni (cero para finalizar): ");
    scanf("%d", &persona.dni );

    if( persona.dni == 0 ){//SI EL DNI ES CERO SALE
		return persona;
    }else{
		printf("Ingrese nombre y apellido: " );
		scanf("%s %s", persona.nombre, persona.apellido );
    }
    return persona;
}




Persona cargarPersonaEnPosicion()
{
	Persona persona = inicializarPersona();

	printf("\nIngrese el dni: ");
    scanf("%d", &persona.dni );
	printf("Ingrese nombre y apellido: " );
	scanf("%s %s", persona.nombre, persona.apellido );

	return persona;
}




void mostrarListaPersonas( Persona *listaPersonas )
{
	int i = 0;
	clrscr();
	printf("\nNOMINA DE PERSONAS");
	printf("\n-------------------------");
	printf("\n##\tDNI   \tNombre\tApellido\tAmigo" );
	for ( i=0; i<=9; i++)
	{
		printf("\n%02d\t%d\t%s\t%s", i+1, (*listaPersonas).dni, (*listaPersonas).nombre, (*listaPersonas).apellido );

		if ( (*listaPersonas).amigo != NULL )
        {
            printf("\t\t%s", (*listaPersonas).amigo->nombre );
        }
		else
        {
            printf("\t\t----" );
        }

		listaPersonas++;
	}

	printf("\nLista Completa\n");
}



/**
	DEVUELVE UN STRUCT VACÍO
*/
Persona inicializarPersona()
{
	Persona persona;
	persona.dni = 0;
	strcpy( persona.nombre, "-----" );
    strcpy( persona.apellido, "-----" );
    persona.amigo = NULL;
    return persona;
}



int seleccionarUbicacion(){

	int ubicacion;
	do{
		printf("\nElija la ubicacion a ingresar entre 1 y 10");
		printf("\nIngrese un numero entre 1 y 10: ");
		scanf("%d", &ubicacion );
	} while ( ubicacion <=1 && ubicacion >= 10);

    return --ubicacion;

}



void buscarPersonaDNI( Persona *listaPersonas )
{
	int dni=0;
	clrscr();
	printf("BUSCAR PERSONA POR DNI ");
	printf("\nIngrese el dni a buscar: ");
    scanf("%d", &dni );
    int i=0;

    do
    {
        if( (*listaPersonas).dni == dni )
    	{
    		printf("\nDNI HALLADO:");
    		printf("\n-------------------------");
    		printf("\nLegajo\tNombre\tapellido" );
    		printf("\n%d\t%s\t%s\n", (*listaPersonas).dni, (*listaPersonas).nombre, (*listaPersonas).apellido );

    		i=10;
    	}
    	i++;
        listaPersonas++;
    } while( i < 10 );

    if ( i == 10) printf("\nDNI NO HALLADO.\n");
}




void buscarPersonaNombre( Persona *listaPersonas )
{
	char nombre[20];
	clrscr();
	printf("BUSCAR PERSONA POR NOMBRE");
	printf("\nIngrese el nombre a buscar: ");
    scanf("%s", nombre );
    int i=0;

    do
    {
    	if( strncmp( (*listaPersonas).nombre, nombre, 20 ) == 0 )
    	{
    		printf("\nNOMBRE HALLADO:");
    		printf("\n-------------------------");
    		printf("\nLegajo\tNombre\tapellido" );
    		printf("\n%d\t%s\t%s\n", (*listaPersonas).dni, (*listaPersonas).nombre, (*listaPersonas).apellido );

    		i=10;
    	}
    	i++;
        listaPersonas++;
    } while( i < 10 );

    if ( i == 10) printf("\nNOMBRE NO HALLADO.\n");
}




int seleccionarPersona()
{
    int nroPersona=0;
    printf("\nIngrese el numero de la persona (1-10): ");
    scanf("%d", &nroPersona );
    return --nroPersona;
}



void asignarAmigoPersona( Persona *listaPersonas  )
{
    clrscr();
    printf("ASIGNAR AMIGO A PERSONA");
    printf("\n-------------------------");
    mostrarListaPersonas( listaPersonas );

    printf("\nSELECCIONE LA PERSONA A ASIGNARLE UN AMIGO");
    int nroPersonaAAsignarleAmigo;
    nroPersonaAAsignarleAmigo = seleccionarPersona();

    mostrarListaPersonas( listaPersonas );

    printf("\nSELECCIONE UN AMIGO PARA LA PERSONA: %d", (nroPersonaAAsignarleAmigo+1) );
    int nroPersonaAmigo;
    nroPersonaAmigo = seleccionarPersona();

    Persona *persona;
    persona = listaPersonas + nroPersonaAAsignarleAmigo;
    Persona *amigo;
    amigo = listaPersonas + nroPersonaAmigo;

    persona->amigo = amigo;

    printf("\nLa persona es: %s --> su amigo es: %s\n", (*persona).nombre, (*amigo).nombre );
}




void almacenarPersonas( Persona *listaPersonas )
{
	int i;
	char *linea;
	FILE *file = abrirArchivoEscritura( archivoPersonas );

	if ( file != NULL )
	{
		//fprintf( file, "ID;DNI;NOMBRE;APELLIDO;AMIGO\n" );
		for ( i=0; i<=9; i++)
		{
			if ( (*listaPersonas).dni != NULL )
			{
				// fprintf( file, "%02d;%d;%s;%s", i+1, (*listaPersonas).dni, (*listaPersonas).nombre, (*listaPersonas).apellido );
				fprintf( file, "%d;%s;%s", (*listaPersonas).dni, (*listaPersonas).nombre, (*listaPersonas).apellido );

				if ( (*listaPersonas).amigo != NULL )
				{
					fprintf( file,";%s\n", (*listaPersonas).amigo->nombre );
				}
				else
				{
					fprintf( file,";----\n" );
				}
			}

			listaPersonas++;
		}

		clrscr();
		printf("\n\tLA INFORMACI%cN SE ALMACEN%c CORRECTAMENTE.\n", acento_O, acento_O );
	}
	else
	{
		printf("\nERROR AL ABRBIR EL ARCHIVO!!\n");
	}
	fclose( file );
}




void verificarAmigos( Persona *listaPersonas )
{
	FILE *file = abrirArchivoLectura( archivoPersonas );

	// printf("\nVERIFICACI%cN DE AMIGOS\n", acento_O );

	if ( file != NULL )
	{
		int totalLineas = obtenerTotalLineasArchivo( file );
		file = abrirArchivoLectura( archivoPersonas );
		int pos_persona = 0;

		if ( totalLineas > 0 )
		{
			char linea[1024];
			char c;
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
			printf("\nEL ARCHIVO DE PERSONAS EST%c VAC%cO.\n", acento_A, acento_I );
		}

	}
}




void recuperarPersonas( Persona *listaPersonas )
{
	clrscr();
    printf("LEER ALMACEN DE PERSONAS\n");
    printf("-------------------------\n");

	FILE *file = abrirArchivoLectura( archivoPersonas );

	if ( file != NULL )
	{
		int totalLineas = obtenerTotalLineasArchivo( file );
		file = abrirArchivoLectura( archivoPersonas );
		int pos_persona = 0;

		if ( totalLineas > 0 )
		{
			char linea[1024];
			char c;
			while(fgets(linea, 1024, file))
			{
				int n = strlen( linea );//ELIMINACIÓN DEL \n
				linea[n-1] = 0;
				parcerarLineaArchivo( linea, listaPersonas, pos_persona );
				pos_persona++;
			}
			fclose( file );
			if ( pos_persona > 9 ) pos_persona=0;
		}
		else
		{
			printf("\nEL ARCHIVO DE PERSONAS EST%c VAC%cO.\n", acento_A, acento_I );
		}

	}
	else
	{
		printf("\nEL ARCHIVO NO SE PUDO ABRIR.\n");
	}

	verificarAmigos( listaPersonas );
}




void parcerarLineaArchivo( char linea[1024], Persona *listaPersonas, int pos_persona )
{
	//printf("\nL%cnea obtenida: %s\n", acento_i, linea );
	int ln = strlen( linea );
	int cuentaDato = 0;
	char dato[ 100 ];
	char caracter;
	int i, j=0;
	//1-DNI
	//2-NOMBRE
	//3-APELLIDO
	//4-AMIGO

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
			//printf ("CUENTADATO:%d. ", cuentaDato );

			switch ( cuentaDato )
			{
				// case 1: printf("EL DNI es: %s\n", dato); persona.dni = atoi( dato );  break;
				case 1: persona.dni = atoi( dato );  break;
				// case 2: printf("EL NOMBRE es: %s\n", dato); strcpy( persona.nombre, dato ); break;
				case 2: strcpy( persona.nombre, dato ); break;
				// case 3: printf("EL APELLIDO es: %s\n", dato); strcpy( persona.apellido, dato ); break;
				case 3: strcpy( persona.apellido, dato ); break;
				// case 4: printf("EL AMIGO es: %s\n", dato ); break;
				case 4: listaPersonas[ pos_persona ] = persona; cuentaDato = 0; break;
			}
			strcpy( dato, "" );
		}

		/*if ( cuentaDato == 4 ) {
			// printf("%02d, %d\t%s\t%s\t%s\n", pos_persona, persona.dni, persona.nombre, persona.apellido, persona.amigo );
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
    		// printf("\nAMIGO HALLADO:");
    		// printf("-------------------------\n");
    		// printf("\nLegajo\tNombre\tapellido" );
    		// printf("\n%d\t%s\t%s\n", (*listaPersonas).dni, (*listaPersonas).nombre, (*listaPersonas).apellido );
			// retorno = listaPersonas;
			retorno++;

    		i=10;
    	}
    	i++;
        listaPersonas++;
    } while( i < 10 );

    if ( i == 10) printf("\nNOMBRE NO HALLADO.\n");
	
	return retorno;
}



void parcerarLineaArchivoPorAmigo( char linea[1024], Persona *listaPersonas, int pos_persona )
{
	//printf("\nL%cnea obtenida: %s\n", acento_i, linea );
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
			//printf ("CUENTADATO:%d. ", cuentaDato );

			switch ( cuentaDato )
			{
				// case 1: persona.dni = atoi( dato );  break;
				// case 2: strcpy( persona.nombre, dato ); break;
				// case 3: strcpy( persona.apellido, dato ); break;
				case 4:
					a = strcmp( "----", dato );
					persona = listaPersonas + pos_persona;
					// printf("EL AMIGO de %s es: %s (%d) \n", persona->nombre, dato, a );
					if ( a != 0 )
					{
						amigo = listaPersonas + buscarAmigoNombre( listaPersonas, dato );
						// printf("%02d, %d\t%s\t%s\t%s\n", pos_persona, amigo->dni, amigo->nombre, amigo->apellido, amigo->amigo );
						persona->amigo = amigo;
						cuentaDato = 0;
					}

					break;
			}
			strcpy( dato, "" );
		}
	}
}