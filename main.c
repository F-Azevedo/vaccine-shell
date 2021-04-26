#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "shell.h"
#include "Corzinha.h"

void zeca(int sig){
    sigset_t sigset;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigaddset(&sigset, SIGQUIT);
    if(sigprocmask(SIG_BLOCK, &sigset, NULL))
        perror("Erro na criação da sigprocmask\n");

    printf(BOLD VERDE"\n                     .--.  .--.\n"
           "                    /    \\/    \\\n"
           "                   | .-.  .-.   \\\n"
           "                   |/_  |/_  |   \\\n"
           "                   || `\\|| `\\|    `----.\n"
           "                   |\\X_/ \\X_/    --,    \\_\n"
           " .--\"\"\"\"\"-.       /              (` \\     `-.\n"
           "/          \\-----'-.              \\          \\\n"
           "\\  () ()                         /`\\          \\\n"
           "|                         .___.-'   |          \\\n"
           "\\                        /` \\|      /           ;\n"
           " `-.___             ___.' .-.`.---.|             \\\n"
           "    \\| ``-..___,.-'`\\| / /   /     |              `\\\n"
           "     `      \\|      ,`/ /   /   ,  /\n"
           "             `      |\\ /   /    |\\/\n"
           "              ,   .'`-;   '     \\/\n"
           "         ,    |\\-'  .'   ,   .-'`\n"
           "       .-|\\--;`` .-'     |\\.'\n"
           "      ( `\"'-.|\\ (___,.--'`'   \n"
           "       `-.    `\"`          _.--'\n"
           "          `.          _.-'`-.\n"
           "            `''---''``       `.\n" RESET
           "\033[5;" VERMELHO "To doidão.\033[0m\n" RESET);
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

    clearScreen();
    run_shell();
    return 0;
}

