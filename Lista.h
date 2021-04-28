//
// Created by fernando on 26/04/2021.
//

#ifndef T1_SO_LISTA_H
#define T1_SO_LISTA_H

typedef struct lista Lista;

Lista* iniciaLista();
void insereLista(Lista* list, int gid);
void removeLista(Lista* list, int gid);
void imprimeLista(Lista* list);
void liberaLista(Lista * lis);
void armageddon(Lista* list, int pid);
void liberaMoita(Lista* list);

#endif //T1_SO_LISTA_H
