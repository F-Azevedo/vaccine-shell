//
// Created by fernando on 26/04/2021.
//

#include "Lista.h"
#include "Corzinha.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

typedef struct cel Cel;

struct cel{
    int gid;
    Cel * prox;
};

struct lista{
    Cel* prim,
       * ult;
};

void liberaMoita(Lista* list){

    for(Cel* aux = list->prim; aux; aux = aux->prox)
        waitpid(aux->gid, NULL, WNOHANG);

}

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
    free(lis);
}

