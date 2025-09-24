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
  int raizAnterior = 0;

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
  
  imprimirValidacion(arbolValidacion,federacion->capacidad+1);
  alta(arbolValidacion,federacion,"cambie juasjuasjuas",p,&cont,2,federacion->capacidad+1,&raizAnterior);
  imprimirValidacion(arbolValidacion,federacion->capacidad+1);

  imprimirBlockChain(bc1);
  actualizacion(1,7,"aeiou",p,&cont,federacion,arbolValidacion,federacion->capacidad+1,&raizAnterior);
  imprimirBlockChain(bc1);
  validacion(raizAnterior,arbolValidacion,federacion->capacidad+1,federacion);
  free(p);
  return 0;
}