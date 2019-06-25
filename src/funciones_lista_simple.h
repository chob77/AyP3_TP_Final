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
	}
}



/** CREA UN NUEVO ELEMENTO DE LA LISTA */
void inicializarSiguienteNodoCredito( ListaCreditosClientes *miLista, int cliente, Credito credito )
{
	miLista->siguiente = malloc(sizeof( struct NodoCredito ));

	if ( miLista->siguiente == NULL ){

		printf( "\nNo hay memoria disponible!\n");
	}
	else
	{
		miLista->siguiente->dniCliente = cliente;
		miLista->siguiente->credito = credito;
		miLista->siguiente->siguiente = NULL;
	}
}



/** CREA UN NUEVO ELEMENTO DE LA LISTA */
void inicializarSiguienteNodoLineaClienteArchivo( ListaClienteLineaArchivo *miLista, int cliente, int linea )
{
	miLista->siguiente = malloc(sizeof( struct NodoArchivo ));

	if ( miLista->siguiente == NULL ){

		printf( "\nNo hay memoria disponible!\n");
	}
	else
	{
		miLista->siguiente->dniCliente = cliente;
		miLista->siguiente->linea = linea;
		miLista->siguiente->siguiente = NULL;
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



/** AGREGA LOS ELEMENTOS A LA LISTA SIMPLE */
void agregarElementoListaCredito( ListaCreditosClientes *miLista, int cliente, Credito credito )
{
	if ( miLista->dniCliente == NULL )
	{
		miLista->dniCliente = cliente;
		miLista->credito = credito;
		miLista->siguiente = NULL;
	}
	else
	{
		while( miLista->siguiente != NULL )
		{
			miLista = miLista->siguiente;
		}

		inicializarSiguienteNodoCredito( miLista, cliente, credito );
	}
}



/** AGREGA LOS ELEMENTOS A LA LISTA SIMPLE */
void agregarElementoListaLineaClienteArchivo( ListaClienteLineaArchivo *miLista, int cliente, int linea )
{
	if ( miLista->dniCliente == NULL )
	{
		miLista->dniCliente = cliente;
		miLista->linea = linea;
		miLista->siguiente = NULL;
	}
	else
	{
		while( miLista->siguiente != NULL )
		{
			miLista = miLista->siguiente;
		}

		inicializarSiguienteNodoLineaClienteArchivo( miLista, cliente, linea );
	}
}



/** RECORRE LA LISTA MOSTRANDO EL CONTENIDO */
void recorrerLista ( Lista *miLista)
{
	printf( "\nCONTENIDO DE LA LISTA:");

	while( miLista != NULL )
	{
		printf( "\nCliente %d Amigo %d", miLista->cliente, miLista->amigo);
		miLista = miLista->siguiente;
	}
	printf("\n");
}



/** RECORRE LA LISTA MOSTRANDO EL CONTENIDO */
void listarCreditos ( ListaCreditosClientes *miLista )
{

PaginarCreditos:
	countInOrder = 0;
	clrscr();
	printf( "\n\nCR%cDITOS ACTIVOS EXISTENTES\n", acento_E );

/* CRÉDITOS: ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO */

	printf("\n\t------------------------------------------------------------------------------------------");
	printf( "\n\tCR%cDITO\tCLIENTE\tFECHA\t\tMONTO\t   MONEDA    CUOTAS\tSALDO\t\tCUOTA", acento_E );
	printf("\n\t------------------------------------------------------------------------------------------");

	while( miLista != NULL )
	{
		if ( miLista->credito.estado==ACTIVO )
		{
			printf( "\n\t%d\t%d\t%s   $%10.2f  %7s      %-3d   $%10.2f   $%10.2f",
								miLista->credito.idCredito, miLista->dniCliente,
								&miLista->credito.fechalta, miLista->credito.monto, (miLista->credito.moneda==0?"PESOS":"DOLARES"),
								miLista->credito.cuotas, miLista->credito.saldo, ( miLista->credito.saldo/miLista->credito.cuotas) );
			printf("\n\t------------------------------------------------------------------------------------------");
			countInOrder++;
		}
		miLista = miLista->siguiente;
		if ( countInOrder == 17 ) { printf("\ncontin%ca.... ", acento_u ); pause(); goto PaginarCreditos; }
	}
}



/** RECORRE LA LISTA MOSTRANDO EL CONTENIDO */
int listarCreditosDNI ( ListaCreditosClientes *miLista, int dni )
{
	ListaCreditosClientes * aux = miLista;

	printf("\nEL CLIENTE POSEE LOS SIGUIENTES CR%cDITOS PENDIENTES:\n", acento_E );

/* CRÉDITOS: ID;DNI;ESTADO;FECHALTA;MONTO;MONEDA;CUOTAS;SALDO */

	printf("\n\t------------------------------------------------------------------------------------------");
	printf( "\n\tCR%cDITO\tCLIENTE\tFECHA\t\tMONTO\t   MONEDA    CUOTAS\tSALDO\t\tCUOTA", acento_E );
	printf("\n\t------------------------------------------------------------------------------------------");

	countInOrder = 0;
	double pagosRealizados = 0;

	double deuda = 0;
	while( aux != NULL )
	{
		if ( aux->dniCliente == dni )
		{
			if ( aux->credito.estado==ACTIVO )
			{
				printf( "\n\t%d\t%d\t%s   $%10.2f    %7s    %-3d   $%10.2f   $%10.2f",
					aux->credito.idCredito, aux->dniCliente,
					&aux->credito.fechalta, aux->credito.monto, (aux->credito.moneda==0?"PESOS":"DOLARES"),
					aux->credito.cuotas, aux->credito.saldo, ( aux->credito.saldo/aux->credito.cuotas) );

				printf("\n\t------------------------------------------------------------------------------------------");
				deuda += aux->credito.saldo;

				if ( isInArrayCreditosPagos( arrayCreditoPagos, aux->credito.idCredito ) )		//SI POSEE PAGOS REGISTRADOS LOS LISTO
				{
					printf("\n\nPAGOS ASOCIADOS AL CR%cDITO: ", acento_E );
					mostrarListaPagosCliente( aux->credito.idCredito );
				}
				else
				{
					printf( "\nEL CREDITO %d NO POSEE PAGOS ASOCIADOS.", aux->credito.idCredito );
				}

				if ( pagosRealizados > 0 )
				{
					printf("\n\t\t-----------------------------------------");
					printf("\nTOTAL DE PAGOS REALIZADOS: \t$%10.2f\n", pagosRealizados );
					pagosRealizados = 0;
				}

				countInOrder++;
			}
		}
		aux = aux->siguiente;
	}

	return countInOrder;
}



/** DEVUELVE EL ID DE UN CRÉDITO */
int obtenerIDCreditoCliente( ListaCreditosClientes *miLista, int dni )
{
	int idCredito = 0;
	while( miLista != NULL )
	{
		if ( miLista->dniCliente == dni )
		{
			idCredito = miLista->credito.idCredito;
		}
		miLista = miLista->siguiente;
	}

	return idCredito;
}



/** DEVUELVE LA DIRECCIÓN DE UN CRÉDITO */
Credito *obtenerDireccionCredito( ListaCreditosClientes *miLista, int idCredito )
{
	Credito *credito;

	while( miLista != NULL )
	{
		if ( miLista->credito.idCredito == idCredito )
		{
			credito = &miLista->credito;
		}
		miLista = miLista->siguiente;
	}

	return credito;
}



/** RECORRE LA LISTA MOSTRANDO EL CONTENIDO */
void recorrerListaLineaArchivo ( ListaClienteLineaArchivo *miLista )
{
	printf( "\nCONTENIDO DE LA LISTA:");

	while( miLista != NULL )
	{
		printf( "\nCliente %d L%cnea %d", miLista->dniCliente, acento_i, miLista->linea);
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



/** DEVUELVE EL TAMAÑO DE LA LISTA */
int obtenerTamanioListaCredito ( ListaCreditosClientes *miLista )
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



/** VERIFICA SI UN CRÉDITO POSEE PAGOS */
int isInArrayCreditosPagos( ArrayCreditos *arrayCred, int idCredito )
{
	ArrayCreditos *aux = arrayCred;
	int retorno = FALSE;

	while( aux != NULL )
	{
		if ( aux->idCredito == idCredito ) retorno = TRUE;
		aux = aux->siguiente;
	}

    return retorno;
}



ListaPagoCliente *obtenerNodoLista( int idCredito )
{
	ListaPagoCliente *aux = listaPagoCliente;

	while( aux->siguiente != NULL )
	{
		if ( aux->idCredito == idCredito ) return aux;
		aux = aux->siguiente;
	}

	return aux;
}



SubListaPagos *agregrarSubLista( SubListaPagos *pagos, Pago pago )
{
	SubListaPagos *nodo = ( SubListaPagos * ) malloc( sizeof( struct nodoSubPagos ));
	nodo->pago = pago;
	nodo->siguiente = NULL;

	if ( pagos == NULL )
	{
		return nodo;
	}

	SubListaPagos *ultimoPago = pagos;

	while( ultimoPago->siguiente != NULL )
	{
		ultimoPago = ultimoPago->siguiente;
	}

	ultimoPago->siguiente = nodo;
	return pagos;
}



/** VINCULA CLIENTES Y SUS PAGOS */
ListaPagoCliente *agregarPagoCredito( int id_credito )
{
	ListaPagoCliente *nodo = ( ListaPagoCliente * ) malloc( sizeof( struct NodoPago ));
	nodo->idCredito = id_credito;
	nodo->pagos = NULL;
	nodo->siguiente = NULL;

	if ( listaPagoCliente == NULL )
	{
		return nodo;
	}

	ListaPagoCliente *ultimoNodo = listaPagoCliente;

	while( ultimoNodo->siguiente != NULL  )
	{
		ultimoNodo = ultimoNodo->siguiente;
	}

	ultimoNodo->siguiente = nodo;
	return listaPagoCliente;

}



/** AGREGA UN NODO AL A LISTA ENLAZADA DE CRÉDITOS CON PAGOS ASOCIADOS */
ArrayCreditos *agregraArrayCreditoPagos( int id_credito )
{
	ArrayCreditos *nodo = ( ArrayCreditos * ) malloc( sizeof( struct arrayCredito ));
	nodo->idCredito = id_credito;
	nodo->siguiente = NULL;


	if ( arrayCreditoPagos == NULL )
	{
		return nodo;
	}

	ArrayCreditos *ultimoNodo = arrayCreditoPagos;

	while( ultimoNodo->siguiente != NULL  )
	{
		ultimoNodo = ultimoNodo->siguiente;
	}

	ultimoNodo->siguiente = nodo;
	return arrayCreditoPagos;
}



/** MUESTRA LOS PAGOS ASOCIADOS A UN CRÉDITO */
void mostrarListaPagosCliente( int idCredito )
{
	ListaPagoCliente *ultimoNodo = listaPagoCliente;

	while( ultimoNodo != NULL  )
	{
		if ( ultimoNodo->idCredito == idCredito )
		{
			printf(" %d:", ultimoNodo->idCredito );

			SubListaPagos * subaux = ultimoNodo->pagos;
			while( subaux != NULL )
			{
				printf("\n\tPAGO: %d - FECHA: %s - MONTO: %.2f", subaux->pago.idPago, subaux->pago.fechalta, subaux->pago.monto );
				subaux = subaux->siguiente;
			}
			printf("\n");
		}
		ultimoNodo = ultimoNodo->siguiente;
	}

}



void mostrarArrayCreditoPagos()
{
	ArrayCreditos *ultimoNodo = arrayCreditoPagos;

	printf("\nCONTENIDO DE LA LISTA: arrayCreditoPagos: ");
	while( ultimoNodo != NULL  )
	{
		printf("%d, ", ultimoNodo->idCredito );
		ultimoNodo = ultimoNodo->siguiente;
	}

	printf("\n");
}
