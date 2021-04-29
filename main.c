#include <signal.h>
#include "shell.h"
#include "Lista.h"
#include "desenhos.h"

int main() {

    struct sigaction act;
    setSigactionMain(&act);

    entryScreen();  // Imprime tela de entrada

    Lista* list = iniciaLista();
    run_shell(list, &act);

    liberaMoita(list);
    liberaLista(list);  // Libera a estrutura da lista
    return 0;

}

