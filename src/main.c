#include <signal.h>
#include "shell.h"
#include "Lista.h"
#include "desenhos.h"

int main() {

    struct sigaction act;

    // Inicia nosso controle de sinais, capturando os SIGUSR 1 e 2.
    setSigactionPadraoVSH(&act);

    // Imprime tela de entrada.
    entryScreen();

    // Inicia a lista que vai guardar o grupo dos processos que esta rodando em background e
    // os processos foreground suspensos.
    Lista* list = iniciaLista();

    // Roda a vsh.
    run_shell(list, &act);

    // Da um libera moita, para fazer a main ficar ciente que os processos filhos terminaram.
    liberaMoita(list);

    // Libera a lista de grupo de processos background e processos foreground suspensos.
    liberaLista(list);  // Libera a estrutura da lista

    return 0;

}

