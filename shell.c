// Created by igor on 16/04/2021
// in T1_SHELL_C as shell.c 
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Corzinha.h"
#include "Lista.h"
#include <limits.h>
#include <sys/wait.h>

#define ARG_MAX 3

typedef struct COMANDO{
    char* fullCommand;
    char* command;
    char** args;
    int nargs;
}tCommand;

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

void preencheArgumentos(tCommand* cmd){

    char* save;

    cmd->nargs = 0;
    cmd->command = strtok_r(cmd->fullCommand, " ", &save);

    char    * arg = strtok_r(NULL, " ", &save),
            * all_args[ARG_MAX];

    // Find all args from command
    for (; arg; cmd->nargs++, arg=strtok_r(NULL, " ", &save))
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

void freeCommandArgs(tCommand* cmd) {
    free(cmd->args);
}

void freeCommand(tCommand* cmd){
    freeCommandArgs(cmd);
    free(cmd);
}

void foreground(tCommand cmd[5]){

    printf("FOREGROUND\n");

    int pid = fork();
    if(pid == 0){
        if(execvp(cmd[0].command, cmd[0].args) == -1){
            printf("Da um comando válido filhx da pute\n");
            exit(0);
        }
    }
    else waitpid(pid, NULL, 0);

}

void liberaPipes(int pipes[][2], int type, int qtd) {

    for (int k = 0; k < qtd; k++) close(pipes[k][type]);

}

void background(tCommand cmd[5], int qtdCmds, Lista* list){

    int BACKGROUND = fork();

    if(BACKGROUND == 0){
        printf("BACKGROUND\n");
        printf("RES ANTIGO: %d\n", getsid(getpid()));
        int newSession = setsid();
        printf("NewSession = %d\n", newSession);

        if(newSession == -1){ perror("Erro na criação de uma nova sessão"); exit(1);}

        int qtdPipes = qtdCmds-1;
        int fd[qtdPipes][2];

        for(int j = 0; j<qtdPipes; j++)
            if(pipe(fd[j]) < 0){ printf("Erro ao abrir pipe\n"); exit(1); }

        //printf(NORMAL AMARELO "Passei aqui\n" RESET);
        for (int j = 0; j < qtdCmds; j++) {
            int pid = fork();
            if (pid == 0) {
                //printf(NORMAL VERMELHO "Passei aqui\n" RESET);
                //printCommand(cmd[j]);
                if (j == 0) {
                    dup2(fd[j][1], STDOUT_FILENO);
                } else if (j == qtdPipes) {
                    dup2(fd[j - 1][0], STDIN_FILENO);
                } else {
                    dup2(fd[j - 1][0], STDIN_FILENO);
                    dup2(fd[j][1], STDOUT_FILENO);
                }

                // Libera os todos os pipes
                liberaPipes(fd, 0, qtdPipes);
                liberaPipes(fd, 1, qtdPipes);

                if(execvp(cmd[j].command, cmd[j].args) == -1) {
                    printf("Da um comando válido filho da puta\n");
                    exit(0);
                }
            } else {
                //printf(NORMAL MAGENTA "Passei aqui\n" RESET);
                if(j < qtdPipes) close(fd[j][1]);
                waitpid(pid, NULL, 0);
            }
        }

        // Libera todos pipes de leitura
        liberaPipes(fd, 0, qtdPipes);

        for(int j =0; j<qtdCmds; j++) freeCommandArgs(&cmd[j]);

        //Termina o filho.
        exit(0);
    }
    else{
        //waitpid(BACKGROUND, NULL, 0);
        insereLista(list, BACKGROUND);
    }

}

void defineGround(tCommand cmd[5], int qtdCmds, Lista* list){

    //for (int i=0; i < qtdCmds; i++) printCommand(&cmd[i]);
    if(qtdCmds < 2) foreground(cmd);
    else background(cmd, qtdCmds, list);

}

int readLine(Lista* list){

    tCommand cmd[5];
    int qtdCmds = 0;

    char* command_line, * save;
    size_t bufsize = LINE_MAX;
    command_line = (char*) malloc(bufsize * sizeof(char));
    getline(&command_line, &bufsize, stdin);
    command_line[strlen(command_line)-1] = 0;

    printf("\"%s\"\n", command_line);

    cmd[qtdCmds].fullCommand = strtok_r(command_line, "|", &save);
    printf("FULL COMMAND: '%s'\n", cmd[qtdCmds].fullCommand);
    while (cmd[qtdCmds].fullCommand){
        if(strcmp(cmd[qtdCmds].fullCommand, "armageddon") == 0){
            armageddon(list);
            printf("SIM\n");
            free(command_line);
            return(0);
        }
        preencheArgumentos(&cmd[qtdCmds]);
        qtdCmds++;
        cmd[qtdCmds].fullCommand = strtok_r(NULL, "|", &save);
    }



    defineGround(cmd, qtdCmds, list);

    free(command_line);
    for(int j =0; j<qtdCmds; j++) {
        freeCommandArgs(&cmd[j]);
    }
    return 1;

}

void run_shell(Lista* list) {

    do{
        printLineCommand();
    } while (readLine(list));

}