// filepath: /blockchain-federada/blockchain-federada/src/BCfederada.h
#include <stdlib.h>
#include <stdio.h>

typedef struct _Bloque {
    int id;
    char mensaje[100];
    struct _Bloque *sig;
    struct _Bloque *ant;
} Bloque;

typedef struct _Blockchain {
    Bloque *primero;
    Bloque *ultimo;

} Blockchain;

typedef struct _BlockchainFederada {
    Blockchain** blockchains;
    int cantidad;
    
} BlockchainFederada;

int siguientePotencia(int n);

Bloque* crearBloque(int id, char* mensaje);

Blockchain* crearBlockchain();

void agregarBloque(Blockchain* cadena, int arreglo[],int*cont, char* mensaje);

int* construirArbolValidacion(BlockchainFederada* federada);


void imprimirBC(Bloque* bc);
