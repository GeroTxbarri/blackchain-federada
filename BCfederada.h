// filepath: /blockchain-federada/blockchain-federada/src/BCfederada.h
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    int capacidad;
    int indice;
    
} BlockchainFederada;

int siguientePotencia(int n);

Bloque* crearBloque(int id, char* mensaje);

Blockchain* crearBlockchain();

BlockchainFederada* crearBCfederada(int tamano);

void agregarBloque(Blockchain* cadena, int arreglo[],int*cont, char* mensaje);

void agregarAfederacion(BlockchainFederada* federacion,Blockchain* bc);

int* construirArbolValidacion(BlockchainFederada* federada);

void imprimirBlockChain(Blockchain* bc);

void imprimirValidacion(int* arbol, int n);

void actualizarArbolValidacion(int* arbol, int num, int aCambiar, int tam, int* raizAnterior);

void alta(int* arbol,BlockchainFederada* federada, char* mensaje,int arreglo[],int*cont,int numBC, int tam, int* raizAnterior);

void actualizacion(int indice, int id, char* mensaje, int arreglo[],int* cont, BlockchainFederada* federada, int* arbol, int tam, int*raizAnterior);

int validacion(int raizAnterior,int* arbol,int tam,BlockchainFederada* federada);