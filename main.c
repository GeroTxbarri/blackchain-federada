#include "stdlib.h"
#include "stdio.h"
#include "generador_primos.h"


#include "funciones.h"

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

  agregarBloque(bc0,p,&cont,"BC0 primer bloque");
  agregarBloque(bc0,p,&cont,"segundo bloque");

  agregarBloque(bc1,p,&cont,"BC1 primer bloque");
  agregarBloque(bc1,p,&cont,"segundo bloque");

  agregarBloque(bc2,p,&cont,"BC2 primer bloque");
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

  alta(arbolValidacion,federacion,"cambie juasjuasjuas",p,&cont,1,federacion->capacidad+1);
  imprimirValidacion(arbolValidacion,federacion->capacidad+1);
  printf("\n");
  imprimirBlockChain(bc1);

  actualizacion(1,7,"aeiou",p,&cont,federacion,arbolValidacion,federacion->capacidad+1);
  imprimirBlockChain(bc1);
  imprimirValidacion(arbolValidacion,federacion->capacidad+1);

  //federacion->blockchains[0]->primero->sig->id=20;

  if(validacion(arbolValidacion,federacion->capacidad+1,federacion)){
    printf("\n la federacion es valida");
  }
  else
    printf("\n la federacion no es valida");

  
  if(validacion_subConjuntos(arbolValidacion,8,0,1)){
    printf("\n el subconjunto es valida");
  }
  else
    printf("\n el subconjunto no es valida");
  free(p);
  return 0;
}