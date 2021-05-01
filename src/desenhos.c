// Created by igor on 29/04/2021
// in T1_DESENHOS_C as desenhos.c 
//
#include "desenhos.h"
#include "Corzinha.h"
#include <stdio.h>
#include <unistd.h>

// Constantes definidas com o propósito de
// facilitar a impressão colorida do zé jacaré,
// mais conhecido como Zeca
#define V(c) FILL VERDE c RESET
#define W(c) FILL CINZA_CLARO c RESET
#define A(c) FILL AZUL c RESET
#define Y(c) FILL AMARELO c RESET
#define P(c) FILL PRETO c RESET
#define R(c) FILL VERMELHO c RESET
#define T(c) SPOTLIGHT "7;" CIANO c RESET
#define S(c) SPOTLIGHT VERMELHO c RESET

// Limpa a saída padrão do terminal.
void clearScreen(void)
{
    usleep(1 * 100000); // Tempo de espera
    fflush(stdout);
    const char * CLEAR_SCREEN_ANSI = "\033[1;1H\033[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

// Faz a impressão do Zeca na saída padrão.
void printZeca(void){
    printf(
    "\n"
    "                    "V(".--.  .--.") "\n"
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
    "   |->" BOLD VERDE " by zé jacaré\n" RESET RESET);
}

// Imprime a tela inicial.
void entryScreen(void){
    int c= 0;
    while(c++ < 2) {
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
