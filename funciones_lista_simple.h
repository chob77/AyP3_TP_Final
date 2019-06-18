/*
 * MATERIA: ALGORITMOS Y PROGRAMACIÓN 3
 * UNTREF 2019.
 *
 * TRABAJO PRÁCTICO FINAL INTEGRADOR: SISTEMA DE CRÉDITOS.
 * FILE: funciones_lista_simple.h
 *
 *  CREATED ON: 3 jun. 2019
 *      AUTHOR: chob
 */


/** CREA UN NUEVO ELEMENTO DE LA LISTA */
void inicializarSiguienteNodo( Lista *miLista, int cliente, int amigo )
{
	miLista->siguiente = malloc(sizeof( struct Nodo ));

	if ( miLista->siguiente == NULL ){

		printf( "\nNo hay memoria disponible!\n");
	}
	else
	{
		miLista->siguiente->cliente = cliente;
		miLista->siguiente->amigo = amigo;
		miLista->siguiente->siguiente = NULL;
		//printf("Se agrego elemento: %d\n", valor);
	}
}



/** AGREGA LOS ELEMENTOS A LA LISTA SIMPLE */
void agregarElementoLista( Lista *miLista, int cliente, int amigo )
{
	if ( miLista->cliente == NULL )
	{
		miLista->cliente = cliente;
		miLista->amigo = amigo;
		miLista->siguiente = NULL;
	}
	else
	{
		while( miLista->siguiente != NULL )
		{
			miLista = miLista->siguiente;
		}

		inicializarSiguienteNodo( miLista, cliente, amigo );
	}
}



/** RECORRE LA LISTA MOSTRANDO EL CONTENIDO */
void recorrerLista ( Lista *miLista)
{
	while( miLista != NULL )
	{
		printf( "\n%d %d", miLista->cliente, miLista->amigo);
		miLista = miLista->siguiente;
	}
	printf("\n");
}




/** DEVUELVE EL TAMAÑO DE LA LISTA */
int obtenerTamanioLista ( Lista *miLista )
{
	int tamanioLista = 0;
	while( miLista != NULL )
	{
		tamanioLista++;
		miLista = miLista->siguiente;
	}
	return tamanioLista;
}




void obtenerElementoLista ( Lista *miLista, int elemento)
{
    int i=0;
    int tamanioLista = obtenerTamanioLista( miLista );
    if ( elemento < tamanioLista )
    {
        while( miLista != NULL && miLista->siguiente != NULL  )
        {
            i++;
            if ( i == elemento )
            {
                printf("El valor del elemento %d: es %d\n", elemento, miLista->cliente );

            }
            miLista = miLista->siguiente;
        }
    }

}




void quitarElementoLista ( Lista *miLista, int elemento )
{
    int tamanioLista = obtenerTamanioLista( miLista );
	Lista *elementoAnterior = NULL;
	Lista *miListaTemp = NULL;

    if ( elemento <= tamanioLista )
    {
        while( miLista != NULL && miLista->siguiente != NULL  )
        {
            if ( miLista->cliente != elemento )
            {
				elementoAnterior = miLista;
				miLista = miLista->siguiente;
            }
			else
			{
				printf("\nSe quit%c el elemento: %d\n",162, miLista->cliente );
				elementoAnterior->siguiente = NULL;
				miListaTemp = miLista->siguiente;
				elementoAnterior->siguiente = miListaTemp;
				miLista = elementoAnterior;
				miLista = elementoAnterior->siguiente;
			}
        }
    }
}




void copiarLista( Lista *miLista, Lista *aux )
{
    while( aux != NULL )
    {
        miLista->cliente = aux->cliente;
        aux = aux->siguiente;
        miLista = miLista->siguiente;
    }
}




int compararListas( Lista *miLista, Lista *aux )
{
    int retorno = 0;
	int iguales = 0;
	int tamanioLista = obtenerTamanioLista( miLista );
    int tamanioAux = obtenerTamanioLista( aux );

	if ( tamanioLista >= tamanioAux )
	{
		while( aux != NULL )
		{
			if ( miLista->cliente == aux->cliente )
			{
				iguales++;
			}
			else
			{
				iguales--;
			}
			aux = aux->siguiente;
			miLista = miLista->siguiente;
		}

		if ( iguales == tamanioLista ) retorno = 1;
	}

	return retorno;
}





void inicializarListas( Lista *miLista, Lista *aux, Lista *P1, Lista *P2 )
{
	P2 = miLista;
	P1 = miLista;
	P1 = P1->siguiente;
	aux = &aux_temp;
	aux->siguiente=NULL;

	if ( P1->cliente < P2->cliente )
	{
		aux->cliente = P1->cliente;
		P1 = P1->siguiente;
	}
	else{
		aux->cliente = P2->cliente;
		P2 = P1;
		P1 = P1->siguiente;
	}
}




void ordenarLista ( Lista *miLista )
{
    int tamanioLista = obtenerTamanioLista( miLista );
	tamanioLista *= tamanioLista;
    int ordenado = 0;

    if ( miLista == NULL ) return;

    else if ( tamanioLista == 1 ) return;

    else
        {
            //printf("SE VA A ORDENAR LA LISTA\n");
            Lista *P1 = miLista;
            P1 = P1->siguiente;
            Lista *P2 = miLista;
			int tamanio = 0;

			aux->siguiente=NULL;
			if ( P1->cliente < P2->cliente )
			{
				aux->cliente = P1->cliente;
				P1 = P1->siguiente;
			}
			else{
				aux->cliente = P2->cliente;
				P2 = P1;
				P1 = P1->siguiente;
			}


            while ( ordenado == 0 && tamanio < tamanioLista )
            {
				//printf( "\nBUCLE: %d\n", tamanio );

				if ( P1->cliente < P2->cliente )
                {
                    //printf( "P1->cliente=%d < P2->cliente=%d\n", P1->cliente, P2->cliente );
                    agregarElementoLista( aux, P1->cliente, P1->amigo );

					if ( P1->siguiente != NULL ) {
						P1 = P1->siguiente;
					}
					else
					{
						agregarElementoLista( aux, P2->cliente, P2->amigo );//DETECTÓ FIN DE LISTA
						ordenado = compararListas( miLista, aux );

						copiarLista( miLista, aux );
						//inicializarListas( miLista, aux, P1, P2 );

						P2 = miLista;
						P1 = miLista;
						P1 = P1->siguiente;
						aux = &aux_temp;
						aux->siguiente=NULL;

						if ( P1->cliente < P2->cliente )
						{
							aux->cliente = P1->cliente;
							P1 = P1->siguiente;
						}
						else{
							aux->cliente = P2->cliente;
							P2 = P1;
							P1 = P1->siguiente;
						}
					}
                }
                else if ( P1->cliente > P2->cliente )
                {
                    //printf( "P1->cliente=%d > P2->cliente=%d\n", P1->cliente, P2->cliente );
                    agregarElementoLista( aux, P2->cliente, P2->amigo );
                    P2 = P1;


                    if ( P1->siguiente != NULL ) {
						P1 = P1->siguiente;
					}
					else
					{
						agregarElementoLista( aux, P1->cliente, P2->amigo );//DETECTÓ FIN DE LISTA
                        ordenado = compararListas( miLista, aux );

						copiarLista( miLista, aux );
						//inicializarListas( miLista, aux, P1, P2 );

						P2 = miLista;
						P1 = miLista;
						P1 = P1->siguiente;
						aux = &aux_temp;
						aux->siguiente=NULL;

						if ( P1->cliente < P2->cliente )
						{
							aux->cliente = P1->cliente;
							P1 = P1->siguiente;
						}
						else{
							aux->cliente = P2->cliente;
							P2 = P1;
							P1 = P1->siguiente;
						}
					}
                }
				else //LOS ELEMENTOS SON IGUALES
				{
					//printf( "P1->cliente=%d == P2->cliente=%d\n", P1->cliente, P2->cliente );
                    agregarElementoLista( aux, P1->cliente, P2->amigo );

                    if ( P1->siguiente != NULL ) {
						P1 = P1->siguiente;
					}
					else
					{
						agregarElementoLista( aux, P1->cliente, P2->amigo );//DETECTÓ FIN DE LISTA
                        ordenado = compararListas( miLista, aux );

						copiarLista( miLista, aux );
						//inicializarListas( miLista, aux, P1, P2 );

						P2 = miLista;
						P1 = miLista;
						P1 = P1->siguiente;
						aux = &aux_temp;
						aux->siguiente=NULL;

						if ( P1->cliente < P2->cliente )
						{
							aux->cliente = P1->cliente;
							P1 = P1->siguiente;
						}
						else{
							aux->cliente = P2->cliente;
							P2 = P1;
							P1 = P1->siguiente;
						}
					}
				}

                /*recorrerLista( miLista );
                printf( "aux: " );
                recorrerLista( aux );*/
				tamanio++;
            }
        }

		/*printf("\nLISTA ORDENADA: " );
		recorrerLista( miLista );*/
}
