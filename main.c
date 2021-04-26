#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "shell.h"
#include "Corzinha.h"

#define V(c) FILL VERDE c RESET
#define W(c) FILL CINZA_CLARO c RESET
#define P(c) FILL PRETO c RESET
#define R(c) FILL VERMELHO c RESET

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
           "                   "V("|")W("\\")P("  ")W("/")V(" ")W("\\")P("  ")W("/")V("    --,    \\_\n")
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
           "\033[5;" VERMELHO "To doidão.\033[0m\n" RESET
           "   |->" BOLD VERDE " by zé jacaré\n" RESET);
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);

}

void clearScreen()
{
    const char *CLEAR_SCREEN_ANSI = "\033[1;1H\033[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

int main() {

    struct sigaction act;
    act.sa_handler = zeca;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    //clearScreen();
    run_shell();
    return 0;
}

