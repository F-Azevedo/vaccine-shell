//
// Created by fernando on 28/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "desenhos.h"
#include "sinais.h"
#include "shell.h"

// Variável global para sabermos, dentro do tratador de sinais, quem é
// o filho que deve receber os sinais.
int SON_PID = 0;

// Handler que vai matar o grupo do processo background que receber o SIGUSR 1 ou 2.
void signalHandler(int sig){
    kill(0, SIGKILL);
}

// Handler que vai passar os sinais que a VSH receber para o processo foreground.
void passaProFilho(int sig){
    kill(SON_PID, sig);
}

// Handler que vai imprimir o Zeca.
void zeca(int sig){
    //Teste para ver se o signal fica pendente.
    // Funcionou
    sleep(10);

    printZeca();

    // Printa a linha de comando duas vezes se o sinal for mandado por kill pela própria VSH.
    printLineCommand();
    fflush(stdout);
}

//Função para modificar o Sigaction da VSH enquanto ela espera o processo de foreground terminar.
void setSigactionVSH(struct sigaction* act, int pid){
    // Seta a variável global para o pid do filho.
    SON_PID = pid;

    act->sa_handler = passaProFilho;
    act->sa_flags = SA_RESTART;
    sigaction(SIGINT, act, NULL);
    sigaction(SIGTSTP, act, NULL);
    sigaction(SIGQUIT, act, NULL);
}

// Função para resetar o Sigaction da VSH.
void resetSigaction(struct sigaction* act){
    act->sa_handler = SIG_DFL;
    act->sa_flags = SA_RESTART;
    sigaction(SIGINT, act, NULL);
    sigaction(SIGTSTP, act, NULL);
    sigaction(SIGQUIT, act, NULL);
}

// Função para atribuir o Sigaction padrão da VSH.
void setSigactionPadraoVSH(struct sigaction* act){
    act->sa_handler = zeca;

    sigset_t sigset;
    sigemptyset(&sigset);

    // Bloquear sinais do teclado durante o handler.
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGTSTP);
    sigaddset(&sigset, SIGQUIT);

    act->sa_mask = sigset;
    act->sa_flags = SA_RESTART;

    // Capturar SIGUSR 1 e 2.
    sigaction(SIGUSR1, act, NULL);
    sigaction(SIGUSR2, act, NULL);
}

// Função para modificar o Sigaction dos processos em background.
void setSigactionSIGUSR(struct sigaction* act){
    act->sa_handler = signalHandler;
    act->sa_flags = SA_RESTART;
    sigaction(SIGUSR1, act, NULL);
    sigaction(SIGUSR2, act, NULL);
}

void setSigactionForeground(struct sigaction* act){
    act->sa_handler = SIG_IGN;
    sigemptyset(&act->sa_mask);
    sigaction(SIGUSR1, act, NULL);
    sigaction(SIGUSR2, act, NULL);
}