//
// Created by fernando on 26/04/2021.
//

#include "Lista.h"
#include "Corzinha.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef struct cel Cel;

struct cel{
    int gid;
    Cel * prox;
};

struct lista{
    Cel* prim,
       * ult;
};

void armageddon(Lista* list){

    for(Cel* aux = list->prim; aux; aux = aux->prox)
        killpg(aux->gid, SIGKILL);
}

Lista* iniciaLista(){
    Lista* list = malloc(sizeof(Lista));
    list->prim = list->ult = NULL;
    return list;
}

void insereLista(Lista* list, int gid){
    Cel* cel = malloc(sizeof(Cel));
    cel->gid = gid;
    cel->prox = NULL;

    if (!list->prim)
        list->prim = list->ult = cel;
    else{
        list->ult->prox = cel;
        list->ult = cel;
    }

}

void removeLista(Lista* list, int gid){
    Cel * ant,
        * aux;
    for(aux = list->prim; aux != NULL; aux = aux->prox){
        if(aux->gid == gid){
            break;
        }
        ant = aux;
    }

    if(list->prim == aux && list->ult == aux) list->prim = list->ult = NULL;
    else if(list->prim == aux)  list->prim = aux->prox;
    else if(list->ult == aux){
        ant->prox = NULL;
        list->ult = ant;
    }
    else    ant->prox = aux->prox;

}

void imprimeLista(Lista* list){

    printf(NORMAL VERDE "Lista:\n" RESET);

    if (!list->prim){ printf("Lista Vazia.\n\n"); return; }

    int cont=0;
    for(Cel * aux = list->prim; aux; aux=aux->prox)
        printf("Gid[%d]: %d\n", cont++, aux->gid);
    printf("\n\n");
}

void liberaLista(Lista * lis){
    Cel* prox;
    Cel* aux = lis->prim;

    while(aux != NULL){
        prox = aux->prox;
        free(aux);
        aux = prox;
    }

    //for (Cel * aux=lis->prim, * prox=aux->prox; aux; aux=prox, aux=aux->prox) free(aux);
}