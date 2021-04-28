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
#define A(c) FILL AZUL c RESET
#define Y(c) FILL AMARELO c RESET
#define P(c) FILL PRETO c RESET
#define R(c) FILL VERMELHO c RESET
#define T(c) SPOTLIGHT "7;" CIANO c RESET
#define S(c) SPOTLIGHT VERMELHO c RESET

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
           S("Vodu é pra jacu\n")
           "   |->" BOLD VERDE " by zé jacaré\n" RESET);
    printLineCommand();
    fflush(stdout);
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);

}

void clearScreen()
{
    usleep(1 * 100000);
    fflush(stdout);
    const char *CLEAR_SCREEN_ANSI = "\033[1;1H\033[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void print(){
    int c= 0;
    while(c++ <= 5) {
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n");
        clearScreen();
        printf(
                "| V |                                     | V |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T                            |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "| | |                                     | | |\n"
                "| V |- - - - - - - - - - - - - - - - - - -| V |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R                          |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "| | |- - - - - - - - - - - - - - - - - - -| | |\n"
                "| V |                                     | V |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A                        |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "| | |                                     | | |\n"
                "| V |                                     | V |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B                      |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n"
               "| | |                                     | | |\n"
               "| V |                                     | V |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |        T R A B A                    |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n");
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "| | |                                     | | |\n"
               "| V |                                     | V |\n"
               "|   |                                     |   |\n"
               "|   |        T R A B A L                  |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n");
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "| | |                                     | | |\n"
               "| V |                                     | V |\n"
               "|   |        T R A B A L H                |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n");
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "| | |                                     | | |\n"
               "| V |        T R A B A L H O              | V |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n");
        clearScreen();
        printf(
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "| | |        T R A B A L H O  D           | | |\n"
               "| V |                                     | V |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |                                     |   |\n"
               "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
               "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "| | |                                     | | |\n"
                "| V |                                     | V |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "| | |                  S                  | | |\n"
                "| V |                                     | V |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "| | |                                     | | |\n"
                "| V |   B                                 | V |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "|   |                                     |   |\n"
                "| | |   B Y:                              | | |\n"
                "| V |                                     | V |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "|   |                                     |   |\n"
                "|   |   B Y:     "R("FERNANDO AZEVEDO")"         |   |\n"
                "| | |                                     | | |\n"
                "| V |            "A("IGOR VAREJÃO")"             | V |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "|   |                                     |   |\n"
                "|   |   B Y:     "R("FERNANDO AZEVEDO")"         |   |\n"
                "|   |                                     |   |\n"
                "| | |            "A("IGOR VAREJÃO")"             | | |\n"
                "| V |                                     | V |\n"
                "|   |            "Y("LUÍS EDUARDO CÂMARA")"      |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "|   |                                     |   |\n"
                "|   |   B Y:     "R("FERNANDO AZEVEDO")"         |   |\n"
                "|   |                                     |   |\n"
                "|   |            "A("IGOR VAREJÃO")"             |   |\n"
                "| | |                                     | | |\n"
                "| V |            "Y("LUÍS EDUARDO CÂMARA")"      | V |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "|   |                                     |   |\n"
                "|   |   B Y:     "R("FERNANDO AZEVEDO")"         |   |\n"
                "|   |                                     |   |\n"
                "|   |            "A("IGOR VAREJÃO")"             |   |\n"
                "|   |                                     |   |\n"
                "| | |            "Y("LUÍS EDUARDO CÂMARA")"      | | |\n"
                "| V |- - - - - - - - - - - - - - - - - - -| V |\n"
                "|   |                                     |   |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "|   |                                     |   |\n"
                "|   |   B Y:     "R("FERNANDO AZEVEDO")"         |   |\n"
                "|   |                                     |   |\n"
                "|   |            "A("IGOR VAREJÃO")"             |   |\n"
                "|   |                                     |   |\n"
                "|   |            "Y("LUÍS EDUARDO CÂMARA")"      |   |\n"
                "| | |- - - - - - - - - - - - - - - - - - -| | |\n"
                "| V |                                     | V |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "|   |                                     |   |\n"
                "|   |   B Y:     "R("FERNANDO AZEVEDO")"         |   |\n"
                "|   |                                     |   |\n"
                "|   |            "A("IGOR VAREJÃO")"             |   |\n"
                "|   |                                     |   |\n"
                "|   |            "Y("LUÍS EDUARDO CÂMARA")"      |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "| | |                                     | | |\n");
        clearScreen();
        printf(
                "|   |                                     |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |                                     |   |\n"
                "|   |        T R A B A L H O  D E         |   |\n"
                "|   |                                     |   |\n"
                "|   |                  S O                |   |\n"
                "|   |                                     |   |\n"
                "|   |   B Y:     "R("FERNANDO AZEVEDO")"         |   |\n"
                "|   |                                     |   |\n"
                "|   |            "A("IGOR VAREJÃO")"             |   |\n"
                "|   |                                     |   |\n"
                "|   |            "Y("LUÍS EDUARDO CÂMARA")"      |   |\n"
                "|   |- - - - - - - - - - - - - - - - - - -|   |\n"
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

