
#include "arbolValidacion.h"


void alta(int* arbol,BlockchainFederada* federada, char* mensaje,int arreglo[],int*cont,int numBC, int tam);

void actualizacion(int indice, int id, char* mensaje, int arreglo[],int* cont, BlockchainFederada* federada, int* arbol, int tam);

int validacion(int* arbol,int tam,BlockchainFederada* federada);

int validacion_subConjuntos(int* arbol, int n,int min,int max);