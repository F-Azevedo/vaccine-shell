//
// Created by fernando on 28/04/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#include "sinais.h"
#include "shell.h"
#include "Corzinha.h"

#define V(c) FILL VERDE c RESET
#define W(c) FILL CINZA_CLARO c RESET
#define A(c) FILL AZUL c RESET
#define Y(c) FILL AMARELO c RESET
#define P(c) FILL PRETO c RESET
#define R(c) FILL VERMELHO c RESET
#define T(c) SPOTLIGHT "7;" CIANO c RESET
#define S(c) SPOTLIGHT VERMELHO c RESET

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

    printf("\n"
           "                    " V(".--.  .--.")"\n"
                                                 "                   "V("/    \\/    \\")"\n"
                                                                                         "                   "V("| ") W(".-.") V("  ") W(".-.") V("  \\\n")
    "                   "V("|")W("/_  |/_  |")V("   \\\n")
    "                   "V("|")W("| `\\|| `\\")W("|")V("    `----.\n")
    "                   "V("|")W("\\")T("0 ")W("/")V(" ")W("\\")T("0 ")W("/")V("    --,    \\_\n")
    " "V(".--\"\"\"\"\"-.")"       "V("/              (` \\     `-.\n")
    ""V("/          \\-----'-.              ")V("\\")V("          \\\n")
    ""V("\\  ") P("  ")V(" ")P("  ")V("                         ")V("/`\\")V("         \\\n")
    ""V("|                         .___")V(".-'   |")V("          \\\n")
    ""V("\\                        ")V("/` ")W("\\|")V("      ")V("/           ;\n")
    " "V("`-.___             ___.' ")R(".-.")W("`")R(".---.")V("|             \\\n")
    "    "W("\\|")" "V("``-..___,.-'`")W("\\|")V(" / ")R("/   /     |")V("              `\\\n")
    "     "W("`")"      "W("\\|")"      "W(",`")V("/ ")R("/   /   ")W(",")R("  /")V("                  \n")
    "             "W("`")"      "W("|\\")V(" ")R("/   /    ")W("|\\")V("/                      \n")
    "              "W(",")"   "V(".'`-")R(";   '     ")W("\\/")V("                         \n")
    "         "W(",")"    "W("|\\")V("-'  ")R(".'   ")W(",")R("   .-'`")V("                           \n")
    "       "V(".-")W("|\\")V("--")W(";")V("`` ")R(".-'     ")W("|\\")R(".'")V("                                \n")
    "      "V("( `")W("\"'")V("-.")W("|\\")V(" ")R("(___,.--'")V("`'                                   \n")
    "       "V("`-.    `\"`          _.--'                               \n")
    "          "V("`.          _.-'`-.'                                  \n")
    "            "V("`''---''``")"       "V("`.'                                 \n")
    S("To doidão.\n")
    S("Vodu é pra jacu\n")
    "   |->" BOLD VERDE " by zé jacaré\n" RESET);
    printLineCommand();
    fflush(stdout);

}