
#include "BCfederada.h"


Bloque* crearBloque(int id, char* mensaje){
    Bloque* b = malloc(sizeof(Bloque));
    b->id = id;
    strcpy(b->mensaje, mensaje);
    b->ant = b->sig = NULL;
    return b;
}

Bloque* agregarBloque(Bloque* bc ,int id, char* mensaje){
    for(;bc->sig!=NULL;bc=bc->sig);
    Bloque *bc = rearBloque(id,mensaje);
    bc->sig = bc;
    
}
void imprimirBC(Bloque* bc){
    for(;bc->sig!=NULL;bc=bc->sig)
        printf("%d %s --",bc->id,bc->mensaje);
    printf("/n");
}
