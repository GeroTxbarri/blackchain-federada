
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

void imprimirValidacion(int* arbol, int n){
    printf("arbol de validacion : ");
    for(int i = 0; i<n; i++)
        printf(" %d,",arbol[i]);
    printf("\n");

}

void actualizarArbolValidacion(int* arbol, int id, int aCambiar, int tam, int* raizAnterior){
    *raizAnterior = arbol[0];
    arbol[aCambiar] = id;
    int raiz=1;
    for(int i=1; i<tam; i++)
        raiz = raiz * arbol[i];
    arbol[0] = raiz;
}

void alta(int* arbol,BlockchainFederada* federada, char* mensaje,int arreglo[],int*cont,int numBC, int tam, int* raizAnterior){
    agregarBloque(federada->blockchains[numBC],arreglo,cont,mensaje);
    actualizarArbolValidacion(arbol,arreglo[*cont],numBC, tam, raizAnterior); 
}

void actualizacion(int indice, int id, char* mensaje, int arreglo[],int* cont, BlockchainFederada* federada, int* arbol, int tam, int* raizAnterior){
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

    while(bloqueAModificar!=NULL){
        bloqueAModificar->id = arreglo[*cont];
        (*cont)++;
        bloqueAModificar = bloqueAModificar->sig;
    }
    actualizarArbolValidacion(arbol,arreglo[*cont],indice,tam,raizAnterior);
}

void validacion(int raizAnterior,int* arbol,int tam,BlockchainFederada* federada){
    int mult = 1;
    for(int i=1; i<tam; i++,mult*=arbol[i]);
    if(raizAnterior > arbol[0] || arbol[0] != mult){
        printf("\nLa raiz esta mal\n");
        return;
    }
    int cant = (federada->capacidad)-1;
    for(int i=0; i<cant;i++){
        Bloque* bcuno = federada->blockchains[i]->primero;
        Bloque* bcdos = bcuno->sig;
        while(bcdos){
            if(bcuno->id >= bcdos->id){
                printf("\nLos id no corresponden\n");
                return;
            }
            bcuno = bcdos;
            bcdos = bcdos->sig;
        }
   }
   printf("Todo bien :)\n");
}