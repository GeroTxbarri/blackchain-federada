
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
int* construirArbolValidacion(BlockchainFederada* federada) {

    int hojasFederada = federada->cantidad;
    int cantidadHojas = siguientePotencia(hojasFederada);
    
    int* arregloArbol = (int*)malloc((cantidadHojas + 1) * sizeof(int));
   
    int valorRaiz = 1;
    for (int i = 0; i < cantidadHojas; i++) {
        int valorHoja;
        
        if (i < hojasFederada) {

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


void imprimirBC(Bloque* bc){
    for(;bc->sig!=NULL;bc=bc->sig)
        printf("%d %s --",bc->id,bc->mensaje);
    printf("/n");
}
