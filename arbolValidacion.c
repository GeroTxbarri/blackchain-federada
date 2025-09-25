#include "arbolValidacion.h"

int* construirArbolValidacion(BlockchainFederada* federada) {

    int cantidad = federada->capacidad;
    int cantidadHojas = siguientePotencia(cantidad);
    
    int* arregloArbol = (int*)malloc((cantidadHojas + 1) * sizeof(int));
   
    int valorRaiz = 1;
    for (int i = 0; i < cantidadHojas; i++) {
        int valorHoja;
        
        if (i < cantidad) {

            if (federada->blockchains[i] != NULL && federada->blockchains[i]->ultimo!= NULL) {
                valorHoja = federada->blockchains[i]->ultimo->id;
            } else {
                valorHoja = 1;
            }
        } else {
    
            valorHoja = 1;
        }
        
        arregloArbol[i + 1] = valorHoja;
        valorRaiz *= valorHoja;      
    }
    
    arregloArbol[0] = valorRaiz;

    return arregloArbol;
}

void imprimirValidacion(int* arbol, int n){
    printf("arbol de validacion : ");
    for(int i = 0; i<n; i++)
        printf(" %d,",arbol[i]);
    printf("\n");

}

void actualizarArbolValidacion(int* arbol, int id, int aCambiar, int tam){
    arbol[aCambiar] = id;
    int raiz=1;
    for(int i=1; i<tam; i++)
        raiz = raiz * arbol[i];
    arbol[0] = raiz;
}
