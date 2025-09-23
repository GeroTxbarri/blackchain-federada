#include "stdlib.h"
#include "stdio.h"
#include "generador_primos.h"
#include "BCfederada.h"

int main() {
  // Genero y muestro los primeros 100 números primos
  int *p = primos(100);
  //for(int i = 0; i < 100; i++)
    //printf("%d ",p[i]);

  // Uso los números primos

  // IMPORTANTE: libero la memoria pedida para el arreglo de números primos

  int cont = 0;

  Blockchain* bc0 = crearBlockchain();
  Blockchain* bc1 = crearBlockchain();
  Blockchain* bc2 = crearBlockchain();

  agregarBloque(bc0,p,&cont,"primer bloque");
  agregarBloque(bc0,p,&cont,"segundo bloque");

  agregarBloque(bc1,p,&cont,"primer bloque");
  agregarBloque(bc1,p,&cont,"segundo bloque");

  agregarBloque(bc2,p,&cont,"primer bloque");
  agregarBloque(bc2,p,&cont,"segundo bloque");

  agregarBloque(bc0,p,&cont,"ultimo bloque");
  agregarBloque(bc1,p,&cont,"ultimo bloque");
  agregarBloque(bc2,p,&cont,"ultimo bloque");
  
  BlockchainFederada* federacion= crearBCfederada(3);

  agregarAfederacion(federacion,bc0);
  agregarAfederacion(federacion,bc1);
  agregarAfederacion(federacion,bc2);

  imprimirBlockChain(bc0);
  imprimirBlockChain(bc1);
  imprimirBlockChain(bc2);

  int* arbolValidacion = construirArbolValidacion(federacion);
  printf("\narbol de validacion : ");
  for(int i = 0; i<6;i++){
    printf(" %d,",arbolValidacion[i]);
  }

  free(p);
  return 0;
}