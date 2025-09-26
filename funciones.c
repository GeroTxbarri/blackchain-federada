#include "funciones.h"

void alta(int* arbol,BlockchainFederada* federada, char* mensaje,int arreglo[],int*cont,int numBC, int tam){
    int id_actual = arreglo[*cont];
    agregarBloque(federada->blockchains[numBC],arreglo,cont,mensaje);
    actualizarArbolValidacion(arbol,id_actual,numBC+1, tam); 
}

void actualizacion(int indice, int id, char* mensaje, int arreglo[],int* cont, BlockchainFederada* federada, int* arbol, int tam){
    if (federada == NULL || federada->blockchains == NULL || indice < 0 || indice >= federada->capacidad) {
        printf("no hay blockchains en federada.\n");
        return;
    }
    Blockchain* cadena = federada->blockchains[indice];
    if (cadena == NULL || cadena->primero == NULL) {
        printf("La blockchain en el índice especificado es nula o vacía.\n");
        return;
    }
    
    Bloque* bloqueAModificar = cadena->primero;
    while(bloqueAModificar != NULL){
        if(bloqueAModificar->id == id)
            break;
        bloqueAModificar = bloqueAModificar->sig;
    }
    if(bloqueAModificar->id != id){
        printf("\nNo se ha encontrado el id %d en la cadena %d\n",id,indice);
        return;
    }
    strcpy(bloqueAModificar->mensaje, mensaje);
    int ultimo_primo=0;
    while(bloqueAModificar!=NULL){
        bloqueAModificar->id = arreglo[*cont];
        ultimo_primo =arreglo[*cont];
        (*cont)++;
        bloqueAModificar = bloqueAModificar->sig;
    }
    actualizarArbolValidacion(arbol,ultimo_primo,indice+1,tam);
}

int validacion(int* arbol,int tam,BlockchainFederada* federada){
    int mult = 1;
    for(int i=1; i<tam; i++){
         mult *= arbol[i];
    }
    if(arbol[0] != mult){
        printf("\nLa raiz esta mal");
        return 0;
    }    
    int cant = (federada->capacidad)-1;
    for(int i=0; i<cant;i++){
        Bloque* bcuno = federada->blockchains[i]->primero;
        Bloque* bcdos = bcuno->sig;
        while(bcdos){
            if(bcuno->id >= bcdos->id){
                printf("\nLos id no corresponden\n");
                return 0;
            }
            bcuno = bcdos;
            bcdos = bcdos->sig;
        }
   }
   printf("\nTodo bien :)");
   return 1;
}


int validacion_subConjuntos(int* arbol, int n,int min,int max){
    int raiz=1;
    for(int i = min+1;i<=max+1;i++){
        raiz *= arbol[i];
    }
    if( raiz != n){
        return 0;
    }
    return 1;
}