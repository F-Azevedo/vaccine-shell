// Created by igor on 16/04/2021
// in T1_SHELL_C as shell.c 
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Corzinha.h"
#include <limits.h>
#include <sys/wait.h>

#define ARG_MAX 3

typedef struct COMANDO{
    char* fullCommand;
    char* command;
    char** args;
    int nargs;
}tCommand;

void preencheArgumentos(tCommand* cmd){

    char* save;

    cmd->nargs = 0;
    cmd->command = strtok_r(cmd->fullCommand, " ", &save);

    char    * arg = strtok_r(NULL, " ", &save),
            * all_args[ARG_MAX];

    // Find all args from command
    for (cmd->nargs; arg; cmd->nargs++, arg=strtok_r(NULL, " ", &save))
        all_args[cmd->nargs] = arg;

    // Create arg vector to execute command.
    cmd->args = malloc(sizeof(char*) * (cmd->nargs + 2));
    cmd->args[0] = cmd->command;

    for (int i=1; i <= cmd->nargs; i++){
        cmd->args[i] = all_args[i-1];
    }

    cmd->args[cmd->nargs + 1] = NULL;

}

void execCommand(tCommand* cmd){

    int pid = fork();
    if(pid == 0) {
        printf("[FILHO]: Vou executar o comando \"%s\"\n", cmd->command);
        execvp(cmd->command, cmd->args);
    }
    else{
        printf("[PAI]: O pid do filho é %d\n", pid);
        waitpid(pid, NULL, 0);
    }

}

void freeComand(tCommand* cmd) {
    free(cmd->args);
}

int readLine(){

    tCommand comando[5];
    int i = 0;

    char command_line[LINE_MAX], * save;

    if (scanf("%[^\n]%*c", command_line) != 1) return 0;

    comando[i].fullCommand = strtok_r(command_line, "|", &save);

    while (comando[i].fullCommand){
        if(strcmp(comando[i].fullCommand, "armageddon") == 0){
            return(0);
        }
        preencheArgumentos(&comando[i]);
        i++;
        comando[i].fullCommand = strtok_r(NULL, "|", &save);
    }

    for(int j=0; j<i; j++) {
        execCommand(&comando[j]);
        freeComand(&comando[j]);
    }

    return 1;

}

char * removePath(char * path){

    int i;
    for (i = strlen(path)-1; path[i] != '/'; i--);
    char * new = malloc(sizeof(char) * (strlen(path)-i));
    for (int j=i+1; j <= strlen(path); j++){
        new[j-(i+1)] = path[j];
    }
    return new;
}

void printLineCommand(){

    char cwd[PATH_MAX], user[NAME_MAX];
    getcwd(cwd, sizeof(cwd));
    char* func = removePath(cwd);
    printf(BOLD MAGENTA "afv:vsh "
           BOLD VERDE "%s "
           BOLD AZUL "%s > " RESET, getlogin(), func);
    free(func);

}

void run_shell() {

    do {
        printLineCommand();
    } while (readLine());

}