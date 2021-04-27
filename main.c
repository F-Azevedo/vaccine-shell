#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "shell.h"
#include "Corzinha.h"
#include "Lista.h"
#include <time.h>

#define V(c) FILL VERDE c RESET
#define W(c) FILL CINZA_CLARO c RESET
#define P(c) FILL PRETO c RESET
#define R(c) FILL VERMELHO c RESET
#define T(c) SPOTLIGHT "7;" VERMELHO c RESET
#define S(c) SPOTLIGHT "7;" VERMELHO c RESET

void zeca(int sig){
    sigset_t sigset;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGQUIT);
    if(sigprocmask(SIG_BLOCK, &sigset, NULL))
        perror("Erro na criação da sigprocmask\n");

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
           "   |->" BOLD VERDE " by zé jacaré\n" RESET);
    printLineCommand();
    fflush(stdout);
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);

}

void clearScreen()
{
    sleep(0.2);
    fflush(stdout);
    const char *CLEAR_SCREEN_ANSI = "\033[1;1H\033[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void print(){
    int c=0;
    while(c++ <= 1) {
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "| 0 |- - - - - - - - - - - - - - - - - - -| 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "| 0 |                                     | 0 |\n");
        clearScreen();
        printf(
               "| O |                                     | O |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |        T R                          |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |- - - - - - - - - - - - - - - - - - -| O |\n"
               "|   |                                     |   |\n");
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "| 0 |- - - - - - - - - - - - - - - - - - -| 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |        T R A B                      | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "| 0 |                                     | 0 |\n");
        clearScreen();
        printf(
               "| O |                                     | O |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |        T R A B A L H                |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |- - - - - - - - - - - - - - - - - - -| O |\n"
               "|   |                                     |   |\n");
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "| 0 |- - - - - - - - - - - - - - - - - - -| 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |        T R A B A L H O  D E         | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |                                     |   |\n"
               "| 0 |                                     | 0 |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "| 0 |                                     | 0 |\n");
        clearScreen();
        printf(
               "| O |                                     | O |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |        T R A B A L H O  D E         |   |\n"
               "| O |                                     | O |\n"
               "|   |                  S O                |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |                                     | O |\n"
               "|   |                                     |   |\n"
               "| O |- - - - - - - - - - - - - - - - - - -| O |\n"
               "|   |                                     |   |\n");
    }
}

int main() {

    struct sigaction act;
    act.sa_handler = zeca;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    Lista* list = iniciaLista();
    clearScreen();

    print();
    run_shell(list);
    imprimeLista(list);
    liberaLista(list);
    return 0;
}

