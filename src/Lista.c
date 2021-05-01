//
// Created by fernando on 26/04/2021.
//

#include "Lista.h"
#include "Corzinha.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct cel Cel;

// Definição da célula da nossa lista.
// pid é o pid do processo que é líder do grupo.
struct cel{
    int pid;
    Cel * prox;
};

// Sentinela da lista.
struct lista{
    Cel* prim,
       * ult;
};

// Função que implementa o passaProFilho "liberamoita".
void liberaMoita(Lista* list){

    for(Cel* aux = list->prim; aux; aux = aux->prox) {
        // Para cada processo na nossa lista, verifica se ele já terminou.
        waitpid(aux->pid, NULL, WNOHANG);
    }
}

// Função que implementa o passaProFilho "armageddon".
void armageddon(Lista* list, int pid){

    for(Cel* aux = list->prim; aux; aux = aux->prox){
        // Para cada processo na nossa lista, verifica as seguintes condições:

        // Se o pid do processo é diferente do grupo do processo.
        if(aux->pid != getpgid(aux->pid)) {
            // Se isso for verdade, signifnica que é um processo em foreground que foi suspenso.
            // Mata este processo.
            kill(aux->pid, SIGKILL);
        }
        // Se o pid do processo é diferente do pid da VSH.
        else if(pid != aux->pid){
            // Se isso for verdade, mata o processo.
            killpg(aux->pid, SIGKILL);
        }
    }

}

// Abaixo estão funções padrão de lista.

Lista* iniciaLista(){
    Lista* list = malloc(sizeof(Lista));
    list->prim = list->ult = NULL;
    return list;
}

void insereLista(Lista* list, int pid){
    Cel* cel = malloc(sizeof(Cel));
    cel->pid = pid;
    cel->prox = NULL;

    if (!list->prim)
        list->prim = list->ult = cel;
    else{
        list->ult->prox = cel;
        list->ult = cel;
    }
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

