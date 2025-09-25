
#include "BCfederada.h"

int siguientePotencia(int n) {
    if (n <= 1) return 1;
    int potenciaDOS = 1;
    while (potenciaDOS < n) {
        potenciaDOS *= 2;
    }
    return potenciaDOS;
}

Bloque* crearBloque(int id, char* mensaje){
    Bloque* b = malloc(sizeof(Bloque));
    b->id = id;
    strcpy(b->mensaje, mensaje);
    b->ant = NULL;
    b->sig = NULL;
    return b;
}
Blockchain* crearBlockchain(){
    Blockchain* bc = (Blockchain*)malloc(sizeof(Blockchain));
    bc ->primero=NULL;
    bc ->ultimo =NULL;
    return bc;
}

BlockchainFederada* crearBCfederada(int capacidad){
    BlockchainFederada* federada = (BlockchainFederada*)malloc(sizeof(BlockchainFederada));
    if (federada == NULL) return NULL;
    
    federada->blockchains = (Blockchain**)malloc(capacidad * sizeof(Blockchain*));
    if (federada->blockchains == NULL) {
        free(federada);
        return NULL;
    }
    federada->capacidad = capacidad;
    federada->indice =0;

    return federada;
}

void agregarBloque(Blockchain* cadena, int arreglo[],int*cont, char* mensaje){
    Bloque* nuevo = crearBloque(arreglo[*cont], mensaje);
    (*cont)++;
    if (cadena == NULL) {
        return ;
    }
    if(cadena->primero==NULL){
        cadena->primero=nuevo;
        cadena->ultimo =nuevo;
    }
    else{
        nuevo->ant =cadena->ultimo;
        cadena->ultimo->sig= nuevo;
        cadena->ultimo=nuevo;
    }
}

void agregarAfederacion(BlockchainFederada* federacion,Blockchain*  bc){
    federacion->blockchains[federacion->indice] = bc;
    federacion->indice++;
}


void imprimirBlockChain(Blockchain* bc){
    
    if(bc==NULL||bc->primero==NULL){
        printf("cadena vacia\n");
        return;
    }
    Bloque* actual = bc->primero;
    while(actual!=NULL){
        printf("id : %d ; mensaje: %s ",actual->id,actual->mensaje);
        if(actual->sig != NULL){
            printf(" --> ");
        }
        actual = actual->sig;

    }
    printf("\n");
}



