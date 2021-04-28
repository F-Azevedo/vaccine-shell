#include <signal.h>

#include "shell.h"
#include "Lista.h"
#include "animacao.h"

int main() {

    struct sigaction act;
    setSigactionMain(&act);

    clearScreen();

    //print();
    Lista* list = iniciaLista();
    run_shell(list, &act);

    liberaMoita(list);
//    imprimeLista(list);
    liberaLista(list);
    return 0;

}

