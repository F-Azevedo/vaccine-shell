//
// Created by fernando on 26/04/2021.
//

#ifndef T1_SO_LISTA_H
#define T1_SO_LISTA_H

typedef struct lista Lista;

Lista* iniciaLista();
void liberaMoita(Lista* list);
void liberaLista(Lista* list);
void imprimeLista(Lista* list);
void armageddon(Lista* list, int pid);
void insereLista(Lista* list, int gid);

#endif //T1_SO_LISTA_H
