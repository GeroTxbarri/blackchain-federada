
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
    (*cont)++;


}

void agregarAfederacion(BlockchainFederada* federacion,Blockchain*  bc){
    federacion->blockchains[federacion->indice] = bc;
    federacion->indice++;
}

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


void actualizarArbolValidacion(int* arbol, int num, int aCambiar){
    arbol[aCambiar] = num;
    int raiz = 1;
    int tam = sizeof(arbol)/sizeof arbol[0];
    while(tam > 0){
        raiz *= arbol[aCambiar];
        tam--;
    }
    arbol[0] = raiz;
}

void alta(int* arbol,BlockchainFederada* federada, char* mensaje,int arreglo[],int*cont,int numBC){
    agregarBloque(federada->blockchains[numBC],arreglo,cont,mensaje);
    actualizarArbolValidacion(arbol,arreglo[*cont],numBC); 
}