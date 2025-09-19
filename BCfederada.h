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
    Blockchain *blockchains;
    int cantidad;
} BlockchainFederada;

Bloque* crearBloque(int id, char* mensaje);
Bloque* agregarBloque(Bloque* bc, int id, char* mensaje);
void imprimirBC(Bloque* bc);
