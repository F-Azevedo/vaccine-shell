// Created by igor on 16/04/2021
// in T1_SHELL_C as shell.c 
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Corzinha.h"
#include <limits.h>

int readCommand(){

    char command_line[LINE_MAX];
//    printf("\nretorno: %d\n",scanf("%[^\n]%*c", command_line));
    if (scanf("%[^\n]%*c", command_line) != 1) return 0;
    char * command = strtok(command_line, " ");
    while (command) {
        printf("%s\n", command);
        command = strtok(NULL, " ");
    }
    return 1;
}

char * removePath(char * path){

    int i;
    for (i=strlen(path)-1; path[i] != '/'; i--);
    char * new = malloc(sizeof(char) * (strlen(path)-i));
    for (int j=i+1; j <= strlen(path); j++){
        new[j-(i+1)] = path[j];
    }
    return new;
}

void printLineCommand(){

    char cwd[PATH_MAX], user[NAME_MAX];
    getcwd(cwd, sizeof(cwd));
    printf(BOLD MAGENTA "efi "
           BOLD VERDE "%s "
           BOLD AZUL "%s > " RESET, getlogin(), removePath(cwd));
}

void run_shell(){

    do {
        printLineCommand();
    } while (readCommand());

}