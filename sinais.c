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
#include "Corzinha.h"

int SON_PID = 0;

void signalHandler(int sig){
    kill(0, SIGKILL);
}

void comando(int sig){
    kill(SON_PID, sig);
}

//Função para atribuir à vsh enquanto ela espera o processo de foreground terminar.
void setSigactionForeground(struct sigaction* act, int pid){
    SON_PID = pid;
    act->sa_handler = comando;
    act->sa_flags = SA_RESTART;
    sigaction(SIGINT, act, NULL);
    sigaction(SIGTSTP, act, NULL);
    sigaction(SIGQUIT, act, NULL);
}

void resetSigaction(struct sigaction* act){
    act->sa_handler = SIG_DFL;
    act->sa_flags = SA_RESTART;
    sigaction(SIGINT, act, NULL);
    sigaction(SIGTSTP, act, NULL);
    sigaction(SIGQUIT, act, NULL);
}

void setSigactionMain(struct sigaction* act){
    act->sa_handler = zeca;

    sigset_t sigset;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGTSTP);
    sigaddset(&sigset, SIGQUIT);

    act->sa_mask = sigset;
    act->sa_flags = SA_RESTART;
    sigaction(SIGUSR1, act, NULL);
    sigaction(SIGUSR2, act, NULL);
}

void setSigactionSIGUSR(struct sigaction* act){
    act->sa_handler = signalHandler;
    act->sa_flags = SA_RESTART;
    sigaction(SIGUSR1, act, NULL);
    sigaction(SIGUSR2, act, NULL);
}

void zeca(int sig){

    //Teste para ver se o signal fica pendente.
    // Funcionou
    sleep(10);

    printZeca();
    printLineCommand();
    fflush(stdout);

}