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

void preencheArgumentos(tCommand* cmd, int background){

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

void printCommand(tCommand* cmd){

    printf(NORMAL MAGENTA "Comando inteiro:\n" RESET "%s\n", cmd->fullCommand);
    printf(NORMAL AZUL "Nome do comando:" RESET " %s\n", cmd->command);
    printf(NORMAL AMARELO "Argumentos:\n" RESET);
    for (int i=0; i < cmd->nargs+2; i++){
        printf("Arg[%d]: %s\n", i, cmd->args[i]);
    }
    printf("\n\n");
}

void freeComand(tCommand* cmd) {
    free(cmd->args);
}

int readLine(){

    tCommand cmd[5];
    int qtdCmds = 0;
    int background = 0;

    char command_line[LINE_MAX], * save;

    if (scanf("%[^\n]%*c", command_line) != 1) return 0;

//    printf("\"%s\"\n", command_line);
    if(command_line[strlen(command_line)- 1] == '&'){
        strncpy(command_line, command_line, strlen(command_line)-1);
        //cria filho
        //muda session do filho

        background = 1;
    }
//    printf("\"%s\"\n", command_line);

    cmd[qtdCmds].fullCommand = strtok_r(command_line, "|", &save);

    while (cmd[qtdCmds].fullCommand){
        if(strcmp(cmd[qtdCmds].fullCommand, "armageddon") == 0){
            return(0);
        }
        preencheArgumentos(&cmd[qtdCmds], background);
        qtdCmds++;
        cmd[qtdCmds].fullCommand = strtok_r(NULL, "|", &save);
    }

    int qtdPipes = qtdCmds-1;

    int fd[qtdPipes][2];

    for(int j = 0; j<qtdPipes; j++){
        if(pipe(fd[j]) < 0){
            printf("Erro ao abrir pipe\n");
            printf("I dont fell to good\n");
            return 1;
        }
    }

    if(qtdPipes == 0){
        int pid = fork();
        if(pid == 0){
            execvp(cmd[0].command, cmd[0].args);
        }
        else{
            waitpid(pid, NULL, 0);
        }
    }
    else {
        for (int j = 0; j < qtdCmds; j++) {
            int pid = fork();
            if (pid == 0) {

                if (j == 0) {
                    dup2(fd[j][1], STDOUT_FILENO);
                } else if (j == qtdPipes) {
                    dup2(fd[j - 1][0], STDIN_FILENO);
                } else {
                    dup2(fd[j - 1][0], STDIN_FILENO);
                    dup2(fd[j][1], STDOUT_FILENO);
                }

                for (int k = 0; k < qtdPipes; k++) {
                    close(fd[k][0]);
                    close(fd[k][1]);
                }

                execvp(cmd[j].command, cmd[j].args);
            } else {
                if(j < qtdPipes)
                    close(fd[j][1]);
                waitpid(pid, NULL, 0);
            }
        }
        for (int k = 0; k < qtdPipes; k++) {
            close(fd[k][0]);
        }
    }

    for(int j =0; j<qtdCmds; j++){
        freeComand(&cmd[j]);
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