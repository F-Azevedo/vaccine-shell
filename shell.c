// Created by igor on 16/04/2021
// in T1_SHELL_C as shell.c 
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Corzinha.h"
#include <limits.h>

#define ARG_MAX 3

void execCommand(char * fullCommand){

    char * save,
         * command = strtok_r(fullCommand, " ", &save),
         * arg = strtok_r(NULL, " ", &save),
         * all_args[ARG_MAX];

    // Find all args from command
    int num_args = 0;
    for (num_args; arg; num_args++, arg=strtok_r(NULL, " ", &save))
        all_args[num_args] = arg;

    // Create arg vector to execute command.
    char ** args = malloc(sizeof(*args) * (num_args + 2));
    args[0] = command;
    for (int i=1; i < num_args; i++){
        args[i] = all_args[i-1];
        printf("args[%d], %s\n", i, args[i]);
    }
    args[num_args+1] = NULL;

    printf("Vetor args:\n");
    for (int i=0; i < num_args+1; i++){
        if (i == num_args) printf("\"%s\", ", args[i]);
        else printf("\"%s\"\n", args[i]);
    }
    printf("\n");
    // exec()
}

int readLine(){

    char command_line[LINE_MAX], * save;
    if (scanf("%[^\n]%*c", command_line) != 1) return 0;

    printf("COMAND LINE[1]: \"%s\"\n", command_line);
    char * command = strtok_r(command_line, "|", &save);
    printf("COMAND LINE[2]: \"%s\"\n", command_line);

    while (command){
        printf("COMANDO: \"%s\"\n", command);
        if(strcmp(command, "armageddon") == 0){
            exit(0);
        }
//        char * aux = malloc(sizeof(char) * strlen(command));
//        strcpy(aux, command);
//        execCommand(aux);
        execCommand(command);
        command = strtok_r(NULL, "|", &save);
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
    printf(BOLD MAGENTA "afv:vsh "
           BOLD VERDE "%s "
           BOLD AZUL "%s > " RESET, getlogin(), removePath(cwd));
}

void run_shell() {

    do {
        printLineCommand();
    } while (readLine());
}